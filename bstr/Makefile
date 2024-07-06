CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic
DEBUGCFLAGS = -g -fsanitize=address -fsanitize=undefined

.PHONY: all test
all: test bstr

test: bstr.c maintest.c
	@$(CC) $(CFLAGS) $(DEBUGCFLAGS) *.c
	@./a.out

bstr: bstr.c
	@$(CC) $(CFLAGS) -O2 -c $^
	@echo "Library compiled into $(subst .c,.o,$^)"
