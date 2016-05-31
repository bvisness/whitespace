#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

//
// Private functions
//
int numItemsInStack(Stack* stack) {
    return stack->pList->length;
}

//
// Functions from header file
//
Stack* createEmptyStack(void) {
    Stack* result = malloc(sizeof(Stack));
    result->pList = newList();

    return result;
}

void freeStack(Stack* stack) {
    freeList(stack->pList);
    free(stack);
}

void push(Stack* stack, StackVal val) {
    addAtHead(stack->pList, (void*) val);
}

StackVal pop(Stack* stack) {
    StackVal val;

    if (numItemsInStack(stack) <= 0) {
        fprintf(stderr, "Attempted to pop from empty stack! Exiting...\n");
        exit(-1);
    }

    val = (StackVal) (stack->pList->pHead->data);
    removeAtHead(stack->pList);

    return val;
}

StackVal peek(Stack* stack) {
    StackVal val;

    if (numItemsInStack(stack) <= 0) {
        fprintf(stderr, "Attempted to peek from empty stack! Exiting...\n");
        exit(-1);
    }

    return (StackVal) (stack->pList->pHead->data);
}

void printStack(Stack* stack) {
    int i;

    if (stack->pList->length > 0) {
        printf("%d", (int) get(stack->pList, 0)->data);
    }
    for (i = 1; i < stack->pList->length; i++) {
        printf(", %d", (int) get(stack->pList, i)->data);
    }

    printf("\n");
}
