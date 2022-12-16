CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic 
DEBUGCFLAGS = -fsanitize=address -fsanitize=undefined
LIBS = -lm

.PHONY: all
all: vector maintest

test: all
	$(CC) $(DEBUGCFLAGS) $(LIBS) *.o 
	@./a.out

vector: vector.c
	$(CC) $(CFLAGS) -c $^

maintest: maintest.c
	$(CC) $(CFLAGS) -c $^