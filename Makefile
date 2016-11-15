CC = gcc
CFLAGS = -I. -Wall -std=c89 -g -O0 -fprofile-arcs -ftest-coverage

DEPS = binaryheap.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: binaryheap.o test.o 
	gcc -o test binaryheap.o test.o $(CFLAGS)

clean:
	rm -rf *.o *~ test test.dySYM tes.gcno test.gcda
