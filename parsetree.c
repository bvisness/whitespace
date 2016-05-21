#include <stddef.h>
#include "stack.h"
#include "parsetree.h"

extern Stack* pStack;

#define DEBUG 1

//
// Private functions
//
int twoToThe(int exponent) {
    int result = 1;
    int i;
    for (i = 0; i < exponent; i++) {
        result *= 2;
    }

    return result;
}


//
// Public functions
//
TreeNode* createEmptyNode(NodeType type) {
    TreeNode* result = malloc(sizeof(TreeNode));
    result->type = type;
    result->pFirstOperand = NULL;
    result->pSecondOperand = NULL;
    result->digitLiteral = 0;
    result->charLiteral = 0;
    result->pNextNode = NULL;

    return result;
}

void freeNode(TreeNode* pNode) {
    if (!pNode) {
        return;
    }

    freeNode(pNode->pFirstOperand);
    freeNode(pNode->pSecondOperand);
    freeNode(pNode->pNextNode);

    free(pNode);
}

int digitRecursionCount;
void* execute(TreeNode* pNode) {
    if (!pNode) {
        return;
    }

#if DEBUG
    printf("Executing node of type %d\n", pNode->type);
#endif

    switch (pNode->type) {
        // Statements - break so we can execute the next one
        case NT_stack_push: {
            int num = (int) execute(pNode->pFirstOperand);
            push(pStack, num);
        } break;
        case NT_stack_dup: {
            push(pStack, peek(pStack));
        } break;
        case NT_stack_copy: {
            int howManyDown = (int) execute(pNode->pFirstOperand);
            int val = pStack->values[pStack->topIndex - howManyDown];
            push(pStack, val);
        } break;
        case NT_stack_swap: {
            int first = pop(pStack);
            int second = pop(pStack);
            push(pStack, first);
            push(pStack, second);
        } break;
        case NT_stack_discard: {
            pop(pStack);
        } break;
        case NT_stack_slide: {
            // TODO: What the hell does slide mean
        } break;
        case NT_flow_end_program: {
            return NULL;
        } break;

        // Expressions - return so we don't execute a next statement
        case NT_number: {
            digitRecursionCount = 0;
            int value = (int) execute(pNode->pSecondOperand);
            if (pNode->pFirstOperand->digitLiteral) {
                value *= -1;
            }
            return (void*) value;
        } return;
        case NT_digit: {
            int placesFromLeft = digitRecursionCount;
            if (pNode->pNextNode) {
                int sumSoFar;
                digitRecursionCount++;
                sumSoFar = (int) execute(pNode->pNextNode);
                if (pNode->digitLiteral) {
                    sumSoFar += twoToThe(digitRecursionCount - placesFromLeft);
                }
                return (void*) sumSoFar;
            } else {
                return (void*) pNode->digitLiteral;
            }
        } return;
        
        default: {
            printf("Cannot execute node with unrecognized type %d\n", pNode->type);
        } break;
    }

    printf("Stack: ");
    printStack(pStack);
    execute(pNode->pNextNode);

    return NULL;
}
