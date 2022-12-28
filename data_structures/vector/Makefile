CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic 
DEBUGCFLAGS = -fsanitize=address -fsanitize=undefined
LIBS = -lm

.PHONY: all
all: vector maintest

test: all
	@rm -f a.out
	$(CC) $(DEBUGCFLAGS) $(LIBS) *.o 
	@./a.out

vector: vector.c
	$(CC) $(CFLAGS) -O2 -c $^

maintest: maintest.c
	$(CC) $(CFLAGS) -c $^
