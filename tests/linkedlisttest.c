#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../linkedlist.h"

//
// Utilities
//
void printNumberList(LinkedList* pList) {
    int i;

    printf("Length %d, Head %p, Tail %p\n", pList->length, pList->pHead, pList->pTail);
    if (pList->length > 0) {
        printf("%d", (int) get(pList, 0)->data);
    }
    for (i = 1; i < pList->length; i++) {
        printf(", %d", (int) get(pList, i)->data);
    }

    printf("\n");
}

void* plainDataFunc(LinkedListNode* node) {
    return node->data;
}

//
// Tests
//
void testNewList() {
    printf("Testing new list\n");

    LinkedList* list = newList();

    assert(list->length == 0);
    assert(list->pHead == NULL);
    assert(list->pTail == NULL);
}

void testGet() {
    LinkedList* list;
    LinkedListNode* node;

    printf("Testing get\n");

    list = newList();
    addAtTail(list, (void*) 1);
    addAtTail(list, (void*) 2);
    printNumberList(list);

    node = get(list, 0);

    assert(node != NULL);
    assert((int) node->data == 1);

    node = get(list, 1);

    assert(node != NULL);
    assert((int) node->data == 2);

    node = get(list, -1);

    assert(node == NULL);

    node = get(list, 2);

    assert(node == NULL);
}

void testAddAtHead() {
    LinkedListNode* node;

    printf("Testing add at head\n");

    LinkedList* list = newList();
    printNumberList(list);

    node = addAtHead(list, (void*) 1);
    printNumberList(list);

    assert(list->length == 1);
    assert(list->pHead != NULL);
    assert(list->pHead == node);
    assert(list->pHead == list->pTail);

    node = addAtHead(list, (void*) 2);
    printNumberList(list);

    assert(list->length == 2);
    assert(list->pHead == node);
    assert(list->pHead != list->pTail);
}

void testAddAtTail() {
    printf("Testing add at tail\n");

    LinkedList* list = newList();
    printNumberList(list);

    addAtTail(list, (void*) 1);
    printNumberList(list);

    assert(list->length == 1);
    assert(list->pHead != NULL);
    assert(list->pHead == list->pTail);

    addAtTail(list, (void*) 2);
    printNumberList(list);

    assert(list->length == 2);
    assert(list->pHead != list->pTail);
}

void testAddAtIndex() {
    LinkedList* list;
    LinkedListNode* node;

    printf("Testing add at index\n");

    list = newList();
    printNumberList(list);

    node = addAtIndex(list, (void*) 1, 0);
    printNumberList(list);
    
    assert(list->length == 1);
    assert(list->pHead != NULL);
    assert(list->pHead == node);
    assert(list->pHead == list->pTail);
    assert(node->pBefore == NULL);
    assert(node->pAfter == NULL);

    node = addAtIndex(list, (void*) 2, 1);
    printNumberList(list);
    
    assert(list->length == 2);
    assert(list->pTail != NULL);
    assert(list->pTail == node);
    assert(node->pBefore == list->pHead);
    assert(node->pAfter == NULL);

    node = addAtIndex(list, (void*) 3, 1);
    printNumberList(list);
    
    assert(list->length == 3);
    assert(list->pHead != node);
    assert(list->pTail != node);
    assert(node->pBefore == list->pHead);
    assert(node->pAfter == list->pTail);
}

void testRemoveAtHead() {
    LinkedList* list;

    printf("Testing remove at head\n");

    list = newList();
    addAtTail(list, (void*) 1);
    addAtTail(list, (void*) 2);
    printNumberList(list);

    removeAtHead(list);
    
    assert(list->length == 1);
    assert(list->pHead == list->pTail);
    printNumberList(list);

    removeAtHead(list);
    
    assert(list->length == 0);
    assert(list->pHead == NULL);
    assert(list->pTail == NULL);
    printNumberList(list);
}

void testRemoveAtTail() {
    LinkedList* list;

    printf("Testing remove at tail\n");

    list = newList();
    addAtTail(list, (void*) 1);
    addAtTail(list, (void*) 2);
    printNumberList(list);

    removeAtTail(list);
    
    assert(list->length == 1);
    assert(list->pHead == list->pTail);
    printNumberList(list);

    removeAtTail(list);
    
    assert(list->length == 0);
    assert(list->pHead == NULL);
    assert(list->pTail == NULL);
    printNumberList(list);
}

void testRemoveAtIndex() {
    LinkedList* list;

    printf("Testing remove at index\n");

    list = newList();
    addAtTail(list, (void*) 1);
    addAtTail(list, (void*) 2);
    addAtTail(list, (void*) 3);
    printNumberList(list);

    removeAtIndex(list, 1);
    
    assert(list->length == 2);
    printNumberList(list);

    removeAtIndex(list, 1);

    assert(list->pHead == list->pTail);
    printNumberList(list);

    removeAtTail(list);
    
    assert(list->length == 0);
    assert(list->pHead == NULL);
    assert(list->pTail == NULL);
    printNumberList(list);
}

void testFind() {
    LinkedList* list;

    printf("Testing find\n");

    list = newList();
    addAtTail(list, (void*) 1);
    addAtTail(list, (void*) 2);
    addAtTail(list, (void*) 3);

    LinkedListFindResult find2 = find(list, (void*) 2, &plainDataFunc);

    assert(find2.pNode == list->pHead->pAfter);

    LinkedListFindResult findFail = find(list, (void*) -1, &plainDataFunc);

    assert(findFail.pNode == NULL);
    assert(findFail.index == -1);
}

void testContains() {
    LinkedList* list;

    printf("Testing contains\n");

    list = newList();
    addAtTail(list, (void*) 1);
    addAtTail(list, (void*) 2);
    addAtTail(list, (void*) 3);

    assert(contains(list, (void*) 2, &plainDataFunc));
    assert(!contains(list, (void*) -1, &plainDataFunc));
}

int main() {
    testNewList();
    testGet();
    testAddAtHead();
    testAddAtTail();
    testAddAtIndex();
    testRemoveAtHead();
    testRemoveAtTail();
    testRemoveAtIndex();
    testFind();
    testContains();
}
