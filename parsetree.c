#include <stddef.h>
#include "parsetree.h"

TreeNode* createEmptyNode(NodeType type) {
    TreeNode* result = malloc(sizeof(TreeNode));
    result->type = type;
    result->pOperand = NULL;
    result->digitLiteral = 0;
    result->charLiteral = 0;
    result->pNextStatement = NULL;

    return result;
}

void freeNode(TreeNode* pNode) {
    if (!pNode) {
        return;
    }

    freeNode(pNode->pOperand);
    freeNode(pNode->pNextStatement);

    free(pNode);
}

void* execute(TreeNode* pNode) {
    if (!pNode) {
        return;
    }

    switch (pNode->type) {
        // Statements - break so we can execute the next one
        // Expressions - return so we don't execute a next statement
        
        default: {
            printf("Cannot execute node with unrecognized type %d\n", pNode->type);
        } break;
    }

    execute(pNode->pNextStatement);

    return NULL;
}
