#pragma once

typedef int HeapVal;

typedef struct HeapEntryTag {
    int address;
    HeapVal val;
} HeapEntry;

typedef struct HeapTag {
    HeapEntry* entries;
    int capacity;
    int numEntries;
} Heap;

Heap* createEmptyHeap(void);

HeapVal read(Heap* heap, int address);

void store(Heap* heap, int address, HeapVal val);

void printHeap(Heap* heap);

void freeHeap(Heap* heap);
