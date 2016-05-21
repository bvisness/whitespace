#pragma once

typedef int StackVal;

typedef struct StackTag {
    StackVal* values;
    int capacity;
    int topIndex;
} Stack;

Stack* createEmptyStack(void);

void freeStack(Stack* stack);

void push(Stack* stack, StackVal val);

StackVal pop(Stack* stack);

StackVal peek(Stack* stack);
