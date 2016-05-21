%{
#include <stdio.h>

int yyerror(char* s);
int yylex(void);
%}

%token SPACE TAB LF

%%

statement_sequence: statement
    | statement statement_sequence

statement: stack_statement
    | arithmetic_statement
    | heap_statement
    | flow_statement
    | io_statement

stack_statement: SPACE stack_op

arithmetic_statement: TAB SPACE arithmetic_op

heap_statement: TAB TAB heap_op

flow_statement: LF flow_op

io_statement: TAB LF io_op

stack_op: SPACE number // push a number onto the stack
    | LF SPACE // duplicate the item on top of the stack
    | TAB SPACE number // copy the nth item on the stack onto the top of the stack
    | LF TAB // Swap the top two items on the stack
    | LF LF // Discard the top item on the stack
    | TAB LF number // Slide n items off the stack, keeping the top item

arithmetic_op: SPACE SPACE // Addition
    | SPACE TAB // Subtraction
    | SPACE LF // Multiplication
    | TAB SPACE // Integer division
    | TAB TAB // Modulo

heap_op: SPACE // Heap store
    | TAB // Heap retrieve

flow_op: SPACE SPACE label // Mark location in the program
    | SPACE TAB label // Call a subroutine
    | SPACE LF label // Jump unconditionally to a label
    | TAB SPACE label // Jump to a label if the top of the stack is zero
    | TAB TAB label // Jump to a label if the top of the stack is negative
    | TAB LF // End a subroutine and transfer control back to the caller
    | LF LF { // End program
        return 0;
    }

io_op: SPACE SPACE // Output the character at the top of the stack
    | SPACE TAB // Output the number at the top of the stack
    | TAB SPACE // Read a character and place it in the *location given by* the top of the stack
    | TAB TAB // Read a number and place it in the *location given by* the top of the stack

number: sign_bit digit_sequence LF

sign_bit: SPACE
    | TAB

digit_sequence: digit
    | digit digit_sequence

digit: SPACE
    | TAB

label: label_char_sequence LF

label_char_sequence: label_char
    | label_char label_char_sequence

label_char: SPACE
    | TAB

%%

extern FILE* yyin;
main(int argc, char** argv) {
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
}

int yyerror(char* errorMessage) {
    printf("Error with message: %s", errorMessage);
    return 0;
}
