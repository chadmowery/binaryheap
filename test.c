/*
 * test.c
 * Copyleft (C) 2016-2017 Chad Mowery
 *
 * 
 * test.c is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * test.c is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with binaryheap.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "binaryheap.h"

#include <assert.h>
#include <stdio.h>

/* NOTE: All tests assume minheap comparisons */

/* Test comparitor */
int min(void* a, void* b)
{
    assert(a && "Expected non-NULL element in comparitor");
    assert(b && "Expected non-NULL element in comparitor");

    return (*(int*)a - *(int*)b);
}

/* Test helper */
void* elem_new(int value)
{
    int* p = (int*)malloc(sizeof(int));

    assert(p && "Failed to malloc a new element");

    *p = value;
    return ((void*)p);
}

void test_binary_heap_new()
{
    binary_heap_t* heap;
    binary_heap_new(&heap, &min);
    
    assert(heap && "Failed to construct new binary_heap_t");
    void* top = NULL;
    binary_heap_peek(heap, &top);
    assert(top == NULL && "Expected peek value [NULL]");
    assert(binary_heap_size(heap) == 0 && "Expected initial heap size of 0");
    assert(binary_heap_capacity(heap) == BINARY_HEAP_INITIAL_CAPACITY && "Expected initial heap capacity of BINARY_HEAP_INITIAL_CAPACITY [20]");

    binary_heap_destroy_free(heap);
}

void test_binary_heap_resize()
{
    binary_heap_t* heap;
    binary_heap_new(&heap, &min);
    
    assert(heap && "Failed to construct new binary_heap_t");
    void* top = NULL;
    binary_heap_peek(heap, &top);
    assert(top == NULL && "Expected peek value [NULL]");
    assert(binary_heap_size(heap) == 0 && "Expected initial heap size of 0");

    assert(binary_heap_capacity(heap) == BINARY_HEAP_INITIAL_CAPACITY && "Expected initial heap capacity of BINARY_HEAP_INITIAL_CAPACITY [20]");

    size_t i;
    for (i = 0; i < BINARY_HEAP_INITIAL_CAPACITY + 1; ++i)
        assert(1 == binary_heap_push(heap, elem_new((int)i)) && "Expected successful heap push");

    assert(binary_heap_capacity(heap) == BINARY_HEAP_INITIAL_CAPACITY * 2 && "Expected binary heap to resize to BINARY_HEAP_INITIAL_CAPACITY * 2 [40]");

    binary_heap_destroy_free(heap);
}

