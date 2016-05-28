#include <stdlib.h>
#include <assert.h>

#include "../linkedlist.h"

void printNumberList(LinkedList* pList) {
    int i;

    printf("Length %d, Head %p, Tail %p\n", pList->length, pList->pHead, pList->pTail);
    if (pList->length > 0) {
        printf("%d", get(pList, 0)->data);
    }
    for (i = 1; i < pList->length; i++) {
        printf(", %d", get(pList, i)->data);
    }

    printf("\n");
}

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

int main() {
    testNewList();
    testGet();
    testAddAtHead();
    testAddAtTail();
    testAddAtIndex();
    testRemoveAtHead();
    testRemoveAtTail();
    testRemoveAtIndex();
}
