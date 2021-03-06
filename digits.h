#ifndef DIGITS_H
#define DIGITS_H

#define WIDTH(n) (((n - 1) * DIGIT_SPACING) + ((n) * DIGIT_WIDTH))
#define HEIGHT DIGIT_HEIGHT

#define DIGIT_WIDTH    5
#define DIGIT_HEIGHT   5
#define DIGIT_SPACING  1

enum
{
    DIGIT_DOT = 10,
    DIGIT_COMMA,
    DIGIT_COLON,
    DIGIT_MINUS,
    DIGIT_PLUS,
    DIGIT_SLASH,
    DIGIT_EXCLAM,
    DIGIT_QUESTION,
    DIGIT_SPACE,
    DIGIT_A, // Only need A, others are offset
};

// 10 numbers, 6 punctuation, 26 letters
#define DIGITS (10+9+26)
char digits[DIGITS][DIGIT_HEIGHT][DIGIT_WIDTH + 1] = {
    {
        " ### ",
        "#   #",
        "#   #",
        "#   #",
        " ### "
    },
    {
        "  #  ",
        " ##  ",
        "  #  ",
        "  #  ",
        " ### "
    },
    {
        " ### ",
        "#   #",
        "  ## ",
        " #   ",
        "#####"
    },
    {
        " ### ",
        "#   #",
        "  ## ",
        "#   #",
        " ### "
    },
    {
        "#   #",
        "#   #",
        " ### ",
        "    #",
        "    #"
    },
    {
        "#####",
        "#    ",
        " ### ",
        "    #",
        "#### "
    },
    {
        " ### ",
        "#    ",
        "#### ",
        "#   #",
        " ### "
    },
    {
        " ####",
        "    #",
        "   # ",
        "   # ",
        "   # "
    },
    {
        " ### ",
        "#   #",
        " ### ",
        "#   #",
        " ### "
    },
    {
        " ### ",
        "#   #",
        " ####",
        "    #",
        " ### "
    },
    { // '.'
        "     ",
        "     ",
        "     ",
        "     ",
        "  #  "
    },
    {
        "     ",
        "     ",
        "     ",
        "  #  ",
        " #   "
    },
    { // ':'
        "     ",
        "  #  ",
        "     ",
        "     ",
        "  #  "
    },
    { // '-'
        "     ",
        "     ",
        " ### ",
        "     ",
        "     "
    },
    { // '+'
        "     ",
        "  #  ",
        " ### ",
        "  #  ",
        "     "
    }, 
    { // '/'
        "    #",
        "   # ",
        "  #  ",
        " #   ",
        "#    "
    }, 
    { // '!'
        "  #  ",
        "  #  ",
        "  #  ",
        "     ",
        "  #  "
    }, 
    { // '?'
        "  ## ",
        "    #",
        "  ## ",
        "     ",
        "  #  "
    },
    { // ' '
        "     ",
        "     ",
        "     ",
        "     ",
        "     "
    },
    { // ' '
        " ### ",
        "#   #",
        "#####",
        "#   #",
        "#   #"
    },
    {
        "#### ",
        "#   #",
        "#### ",
        "#   #",
        "#### "
    },
    {
        " ####",
        "#    ",
        "#    ",
        "#    ",
        " ####"
    },
    {
        "#### ",
        "#   #",
        "#   #",
        "#   #",
        "#### "
    },
    {
        "#####",
        "#    ",
        "#####",
        "#    ",
        "#####"
    },
    {
        "#####",
        "#    ",
        "#### ",
        "#    ",
        "#    "
    },
    {
        " ### ",
        "#    ",
        "# ## ",
        "#   #",
        " ### "
    },
    {
        "#   #",
        "#   #",
        "#####",
        "#   #",
        "#   #"
    },
    {
        "  #  ",
        "  #  ",
        "  #  ",
        "  #  ",
        "  #  "
    },
    {
        "   # ",
        "   # ",
        "   # ",
        "#  # ",
        " ##  "
    },
    {
        "#  # ",
        "# #  ",
        "##   ",
        "# #  ",
        "#  # "
    },
    {
        "#    ",
        "#    ",
        "#    ",
        "#    ",
        "#####"
    },
    {
        "#   #",
        "## ##",
        "# # #",
        "#   #",
        "#   #"
    },
    {
        "#   #",
        "##  #",
        "# # #",
        "#  ##",
        "#   #"
    },
    {
        " ### ",
        "#   #",
        "#   #",
        "#   #",
        " ### "
    },
    {
        "#### ",
        "#   #",
        "#### ",
        "#    ",
        "#    "
    },
    {
        " ### ",
        "#   #",
        "#   #",
        "#  # ",
        " ## #"
    },
    {
        "#### ",
        "#   #",
        "#### ",
        "#   #",
        "#   #"
    },
    {
        " ####",
        "#    ",
        " ### ",
        "    #",
        "#### "
    },
    {
        "#####",
        "  #  ",
        "  #  ",
        "  #  ",
        "  #  "
    },
    {
        "#   #",
        "#   #",
        "#   #",
        "#   #",
        " ### "
    },
    {
        "#   #",
        "#   #",
        " # # ",
        " # # ",
        "  #  "
    },
    {
        "#   #",
        "#   #",
        "# # #",
        "# # #",
        " # # "
    },
    {
        "#   #",
        " # # ",
        "  #  ",
        " # # ",
        "#   #"
    },
    {
        "#   #",
        "#   #",
        " ### ",
        "  #  ",
        "  #  "
    },
    {
        "#####",
        "   # ",
        "  #  ",
        " #   ",
        "#####"
    }


















};


#endif

