#pragma once

typedef struct LinkedListNodeTag LinkedListNode;
struct LinkedListNodeTag {
    void* data;
    LinkedListNode* pBefore;
    LinkedListNode* pAfter;
};

typedef struct LinkedListTag {
    LinkedListNode* pHead;
    LinkedListNode* pTail;
    int length;
    int dataCanBeFreed;
} LinkedList;

typedef struct LinkedListFindResultTag {
    LinkedListNode* pNode;
    int index;
} LinkedListFindResult;

typedef void* (*llDataFunc)(LinkedListNode* node);

LinkedList* newList();

LinkedListNode* addAtHead(LinkedList* pList, void* data);
LinkedListNode* addAtTail(LinkedList* pList, void* data);
LinkedListNode* addAtIndex(LinkedList* pList, void* data, int index);
void removeAtHead(LinkedList* pList);
void removeAtTail(LinkedList* pList);
void removeAtIndex(LinkedList* pList, int index);

// No head and tail methods provided. Access them via the LinkedList
// struct itself.
LinkedListNode* get(LinkedList* pList, int index);
LinkedListFindResult find(LinkedList* pList, void* matchData, llDataFunc dataFunc);
int contains(LinkedList* pList, void* matchData, llDataFunc dataFunc);

void freeList(LinkedList* pList);
