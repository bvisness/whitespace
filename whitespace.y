%{
#include <stdio.h>

#include "stack.h"
#include "heap.h"
#include "parsetree.h"

int yyerror(char* s);
int yylex(void);

Stack* pStack;
Heap* pHeap;
TreeNode* pHeadNode;
%}

%union {
    TreeNode* tnval;
}

%token SPACE TAB LF

%type<tnval> statement statement_sequence
%type<tnval> stack_statement arithmetic_statement heap_statement flow_statement io_statement
%type<tnval> stack_op arithmetic_op heap_op flow_op io_op
%type<tnval> number sign_bit digit_sequence digit
%type<tnval> label label_char_sequence label_char

%%

statement_sequence: statement {
        $$ = $1;
        pHeadNode = $$;
    }
    | statement statement_sequence {
        $$ = $1;
        $$->pNextNode = $2;
        pHeadNode = $$;
        if ($$->type == NT_flow_end_program) {
            return 0;
        }
    }

statement: stack_statement
    | arithmetic_statement
    | heap_statement
    | flow_statement
    | io_statement

stack_statement: SPACE stack_op {
        $$ = $2;
    }

arithmetic_statement: TAB SPACE arithmetic_op {
        $$ = $3;
    }

heap_statement: TAB TAB heap_op {
        $$ = $3;
    }

flow_statement: LF flow_op {
        $$ = $2;
    }

io_statement: TAB LF io_op {
        $$ = $3;
    }

stack_op: SPACE number { // push a number onto the stack
        $$ = createEmptyNode(NT_stack_push);
        $$->pFirstOperand = $2;
    }
    | LF SPACE { // duplicate the item on top of the stack
        $$ = createEmptyNode(NT_stack_dup);
    }
    | TAB SPACE number { // copy the nth item on the stack onto the top of the stack
        $$ = createEmptyNode(NT_stack_copy);
        $$->pFirstOperand = $3;
    }
    | LF TAB { // Swap the top two items on the stack
        $$ = createEmptyNode(NT_stack_swap);
    }
    | LF LF { // Discard the top item on the stack
        $$ = createEmptyNode(NT_stack_discard);
    }
    | TAB LF number { // Slide n items off the stack, keeping the top item
        $$ = createEmptyNode(NT_stack_slide);
        $$->pFirstOperand = $3;
    }

arithmetic_op: SPACE SPACE { // Addition
        $$ = createEmptyNode(NT_arithmetic_add);
    }
    | SPACE TAB { // Subtraction
        $$ = createEmptyNode(NT_arithmetic_subtract);
    }
    | SPACE LF { // Multiplication
        $$ = createEmptyNode(NT_arithmetic_multiply);
    }
    | TAB SPACE { // Integer division
        $$ = createEmptyNode(NT_arithmetic_divide);
    }
    | TAB TAB { // Modulo
        $$ = createEmptyNode(NT_arithmetic_mod);
    }

heap_op: SPACE { // Heap store
        $$ = createEmptyNode(NT_heap_store);
    }
    | TAB { // Heap retrieve
        $$ = createEmptyNode(NT_heap_retrieve);
    }

flow_op: SPACE SPACE label { // Mark location in the program
        $$ = createEmptyNode(NT_flow_mark);
        $$->pFirstOperand = $3;
    }
    | SPACE TAB label { // Call a subroutine
        $$ = createEmptyNode(NT_flow_call);
        $$->pFirstOperand = $3;
    }
    | SPACE LF label { // Jump unconditionally to a label
        $$ = createEmptyNode(NT_flow_jump);
        $$->pFirstOperand = $3;
    }
    | TAB SPACE label { // Jump to a label if the top of the stack is zero
        $$ = createEmptyNode(NT_flow_jump_if_zero);
        $$->pFirstOperand = $3;
    }
    | TAB TAB label { // Jump to a label if the top of the stack is negative
        $$ = createEmptyNode(NT_flow_jump_if_negative);
        $$->pFirstOperand = $3;
    }
    | TAB LF { // End a subroutine and transfer control back to the caller
        $$ = createEmptyNode(NT_flow_end_subroutine);
    }
    | LF LF { // End program
        $$ = createEmptyNode(NT_flow_end_program);
    }

io_op: SPACE SPACE { // Output the character at the top of the stack
        $$ = createEmptyNode(NT_io_output_char);
    }
    | SPACE TAB { // Output the number at the top of the stack
        $$ = createEmptyNode(NT_io_output_num);
    }
    | TAB SPACE { // Read a character and place it in the *location given by* the top of the stack
        $$ = createEmptyNode(NT_io_read_char);
    }
    | TAB TAB { // Read a number and place it in the *location given by* the top of the stack
        $$ = createEmptyNode(NT_io_read_num);
    }

number: sign_bit digit_sequence LF {
        $$ = createEmptyNode(NT_number);
        $$->pFirstOperand = $1;
        $$->pSecondOperand = $2;
    }

sign_bit: SPACE {
        $$ = createEmptyNode(NT_sign_bit);
        $$->digitLiteral = 0;
    }
    | TAB {
        $$ = createEmptyNode(NT_sign_bit);
        $$->digitLiteral = 1;
    }

digit_sequence: digit
    | digit digit_sequence {
        $$ = $1;
        $$->pNextNode = $2;
    }

digit: SPACE {
        $$ = createEmptyNode(NT_digit);
        $$->digitLiteral = 0;
    }
    | TAB {
        $$ = createEmptyNode(NT_digit);
        $$->digitLiteral = 1;
    }

label: label_char_sequence LF {
        $$ = createEmptyNode(NT_label);
        $$->pFirstOperand = $1;
    }

label_char_sequence: label_char
    | label_char label_char_sequence {
        $$ = $1;
        $$->pNextNode = $2;
    }

label_char: SPACE {
        $$ = createEmptyNode(NT_label_char);
        $$->charLiteral = ' ';
    }
    | TAB {
        $$ = createEmptyNode(NT_label_char);
        $$->charLiteral = '\t';
    }

%%

extern FILE* yyin;
int main(int argc, char** argv) {
    char* filename = NULL;
    int i;

    for (i = 1; i < argc; i++) {
        // fun logic for options here
        filename = argv[i];
    }

    if (filename) {
        yyin = fopen(filename, "r");
        if (!yyin) {
            printf("Could not open file %s", filename);
        }
    } else {
        yyin = stdin;
    }

    yyparse();

    pStack = createEmptyStack();
    pHeap = createEmptyHeap();
    execute(pHeadNode);

    freeStack(pStack);
    freeHeap(pHeap);
    freeNode(pHeadNode);

    return 0;
}

int yyerror(char* errorMessage) {
    printf("Error with message: %s", errorMessage);
    return 0;
}
