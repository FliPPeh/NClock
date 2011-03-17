#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include <ncurses.h>

#define DIGIT_WIDTH    5
#define DIGIT_HEIGHT   5
#define DIGIT_SPACING  2

#define WIDTH(n) (((n - 1) * DIGIT_SPACING) + ((n) * DIGIT_WIDTH))
#define HEIGHT DIGIT_HEIGHT

void show_help(void);
void clock_main(int, int, int, int);
static void finish(int);
float get_kiloseconds(void);

int draw_time_kiloseconds(int, int);
int draw_time_24h(int, int);

int draw_number(const char*, int, int);
void draw_digit(int,int,int);

#define DIGITS 12

char digits[DIGITS][DIGIT_HEIGHT][DIGIT_WIDTH + 1] = {
    {
        "#####",
        "#   #",
        "#   #",
        "#   #",
        "#####"
    },
    {
        "  #  ",
        " ##  ",
        "  #  ",
        "  #  ",
        " ### "
    },
    {
        "#####",
        "    #",
        "#####",
        "#    ",
        "#####"
    },
    {
        "#####",
        "    #",
        " ####",
        "    #",
        "#####"
    },
    {
        "#   #",
        "#   #",
        "#####",
        "    #",
        "    #"
    },
    {
        "#####",
        "#    ",
        "#####",
        "    #",
        "#####"
    },
    {
        "#####",
        "#    ",
        "#####",
        "#   #",
        "#####"
    },
    {
        "#####",
        "    #",
        "    #",
        "    #",
        "    #"
    },
    {
        "#####",
        "#   #",
        "#####",
        "#   #",
        "#####"
    },
    {
        "#####",
        "#   #",
        "#####",
        "    #",
        "#####"
    },
    {
        "     ",
        "     ",
        "     ",
        "     ",
        "  #  "
    },
    {
        "     ",
        "  #  ",
        "     ",
        "     ",
        "  #  "
    }
};


int main(int argc, char **argv)
{
    int c;
    int clock_color = COLOR_CYAN;
    int border = 0;
    int tmp;
    int tfh = 0;
    int random = 0;

    for (;;)
    {
        if ((c = getopt(argc, argv, "b:c:hvdr:")) != -1)
        {
            switch (c)
            {
                case 'v': /* Version */
                    printf("%s version 1.0\n", "nclock");
                    return EXIT_SUCCESS;

                case 'h':
                    show_help();
                    return EXIT_SUCCESS;

                case 'b':
                    border = *optarg;

                    break;

                case 'd':
                    tfh = 1;
                    break;
                case 'r':
                    random = strtod(optarg, NULL);

                    break;

                case 'c':
                    tmp = strtod(optarg, NULL);

                    if ((tmp <= 8) && (tmp >= 0))
                        clock_color = tmp;
                    else
                        fprintf(stderr, "bad color value -- resorting to "
                                        "default\n");

                    break;

                case '?':
                    return EXIT_FAILURE;
            }
        }
        else
            break;
    }

    signal(SIGINT, finish);

    initscr();
    noecho();
    cbreak();

    start_color();
    use_default_colors();

    clock_main(border, tfh, random, clock_color);

    return EXIT_SUCCESS;
}


void show_help(void)
{
    printf("Usage: nclock [OPTIONS]\n\n");

    printf("Where OPTIONS can be one or more of the following:\n");
    printf("  -v\t\tDisplay version and exit\n");
    printf("  -h\t\tDisplay this help and exit\n");
    printf("  -c <color>\tUse <color> for the clock digits\n");
    printf("  -b\t\tDraw a border around the clock\n");
    printf("  -d\t\tDraw time in 24 hour format\n");
    printf("  -r <s>\tRandomize position every <s> seconds\n\n");

    printf("<color> can be any of the following:\n");
    printf("     0 (Black)\n");
    printf("     1 (Red)\n");
    printf("     2 (Green)\n");
    printf("     3 (Yellow)\n");
    printf("     4 (Blue)\n");
    printf("     5 (Magenta)\n");
    printf("     6 (Cyan [DEFAULT])\n");
    printf("     7 (White)\n");
    printf("     8 (Random)\n");
}


