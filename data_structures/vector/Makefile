CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic 

.PHONY: all
all: vector maintest

test: all
	$(CC) *.o
	@./a.out

vector: vector.c
	$(CC) $(CFLAGS) -c $^

maintest: maintest.c
	$(CC) $(CFLAGS) -c $^