void test_binary_heap_push()
{
    binary_heap_t* heap;
    binary_heap_new(&heap, &min);

    void* top = NULL;
    
    binary_heap_peek(heap, &top);
    assert(top == NULL && "Expected peek value [NULL]");

    binary_heap_push(heap, elem_new(10));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 10 && "Expected peek value [10]");
    assert(binary_heap_size(heap) == 1 && "Expected heap size of [1]");
    assert(binary_heap_capacity(heap) == BINARY_HEAP_INITIAL_CAPACITY && "Expected heap capacity of BINARY_HEAP_INITIAL_CAPACITY [20]");

    binary_heap_push(heap, elem_new(4));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 4 && "Expected peek value [4]");
    assert(binary_heap_size(heap) == 2 && "Expected heap size of [2]");
    assert(binary_heap_capacity(heap) == BINARY_HEAP_INITIAL_CAPACITY && "Expected heap capacity of BINARY_HEAP_INITIAL_CAPACITY [20]");

    binary_heap_push(heap, elem_new(7));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 4 && "Expected peek value [4]");
    assert(binary_heap_size(heap) == 3 && "Expected heap size of [3]");
    assert(binary_heap_capacity(heap) == BINARY_HEAP_INITIAL_CAPACITY && "Expected heap capacity of BINARY_HEAP_INITIAL_CAPACITY [20]");

    binary_heap_push(heap, elem_new(9));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 4 && "Expected peek value [4]");
    assert(binary_heap_size(heap) == 4 && "Expected heap size of [4]");
    assert(binary_heap_capacity(heap) == BINARY_HEAP_INITIAL_CAPACITY && "Expected heap capacity of BINARY_HEAP_INITIAL_CAPACITY [20]");

    binary_heap_push(heap, elem_new(8));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 4 && "Expected peek value [4]");
    assert(binary_heap_size(heap) == 5 && "Expected heap size of [5]");
    assert(binary_heap_capacity(heap) == BINARY_HEAP_INITIAL_CAPACITY && "Expected heap capacity of BINARY_HEAP_INITIAL_CAPACITY [20]");

    binary_heap_push(heap, elem_new(6));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 4 && "Expected peek value [4]");
    assert(binary_heap_size(heap) == 6 && "Expected heap size of [6]");
    assert(binary_heap_capacity(heap) == BINARY_HEAP_INITIAL_CAPACITY && "Expected heap capacity of BINARY_HEAP_INITIAL_CAPACITY [20]");

    binary_heap_push(heap, elem_new(2));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 2 && "Expected peek value [2]");
    assert(binary_heap_size(heap) == 7 && "Expected heap size of [7]");
    assert(binary_heap_capacity(heap) == BINARY_HEAP_INITIAL_CAPACITY && "Expected heap capacity of BINARY_HEAP_INITIAL_CAPACITY [20]");

    binary_heap_push(heap, elem_new(3));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 2 && "Expected peek value [2]");
    assert(binary_heap_size(heap) == 8 && "Expected heap size of [8]");
    assert(binary_heap_capacity(heap) == BINARY_HEAP_INITIAL_CAPACITY && "Expected heap capacity of BINARY_HEAP_INITIAL_CAPACITY [20]");

    binary_heap_push(heap, elem_new(5));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 2 && "Expected peek value [2]");
    assert(binary_heap_size(heap) == 9 && "Expected heap size of [9]");
    assert(binary_heap_capacity(heap) == BINARY_HEAP_INITIAL_CAPACITY && "Expected heap capacity of BINARY_HEAP_INITIAL_CAPACITY [20]");

    binary_heap_push(heap, elem_new(1));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 1 && "Expected peek value [1]");
    assert(binary_heap_size(heap) == 10 && "Expected heap size of [10]");
    assert(binary_heap_capacity(heap) == BINARY_HEAP_INITIAL_CAPACITY && "Expected heap capacity of BINARY_HEAP_INITIAL_CAPACITY [20]");

    binary_heap_destroy_free(heap);
}

