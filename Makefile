CC=cc
CCFLAGS=-Wall -O2
LDFLAGS=-lncurses

BINARY=nclock

all: nclock

nclock: nclock.c

