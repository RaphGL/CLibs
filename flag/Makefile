CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic
DEBUGCFLAGS = -fsanitize=address,leak,undefined -g
LIBS = -lm

.PHONY: all clean
all: flag maintest

clean:
	rm *.o

test: maintest.c flag.c ../vec/vector.c ../bstr/bstr.c
	@rm -f a.out
	$(CC) $(DEBUGCFLAGS) $(LIBS) $^ 
	@./a.out

flag: flag.c ../vec/vector.c ../bstr/bstr.c
	$(CC) $(CFLAGS) -O2 -c $^

maintest: maintest.c
	$(CC) $(CFLAGS) -c $^