void test_binary_heap_pop()
{
    binary_heap_t* heap;
    binary_heap_new(&heap, &min);

    /* Generate a heap */
    binary_heap_push(heap, elem_new(10));
    binary_heap_push(heap, elem_new(4));
    binary_heap_push(heap, elem_new(7));
    binary_heap_push(heap, elem_new(9));
    binary_heap_push(heap, elem_new(8));
    binary_heap_push(heap, elem_new(6));
    binary_heap_push(heap, elem_new(2));
    binary_heap_push(heap, elem_new(3));
    binary_heap_push(heap, elem_new(5));
    binary_heap_push(heap, elem_new(1));

    void* top = NULL;

    /* Tests */
    binary_heap_pop(heap, &top);
    assert(*(int*)top == 1 && "Expected pop value [1]");
    free(top);
    assert(binary_heap_size(heap) == 9 && "Expected heap size of [9]");

    binary_heap_pop(heap, &top);
    assert(*(int*)top == 2 && "Expected pop value [2]");
    free(top);
    assert(binary_heap_size(heap) == 8 && "Expected heap size of [8]");

    binary_heap_pop(heap, &top);
    assert(*(int*)top == 3 && "Expected pop value [3]");
    free(top);
    assert(binary_heap_size(heap) == 7 && "Expected heap size of [7]");

    binary_heap_pop(heap, &top);
    assert(*(int*)top == 4 && "Expected pop value [4]");
    free(top);
    assert(binary_heap_size(heap) == 6 && "Expected heap size of [6]");

    binary_heap_pop(heap, &top);
    assert(*(int*)top == 5 && "Expected pop value [5]");
    free(top);
    assert(binary_heap_size(heap) == 5 && "Expected heap size of [5]");

    binary_heap_pop(heap, &top);
    assert(*(int*)top == 6 && "Expected pop value [6]");
    free(top);
    assert(binary_heap_size(heap) == 4 && "Expected heap size of [4]");

    binary_heap_pop(heap, &top);
    assert(*(int*)top == 7 && "Expected pop value [7]");
    free(top);
    assert(binary_heap_size(heap) == 3 && "Expected heap size of [3]");

    binary_heap_pop(heap, &top);
    assert(*(int*)top == 8 && "Expected pop value [8]");
    free(top);
    assert(binary_heap_size(heap) == 2 && "Expected heap size of [2]");

    binary_heap_pop(heap, &top);
    assert(*(int*)top == 9 && "Expected pop value [9]");
    free(top);
    assert(binary_heap_size(heap) == 1 && "Expected heap size of [1]");

    binary_heap_pop(heap, &top);
    assert(*(int*)top == 10 && "Expected pop value [10]");
    free(top);
    assert(binary_heap_size(heap) == 0 && "Expected heap size of [0]");

    top = NULL;
    binary_heap_pop(heap, &top);
    assert(top == NULL && "Expected pop value [NULL]");

    binary_heap_destroy_free(heap);
}

void test_binary_heap_peek()
{
    binary_heap_t* heap;
    binary_heap_new(&heap, &min);

    void* top = NULL;
    
    binary_heap_peek(heap, &top);
    assert(top == NULL && "Expected peek value [NULL]");
    
    binary_heap_push(heap, elem_new(10));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 10 && "Expected peek value [10]");

    binary_heap_push(heap, elem_new(4));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 4 && "Expected peek value [4]");

    binary_heap_push(heap, elem_new(7));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 4 && "Expected peek value [4]");

    binary_heap_push(heap, elem_new(9));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 4 && "Expected peek value [4]");

    binary_heap_push(heap, elem_new(8));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 4 && "Expected peek value [4]");

    binary_heap_push(heap, elem_new(6));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 4 && "Expected peek value [4]");

    binary_heap_push(heap, elem_new(2));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 2 && "Expected peek value [2]");

    binary_heap_push(heap, elem_new(3));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 2 && "Expected peek value [2]");

    binary_heap_push(heap, elem_new(5));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 2 && "Expected peek value [2]");

    binary_heap_push(heap, elem_new(1));
    binary_heap_peek(heap, &top);
    assert(*(int*)top == 1 && "Expected peek value [1]");

    binary_heap_destroy_free(heap);
}

/* Test visitor */
int idx = 0;
int expected_traverse[10] = { 1, 2, 4, 5, 3, 7, 6, 10, 8, 9 };
void visit(void* elem)
{
    assert(elem && "Expected non-NULL element in visitor");
    assert(idx < 10);

    assert(*(int*)elem == expected_traverse[idx++]);
}

void test_binary_heap_traverse()
{
    binary_heap_t* heap;
    binary_heap_new(&heap, &min);

    binary_heap_push(heap, elem_new(10));
    binary_heap_push(heap, elem_new(4));
    binary_heap_push(heap, elem_new(7));
    binary_heap_push(heap, elem_new(9));
    binary_heap_push(heap, elem_new(8));
    binary_heap_push(heap, elem_new(6));
    binary_heap_push(heap, elem_new(2));
    binary_heap_push(heap, elem_new(3));
    binary_heap_push(heap, elem_new(5));
    binary_heap_push(heap, elem_new(1));

    idx = 0;
    binary_heap_traverse(heap, &visit);

    binary_heap_destroy_free(heap);
}

