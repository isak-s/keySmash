CFLAGS=-Wall
LDFLAGS=-lncurses

CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -Isrc -Itests

SRC := $(wildcard src/*.c)
TESTS := $(wildcard tests/test_*.c)
UNITY := tests/unity.c

TESTOBJS := $(SRC:.c=.o) $(TESTS:.c=.o) $(UNITY:.c=.o)

all: src/main.c
	gcc -Wall src/main.c -o main -lncurses

test_runner: $(TESTOBJS)
	$(CC) $(CFLAGS) $^ -o $@

demo: demo.c
	gcc -Wall demo.c -o demo -lncurses

clean:
	rm -rf demo
