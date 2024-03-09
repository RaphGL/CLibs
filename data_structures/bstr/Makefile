CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic
DEBUGCFLAGS = -g -fsanitize=address -fsanitize=undefined

.PHONY: all
all: test bstr

test: bstr.c maintest.c
	@$(CC) $(DEBUGCFLAGS) *.c
	@./a.out

bstr: bstr.c
	@$(CC) $(CFLAGS) -O2 -c $^
	@echo "Library compiled into $(subst .c,.o,$^)"
