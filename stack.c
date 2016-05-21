#include <stdio.h>

#include "stack.h"

#define STACK_MIN_SIZE 256

//
// Private functions
//
int numItemsInStack(Stack* stack) {
    return stack->topIndex + 1;
}

void expandStack(Stack* stack) {
    int newCapacity = 2 * stack->capacity;
    StackVal* newValues = malloc(newCapacity * sizeof(StackVal));
    int i;

    for (i = 0; i < stack->capacity; i++) {
        newValues[i] = stack->values[i];
    }

    free(stack->values);
    stack->values = newValues;
    stack->capacity = newCapacity;
}

//
// Functions from header file
//
Stack* createEmptyStack(void) {
    Stack* result = malloc(sizeof(Stack));
    result->values = malloc(STACK_MIN_SIZE * sizeof(StackVal));
    result->capacity = STACK_MIN_SIZE;
    result->topIndex = -1;

    return result;
}

void freeStack(Stack* stack) {
    free(stack->values);
    free(stack);
}

void push(Stack* stack, StackVal val) {
    if (numItemsInStack(stack) >= stack->capacity) {
        expandStack(stack);
    }

    stack->topIndex++;
    stack->values[stack->topIndex] = val;
}

StackVal pop(Stack* stack) {
    StackVal val;

    if (numItemsInStack(stack) <= 0) {
        fprintf(stderr, "Attempted to pop from empty stack! Exiting...\n");
        exit(-1);
    }

    val = stack->values[stack->topIndex];
    stack->topIndex--;
    return val;
}

StackVal peek(Stack* stack) {
    if (numItemsInStack(stack) <= 0) {
        fprintf(stderr, "Attempted to peek from empty stack! Exiting...\n");
        exit(-1);
    }

    return stack->values[stack->topIndex];
}