void draw_rect(int x, int y, int w, int h, char g)
{
    move(y, x);
    hline(g, w - 1);
    vline(g, h - 1);

    move(y + h - 1, x);
    hline(g, w);

    move(y, x + w - 1);
    vline(g, h - 1);

    return;
}


void clock_main(int border, int tfh, int random, int col)
{
    int off_x = 0;
    int off_y = 0;

    int update = 1;

    srand(time(NULL));

    int colour = col < 8 ? col : rand() % 8;
    init_pair(1, colour, colour);  // Digits

    curs_set(0);

    for (;;)
    {
        int digit_count = tfh ? 8 : 6;

        int width = WIDTH(digit_count);
        int height = HEIGHT;

        if (random)
        {
            if (--update == 0)
            {
                off_x = rand() % (COLS - width - 1);
                off_y = rand() % (LINES - height - 1);

                if (col == 8)
                {
                    colour = rand() % 8;
                    init_pair(1, colour, colour);
                }

                update = random;
            }
        }
        else
        {
            /* Center = (available_space - reserved_space) / 2 */
            off_x = (COLS - width) / 2;
            off_y = (LINES - height) / 2;
        }


        /* Clear screen */
        erase();

        if (border)
            /* Draw border + 1 space above and below, +3 spaces left and right */
            draw_rect(off_x - 3, off_y - 1, width + 6, height + 2, border);

        /* +3 to compensate for borders */
        if (tfh)
            draw_time_24h(off_x, off_y);
        else
            draw_time_kiloseconds(off_x, off_y);

        move(0,0);

        refresh();
        usleep(10000);
    }

    finish(0);

    return;
}

static void finish(int sig)
{
    endwin();
    exit(EXIT_SUCCESS);
}


float get_kiloseconds(void)
{
    struct tm *ltime;
    time_t now;

    time(&now);
    ltime = localtime(&now);

    return (float)(ltime->tm_hour * 3600 +
            ltime->tm_min * 60    +
            ltime->tm_sec) / 1000;
}


int draw_time_kiloseconds(int x, int y)
{
    char strks[7];
    int n, i, d;
    int xpos = x;
    int ypos = y;
    float ks = get_kiloseconds();

    snprintf(strks, 7, "%06.3f", ks);

    return draw_number(strks, x, y);
}


int draw_time_24h(int x, int y)
{
    char strtm[9];
    int n, i, d;
    int xpos = x;
    int ypos = y;

    time_t time_epoch = time(NULL);
    struct tm *local = localtime(&time_epoch);

    strftime(strtm, 9, "%H:%M:%S", local);

    return draw_number(strtm, x, y);
}


int draw_number(const char *num, int x, int y)
{
    int i;
    int written = 0;

    for (i = 0; i < strlen(num); ++i)
    {
        char glyph = num[i];

        switch (glyph)
        {
            case '.': glyph = 10; break;
            case ':': glyph = 11; break;
            default:  glyph = glyph - '0'; break;
        }

        if (glyph < 0 || glyph > DIGITS)
            continue;

        draw_digit(glyph, x, y);
        x += DIGIT_SPACING + DIGIT_WIDTH;

        ++written;
    }

    return written;
}


void draw_digit(int d, int x, int y)
{
    int w,h;
    int pos = 0;


    for (h = 0; h < DIGIT_HEIGHT; h++)
    {
        int col = 0;
        int xpos = x;

        for (w = 0; w < DIGIT_WIDTH; w++)
        {
            col = digits[d][h][w] != ' ';

            attron(COLOR_PAIR(col));
            mvprintw(pos + y, xpos++, "%c", digits[d][h][w]);
            attroff(COLOR_PAIR(col));
        }

        pos++;
    }

    return;
}
