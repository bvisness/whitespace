#pragma once

#include "linkedlist.h"

typedef int HeapVal;

typedef struct HeapEntryTag {
    int address;
    HeapVal val;
} HeapEntry;

typedef struct HeapTag {
    LinkedList* pList;
} Heap;

Heap* createEmptyHeap(void);

HeapVal read(Heap* heap, int address);

void store(Heap* heap, int address, HeapVal val);

void printHeap(Heap* heap);

void freeHeap(Heap* heap);
