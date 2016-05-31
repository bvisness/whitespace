#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

#define HEAP_MIN_SIZE 256

//
// Private functions
//
void* addressDataFunc(LinkedListNode* node) {
    HeapEntry* entry = node->data;
    return (void*) entry->address;
}

//
// Public functions
// 
Heap* createEmptyHeap(void) {
    Heap* result = malloc(sizeof(Heap));
    result->pList = newList();
    result->pList->dataCanBeFreed = 1;

    return result;
}

HeapVal read(Heap* heap, int address) {
    HeapEntry* entry;
    LinkedListFindResult findResult = find(heap->pList, (void*) address, &addressDataFunc);
    if (findResult.pNode == NULL) {
        fprintf(stderr, "No entry found for address %d in heap! Exiting...\n", address);
        exit(-1);
        return 0;
    }

    entry = findResult.pNode->data;
    return entry->val;
}

void store(Heap* heap, int address, HeapVal val) {
    HeapEntry* foundEntry;
    LinkedListFindResult findResult = find(heap->pList, (void*) address, &addressDataFunc);
    if (findResult.pNode == NULL) {
        HeapEntry* newEntry = malloc(sizeof(HeapEntry));
        newEntry->address = address;
        newEntry->val = val;
        
        addAtHead(heap->pList, newEntry);
        return;
    }

    foundEntry = findResult.pNode->data;
    foundEntry->val = val;
}

void printHeap(Heap* heap) {
    int i;
    for (i = 0; i < heap->pList->length; i++) {
        LinkedListNode* node = get(heap->pList, i);
        HeapEntry* entry = node->data;
        printf("%d: %d\n", entry->address, entry->val);
    }
}

void freeHeap(Heap* heap) {
    freeList(heap->pList);
    free(heap);
}
