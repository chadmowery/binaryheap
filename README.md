Binary Heap
=============

[![Build Status](https://travis-ci.org/chadmowery/binaryheap.svg?branch=master)](https://travis-ci.org/chadmowery/binaryheap) [![Coverage Status](https://coveralls.io/repos/github/chadmowery/binaryheap/badge.svg?branch=master)](https://coveralls.io/github/chadmowery/binaryheap?branch=master) [![License: LGPL v3](https://img.shields.io/badge/License-LGPL%20v3-blue.svg)](http://www.gnu.org/licenses/lgpl-3.0)
> A minimal C89 compatible binary heap implementation.

- [Examples](#examples)
- [Configuration](#configuration)
- [Runtimes](#runtimes)
- [Building](#building)
- [Dependencies](#dependencies)
- [Tests](#tests)
- [Contributing](#contributing)

## Examples

#### binary_heap_t
```c
// Implement your own compare function.
int min(void* a, void* b)
{
    return (*(int)a - *(int)b);
}

...

// Create a new 'min' heap
binary_heap_t* heap;
binary_heap_new(&heap, &min);

if (heap == NULL) {
    ...
}
else {
    ...
}

// Push elements on a heap
int foo = 10;
void* p_foo = &foo;
binary_heap_push(heap, p_foo);

int bar = 5;
void* p_bar = &bar;
binary_heap_push(heap, p_bar);

int baz = 1;
void* p_baz = &baz;
binary_heap_push(heap, p_baz);


// Peek on the top element of the heap
void* peek = NULL;
binary_heap_peek(heap, &peek);
if (peek != NULL) {
    ...
}
else {
    ...
}


// Pop elements from a heap
void* pop = NULL;
binary_heap_pop(heap, &pop);
if (pop != NULL) {
    ...
}
else {
    ...
}


// Destroy heap
binary_heap_destroy_free(heap);
```

## Configuration

Additional binary heap configuration is always optional and is done through a few macros defined at the top of `binaryheap.h`.

> NOTE: Binary heaps resize themselves by doubling current capacity and resize by default.

```c
// File binaryheap.h

// A value of 0 disallows heap resizing
#define BINARY_HEAP_RESIZE 1

// Change the initial heap capacity
#define BINARY_HEAP_INITIAL_CAPACITY 20
```

> You can also provide your own implementations for `malloc`, `free`, and `realloc` and avoid `<stdlib.h>`.

```c
// binaryheap.h

#ifndef BINARY_HEAP_ALLOC
#include <stdlib.h>
#define BINARY_HEAP_ALLOC(x)        malloc(x)
#define BINARY_HEAP_REALLOC(x, num) realloc(x, num)
#define BINARY_HEAP_FREE(x)         free(x)
```

```c
// yourfile.h

#define BiNARY_HEAP_ALLOC
#define BINARY_HEAP_ALLOC(x)        custom_alloc(x)
#define BINARY_HEAP_REALLOC(x, num) custom_realloc(x, num)
#define BINARY_HEAP_FREE(x)         custom_free(x)
```

## Runtimes
Operation | Complexity
------------ | -------------
peek | O(1)
push | O(log n)
pop | O(log n)
traverse | O(n)

## Building

To add binary_heap in your project, simply add binary_heap.h to your include directory, and binary_heap.c to your src directory.

```make
# Example Makefile
binaryheap.o:  binaryheap.c binaryheap.h
    gcc -Wall -c binaryheap.c
```

### Dependencies

- C89 compatible compiler (gcc, clang, etc...)

## Tests

To run the binary heap test suite simply run `make test` and the resulting test binary `./test`.

```make
# Test Makefile
CC = gcc
CFLAGS = -I. -Wall -std=c89

DEPS = binaryheap.h

%.o: %.c $(DEPS)
    $(CC) -c -o $@ $< $(CFLAGS)

test: binaryheap.o test.o 
    gcc -o test binaryheap.o test.o -I.

clean:
    rm -rf *.o *~ test
```

You should see output that looks like this:
```c
TESTS BEGIN
---------------------------------------------------------------------------

Running test: test_binary_heap_new()    OK
Running test: test_binary_heap_push()    OK
Running test: test_binary_heap_pop()    OK
Running test: test_binary_heap_peek()    OK
Running test: test_binary_heap_destroy()    OK
Running test: test_binary_heap_destroy_free()    OK

---------------------------------------------------------------------------
TESTS END
```

## Contributing

Contributions are welcome. If you have a feature request, or have found a bug, feel free to open a [new issue](https://github.com/chadmowery/binaryheap/issues/new).
