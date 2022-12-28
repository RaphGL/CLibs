CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic 
DEBUGCFLAGS = -fsanitize=address -fsanitize=undefined

.PHONY: all
all: bintree maintest

test: all
	$(CC) $(DEBUGCFLAGS) $(LIBS) *.o 
	@./a.out

bintree: bintree.c
	$(CC) $(CFLAGS) -O2 -c $^

maintest: maintest.c
	$(CC) $(CFLAGS) -c $^
