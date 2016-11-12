/*
 * binaryheap.c
 * Copyright (C) 2016-2017 Chad Mowery
 *
 * 
 * binaryheap is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * binaryheap is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Collections-C.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "binaryheap.h"

/* Uncomment to disable asserts
 * #define NDEBUG */
#include <assert.h>

/* Forware declarations */
void bubble_up  (binary_heap_t* heap, size_t index);
void bubble_down(binary_heap_t* heap, size_t index);

/**
 * Binary heap object used to store heap state.
 */
struct binary_heap
{
    compare_f cmp;

    void** data;

    size_t size;
    size_t capacity;
};


/**
 * Construct a new binary heap object. Binary heaps can used as either
 * min or max heaps depending on the comparitor function you provide.
 * @param[out] out  The out pointer to hold the new binary_heap_t object
 * @param[in]  cmp  The comparitor function pointer
 */
void binary_heap_new(binary_heap_t** out, compare_f cmp)
{
    assert(cmp);

    binary_heap_t* heap = (binary_heap_t*)BINARY_HEAP_ALLOC(sizeof(binary_heap_t));

    assert(heap);
    if (!heap)
        return;

    heap->data = BINARY_HEAP_ALLOC(BINARY_HEAP_INITIAL_CAPACITY * sizeof(void*));

    assert(heap->data);
    if (!heap->data) {
        binary_heap_destroy(heap);
        return;
    }

    heap->cmp = cmp;
    heap->size   = 0;
    heap->capacity = BINARY_HEAP_INITIAL_CAPACITY;

    *out = heap;
}

/**
 * Destroy a binary heap object. This operation will free internal heap state
 * but will NOT free any heap data (void*).
 * @param[in] heap  The binary heap to destroy
 */
void binary_heap_destroy(binary_heap_t* heap)
{
    assert(heap);

    BINARY_HEAP_FREE(heap->data);
    BINARY_HEAP_FREE(heap);
}

/**
 * Destroy a binary heap object. This operation will free internal heap state
 * AND free all heap data (void*).
 * @param[in] heap  The binary heap to destroy
 */
void binary_heap_destroy_free(binary_heap_t* heap)
{
    assert(heap);

    size_t i;
    for (i = 0; i < heap->size; ++i)
        BINARY_HEAP_FREE(heap->data[i]);

    binary_heap_destroy(heap);
}

/**
 * Get a binary heap size.
 * O(1)
 * @param[in] heap  The binary heap
 * @return          The binary heap size
 */
size_t binary_heap_size(binary_heap_t* heap)
{
    assert(heap);
    return (heap->size);
}

/**
 * Get a binary heap capacity.
 * O(1)
 * @param[in] heap The binary heap 
 * @return         The binary heap capacity
 */
size_t binary_heap_capacity(binary_heap_t* heap)
{
    assert(heap);
    return (heap->capacity);
}

/**
 * Traverse the entire binary heap in array order.
 * O(n)
 * @param[in] heap  The binary heap to traverse
 * @param[in] visit The visitor function pointer
 */
void binary_heap_traverse(binary_heap_t* heap, visit_f visit)
{
    assert(heap);
    assert(visit);

    if (!heap->size)
        return;

    size_t i;
    for (i = 0; i < heap->size; ++i)
        visit(*(heap->data + i));
}

/**
 * Add a new data element to a binary heap.
 * O(logn)
 * @param[in] heap  The binary heap
 * @param[in] data  The data element to add
 * @return          1 if the add is successful, otherwise 0
 */
int binary_heap_push(binary_heap_t* heap, void* data)
{
    assert(heap);

    size_t MAX = (size_t) - 1;

    /* Overflow */
    if (heap->size + 1 == MAX)
        return 0;

    /* If we ran out of space attempt to grab some more */
    if (heap->size == heap->capacity && heap->capacity << 1 < MAX)
    {
        if (!BINARY_HEAP_RESIZE)
            return 0;

        heap->capacity <<= 1;

        void* new_data = BINARY_HEAP_REALLOC(heap->data, heap->capacity * sizeof(void*));

        assert(new_data);
        if (!new_data) {
            /* When realloc fails, our entire block of memory is invalidated so 
             * unfortunately, we must free it along with the entire heap */
            binary_heap_destroy_free(heap);
            return 0;
        }

        heap->data = new_data;
    }

    /* Do the add then bubble up */
    heap->data[heap->size++] = data;
    bubble_up(heap, heap->size - 1);

    return 1;
}

/**
 * Remove the top-most element from a binary heap. The top-most
 * element is guaranteed to be the smallest/largest in the heap
 * based on the user comparitor function. Removing elements from
 * binary heaps reduces their size by 1, but capacity remains unchanged.
 * O(logn)
 * @param[in]  heap The binary heap
 * @param[out] out  The out ptr to the removed data element
 */
void binary_heap_pop(binary_heap_t* heap, void** out)
{
    assert(heap);

    if (heap->size == 0)
        return;

    *out = *heap->data;

    /* Take the last element in the heap and bubble it down */
    if (--heap->size > 0) {
        *heap->data = heap->data[heap->size];
        bubble_down(heap, 0);
    }
}

/**
 * Peek at the top-most data element in a binary heap. The caller
 * should NOT modify it's data as it may invalidate the state of
 * the heap.
 * O(1)
 * @param[in]  heap    The binary heap
 * @param[out] out     The out ptr to the top-most element if exists, otherwise NULL
 */
void binary_heap_peek(binary_heap_t* heap, void** out)
{
    assert(heap);
    *out = (heap->size > 0 ? *heap->data : NULL);
}


/* Internal Helpers */

/**
 * Recursively bubbles up data elements in a heap based on the user
 * comparitor function (min/max). The result of this operation is a
 * binary heap with its top-most element being the smallest/largest
 * in the heap.
 * @param[in] heap  The binary heap
 * @param[in] index The current heap index
 */
void bubble_up(binary_heap_t* heap, size_t index)
{
    assert(heap);
    assert(index >= 0);
    assert(index < heap->size);

    /* If we are at the root level, we are sorted */
    if (index == 0)
        return;

    size_t parent_index = (index - 1) / 2;

    if (heap->cmp(heap->data[index], heap->data[parent_index]) < 0) {
        void* tmp = heap->data[index];
        heap->data[index] = heap->data[parent_index];
        heap->data[parent_index] = tmp;

        bubble_up(heap, parent_index);
    }
}

/**
 * Recursively bubbles down data elements in a heap based on the user
 * comparitor function (min/max). The result of this operation is a
 * binary heap with its top-most element being the smallest/largest
 * in the heap.
 * @param[in] heap  The binary heap
 * @param[in] index The current heap index
 */
void bubble_down(binary_heap_t* heap, size_t index)
{
    assert(heap);
    assert(index >= 0);
    assert(index < heap->size);

    /* We are at the bottom of the heap, we are sorted */
    if (index == heap->size - 1)
        return;

    size_t swp   = index;
    size_t left  = (index << 1) + 1;
    size_t right = (index << 1) + 2;

    /* If this element compares less than its left child or right children swap it */
    if (left < heap->size && heap->cmp(heap->data[left], heap->data[swp]) < 0)
        swp = left;
    if (right < heap->size && heap->cmp(heap->data[right], heap->data[swp]) < 0)
        swp = right;

    /* Perform the actual swap, and continue to bubble down */
    if (swp != index) {
        void* tmp = heap->data[index];
        heap->data[index] = heap->data[swp];
        heap->data[swp] = tmp;

        bubble_down(heap, swp);
    }
}
