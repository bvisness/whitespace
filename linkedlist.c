#include <stdlib.h>
#include <stdio.h>

#include "linkedlist.h"

//
// Private functions
//
LinkedListNode* newNode(void* data) {
    LinkedListNode* newNode = malloc(sizeof(LinkedListNode));
    newNode->data = data;
    newNode->pBefore = NULL;
    newNode->pAfter = NULL;

    return newNode;
}

void freeNode(LinkedListNode* node) {
    free(node);
}

void freeNodeAndData(LinkedListNode* node) {
    free(node->data);
    free(node);
}

//
// Public functions
//
LinkedList* newList() {
    LinkedList* result = malloc(sizeof(LinkedList));
    result->pHead = NULL;
    result->pTail = NULL;
    result->length = 0;
    result->dataCanBeFreed = 1;

    return result;
}

LinkedListNode* addAtHead(LinkedList* pList, void* data) {
    LinkedListNode* node = newNode(data);

    // Set up references on the new node
    node->pBefore = NULL;
    node->pAfter = pList->pHead;

    // Patch it into the current head if possible
    if (pList->pHead) {
        pList->pHead->pBefore = node;
    }
    pList->pHead = node;

    pList->length++;

    // We might be the tail as well
    if (pList->length == 1) {
        pList->pTail = node;
    }

    return node;
}

LinkedListNode* addAtTail(LinkedList* pList, void* data) {
    LinkedListNode* node = newNode(data);

    // Set up references on the new node
    node->pBefore = pList->pTail;
    node->pAfter = NULL;

    // Patch it into the current tail if possible
    if (pList->pTail) {
        pList->pTail->pAfter = node;
    }
    pList->pTail = node;

    pList->length++;

    // We might be the head as well
    if (pList->length == 1) {
        pList->pHead = node;
    }

    return node;
}

LinkedListNode* addAtIndex(LinkedList* pList, void* data, int index) {
    LinkedListNode* before;
    LinkedListNode* after;
    LinkedListNode* node;
    int i;

    // Check for adding at either end
    if (index <= 0) {
        return addAtHead(pList, data);
    }
    if (index >= pList->length) {
        return addAtTail(pList, data);
    }

    // Find the before and after nodes
    before = pList->pHead;
    after = before->pAfter;
    for (i = 1; i < index; i++) {
        before = after;
        after = before->pAfter;
    }

    // Set up references on the new node
    node = newNode(data);
    node->pBefore = before;
    node->pAfter = after;

    // Patch it in
    before->pAfter = node;
    after->pBefore = node;

    pList->length++;

    return node;
}

void removeAtHead(LinkedList* pList) {
    LinkedListNode* nodeToDelete;

    if (pList->length <= 0) {
        fprintf(stderr, "Attempting to remove from head of empty list! Exiting...\n");
        exit(-1);
    }

    nodeToDelete = pList->pHead;
    if (nodeToDelete->pAfter) {
        nodeToDelete->pAfter->pBefore = NULL;
    }
    pList->pHead = nodeToDelete->pAfter;

    if (pList->dataCanBeFreed) {
        freeNodeAndData(nodeToDelete);
    } else {
        freeNode(nodeToDelete);
    }

    pList->length--;

    // We must also set the tail to null if we removed the last item
    if (pList->length == 0) {
        pList->pTail = NULL;
    }
}

void removeAtTail(LinkedList* pList) {
    LinkedListNode* nodeToDelete;

    if (pList->length <= 0) {
        fprintf(stderr, "Attempting to remove from tail of empty list! Exiting...\n");
        exit(-1);
    }

    nodeToDelete = pList->pTail;
    if (nodeToDelete->pBefore) {
        nodeToDelete->pBefore->pAfter = NULL;
    }
    pList->pTail = nodeToDelete->pBefore;

    if (pList->dataCanBeFreed) {
        freeNodeAndData(nodeToDelete);
    } else {
        freeNode(nodeToDelete);
    }

    pList->length--;

    // We must also set the head to null if we removed the last item
    if (pList->length == 0) {
        pList->pHead = NULL;
    }
}

void removeAtIndex(LinkedList* pList, int index) {
    if (pList->length <= 0) {
        fprintf(stderr, "Attempting to remove from index %d of empty list! Exiting...\n", index);
        exit(-1);
    }

    LinkedListNode* nodeToDelete = get(pList, index);

    if (nodeToDelete == pList->pHead) {
        removeAtHead(pList);
        return;
    }
    if (nodeToDelete == pList->pTail) {
        removeAtTail(pList);
        return;
    }

    nodeToDelete->pBefore->pAfter = nodeToDelete->pAfter;
    nodeToDelete->pAfter->pBefore = nodeToDelete->pBefore;

    if (pList->dataCanBeFreed) {
        freeNodeAndData(nodeToDelete);
    } else {
        freeNode(nodeToDelete);
    }

    pList->length--;
}

int contains(LinkedList* pList, void* data, llFindFunc findFunc);

LinkedListFindResult find(LinkedList* pList, llFindFunc findFunc) {
    LinkedListFindResult result;
    LinkedListNode* currentNode = pList->pHead;
    int index = 0;

    result.pNode = NULL;
    result.index = -1;

    while (currentNode != NULL) {
        if (findFunc(currentNode)) {
            result.pNode = currentNode;
            result.index = index;
            break;
        }

        currentNode = currentNode->pAfter;
        index++;
    }

    return result;
}

LinkedListNode* get(LinkedList* pList, int indexToGet) {
    LinkedListNode* result;
    int i;

    // TODO: This could be optimized by starting from the tail in some circumstances

    if (indexToGet < 0 || indexToGet >= pList->length) {
        return NULL;
    }

    result = pList->pHead;
    for (i = 0; i < indexToGet; i++) {
        result = result->pAfter;
    }

    return result;
}

void freeList(LinkedList* pList) {
    LinkedListNode* currentNode = pList->pHead;
    LinkedListNode* nextNode;

    while (currentNode != NULL) {
        nextNode = currentNode->pAfter;

        if (pList->dataCanBeFreed) {
            freeNodeAndData(currentNode);
        } else {
            freeNode(currentNode);
        }

        currentNode = nextNode;
    }

    free(pList);
}
