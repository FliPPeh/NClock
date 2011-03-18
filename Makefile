CC=cc
CFLAGS=-Wall -O2
LDFLAGS=-lncurses

BINARY=nclock

all: nclock

nclock: nclock.c digits.h

