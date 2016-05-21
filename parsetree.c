#include <stddef.h>
#include "stack.h"
#include "parsetree.h"

extern Stack* pStack;

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

    switch (pNode->type) {
        // Statements - break so we can execute the next one
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

    execute(pNode->pNextNode);

    return NULL;
}
