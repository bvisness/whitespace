#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

#define HEAP_MIN_SIZE 256

//
// Private functions
//
void expandHeap(Heap* heap) {
    int newCapacity = heap->capacity * 2;
    HeapEntry* newEntries = malloc(newCapacity * sizeof(HeapEntry));
    int i;

    for (i = 0; i < heap->capacity; i++) {
        newEntries[i] = heap->entries[i];
    }

    free(heap->entries);
    heap->entries = newEntries;
    heap->capacity = newCapacity;
}

//
// Public functions
// 
Heap* createEmptyHeap(void) {
    Heap* result = malloc(sizeof(Heap));
    result->entries = malloc(HEAP_MIN_SIZE * sizeof(HeapEntry));
    result->capacity = HEAP_MIN_SIZE;
    result->numEntries = 0;

    return result;
}

HeapVal read(Heap* heap, int address) {
    int i;
    for (i = 0; i < heap->numEntries; i++) {
        if (heap->entries[i].address == address) {
            return heap->entries[i].val;
        }
    }

    fprintf(stderr, "No entry found for address %d in heap! Exiting...\n", address);
    exit(-1);
    return 0;
}

void store(Heap* heap, int address, HeapVal val) {
    int i;
    HeapEntry newEntry = {address, val};

    for (i = 0; i < heap->numEntries; i++) {
        if (heap->entries[i].address == address) {
            heap->entries[i].val = val;
            return;
        }
    }

    heap->numEntries++;
    if (heap->numEntries > heap->capacity) {
        expandHeap(heap);
    }

    heap->entries[heap->numEntries - 1] = newEntry;
}

void printHeap(Heap* heap) {
    int i;
    for (i = 0; i < heap->numEntries; i++) {
        printf("%d: %d\n", heap->entries[i].address, heap->entries[i].val);
    }
}

void freeHeap(Heap* heap) {
    free(heap->entries);
    free(heap);
}