void test_binary_heap_destroy()
{
    binary_heap_t* heap;
    binary_heap_new(&heap, &min);

    void* e0 = elem_new(10);
    void* e1 = elem_new(4);
    void* e2 = elem_new(7);
    void* e3 = elem_new(9);
    void* e4 = elem_new(8);
    void* e5 = elem_new(6);
    void* e6 = elem_new(2);
    void* e7 = elem_new(3);
    void* e8 = elem_new(5);
    void* e9 = elem_new(1);

    /* Generate a heap */
    binary_heap_push(heap, e0);
    binary_heap_push(heap, e1);
    binary_heap_push(heap, e2);
    binary_heap_push(heap, e3);
    binary_heap_push(heap, e4);
    binary_heap_push(heap, e5);
    binary_heap_push(heap, e6);
    binary_heap_push(heap, e7);
    binary_heap_push(heap, e8);
    binary_heap_push(heap, e9);

    binary_heap_destroy(heap);

    assert(*(int*)e0 == 10 && "Expected element value [10]");
    assert(*(int*)e1 == 4 && "Expected element value [4]");
    assert(*(int*)e2 == 7 && "Expected element value [7]");
    assert(*(int*)e3 == 9 && "Expected element value [9]");
    assert(*(int*)e4 == 8 && "Expected element value [8]");
    assert(*(int*)e5 == 6 && "Expected element value [6]");
    assert(*(int*)e6 == 2 && "Expected element value [2]");
    assert(*(int*)e7 == 3 && "Expected element value [3]");
    assert(*(int*)e8 == 5 && "Expected element value [5]");
    assert(*(int*)e9 == 1 && "Expected element value [1]");

    free(e0);
    free(e1);
    free(e2);
    free(e3);
    free(e4);
    free(e5);
    free(e6);
    free(e7);
    free(e8);
    free(e9);
}

void test_binary_heap_destroy_free()
{
    binary_heap_t* heap;
    binary_heap_new(&heap, &min);

    void* e0 = elem_new(10);
    void* e1 = elem_new(4);
    void* e2 = elem_new(7);
    void* e3 = elem_new(9);
    void* e4 = elem_new(8);
    void* e5 = elem_new(6);
    void* e6 = elem_new(2);
    void* e7 = elem_new(3);
    void* e8 = elem_new(5);
    void* e9 = elem_new(1);

    /* Generate a heap */
    binary_heap_push(heap, e0);
    binary_heap_push(heap, e1);
    binary_heap_push(heap, e2);
    binary_heap_push(heap, e3);
    binary_heap_push(heap, e4);
    binary_heap_push(heap, e5);
    binary_heap_push(heap, e6);
    binary_heap_push(heap, e7);
    binary_heap_push(heap, e8);
    binary_heap_push(heap, e9);

    binary_heap_destroy_free(heap);
}


/* Run all the tests! */
int main(void)
{
    printf("\nTESTS BEGIN\n");
    printf("---------------------------------------------------------------------------\n\n");

    printf("Running test: test_binary_heap_new()");
    test_binary_heap_new();
    printf("    OK\n");

    printf("Running test: test_binary_heap_resize()");
    test_binary_heap_resize();
    printf("    OK\n");

    printf("Running test: test_binary_heap_push()");
    test_binary_heap_push();
    printf("    OK\n");

    printf("Running test: test_binary_heap_pop()");
    test_binary_heap_pop();
    printf("    OK\n");

    printf("Running test: test_binary_heap_peek()");
    test_binary_heap_peek();
    printf("    OK\n");

    printf("Running test: test_binary_heap_traverse()");
    test_binary_heap_traverse();
    printf("    OK\n");

    printf("Running test: test_binary_heap_destroy()");
    test_binary_heap_destroy();
    printf("    OK\n");

    printf("Running test: test_binary_heap_destroy_free()");
    test_binary_heap_destroy_free();
    printf("    OK\n");

    printf("\n---------------------------------------------------------------------------\n");
    printf("TESTS END\n");
    return 0;
}
