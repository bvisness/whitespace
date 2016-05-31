#pragma once

#include "linkedlist.h"

typedef int StackVal;

typedef struct StackTag {
    LinkedList* pList;
} Stack;

Stack* createEmptyStack(void);

void freeStack(Stack* stack);

void push(Stack* stack, StackVal val);

StackVal pop(Stack* stack);

StackVal peek(Stack* stack);

void printStack(Stack* stack);
