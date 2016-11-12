CC = gcc
CFLAGS = -I. -Wall -std=c89 #-g

DEPS = binaryheap.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: binaryheap.o test.o 
	gcc -o test binaryheap.o test.o -I.

clean:
	rm -rf *.o *~ test
