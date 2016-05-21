#pragma once

typedef enum NodeTypeTag
{
    NT_stack_push,
    NT_stack_dup,
    NT_stack_copy,
    NT_stack_swap,
    NT_stack_discard,
    NT_stack_slide,
    NT_arithmetic_add,
    NT_arithmetic_subtract,
    NT_arithmetic_multiply,
    NT_arithmetic_divide,
    NT_arithmetic_mod,
    NT_heap_store,
    NT_heap_retrieve,
    NT_flow_mark,
    NT_flow_call,
    NT_flow_jump,
    NT_flow_jump_if_zero,
    NT_flow_jump_if_negative,
    NT_flow_end_subroutine,
    NT_io_output_char,
    NT_io_output_num,
    NT_io_read_char,
    NT_io_read_num
} NodeType;

typedef struct TreeNodeTag
{
    NodeType type;
    struct TreeNodeTag* pOperand;
    short digitLiteral;
    char charLiteral;
    struct TreeNodeTag* pNextStatement;
} TreeNode;

TreeNode* createEmptyNode(NodeType type);

void freeNode(TreeNode* pNode);

void* execute(TreeNode* pNode);
