/*
 * binaryheap.h
 * Copyright (C) 2016-2017 Chad Mowery
 *
 * 
 * binaryheap.h is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * binaryheap.h is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with binaryheap.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * TODO:
 * - Needs benchmarking
 * - Implement better traversal functionality
 */


/* Override to change heap resizing. Heaps resize doubles capacity. */
#ifndef BINARY_HEAP_RESIZE
#define BINARY_HEAP_RESIZE 1
#endif

/* Starting heap size */
#ifndef BINARY_HEAP_INITIAL_CAPACITY
#define BINARY_HEAP_INITIAL_CAPACITY 20
#endif

/* Override to avoid malloc */
#ifndef BINARY_HEAP_ALLOC
#include <stdlib.h>
#define BINARY_HEAP_ALLOC(x)        malloc(x)
#define BINARY_HEAP_REALLOC(x, num) realloc(x, num)
#define BINARY_HEAP_FREE(x)         free(x)
#endif

/* Forward declare */
typedef struct binary_heap binary_heap_t;

/* Comparitor function pointer */
typedef int (*compare_f)(void*, void*);
/* Visitor function pointer */
typedef void (*visit_f)(void*);


void 	binary_heap_new           (binary_heap_t** out, compare_f cmp);

void 	binary_heap_destroy       (binary_heap_t* heap);
void 	binary_heap_destroy_free  (binary_heap_t* heap);

size_t	binary_heap_size          (binary_heap_t* heap);
size_t 	binary_heap_capacity      (binary_heap_t* heap);

void 	binary_heap_traverse      (binary_heap_t* heap, visit_f visit);

int 	binary_heap_push          (binary_heap_t* heap, void* data);
void 	binary_heap_pop           (binary_heap_t* heap, void** out);
void 	binary_heap_peek          (binary_heap_t* heap, void** out);

#ifdef __cplusplus
}
#endif

#endif /* BINARY_HEAP_H */
