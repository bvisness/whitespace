#include <stdio.h>

#include "../stack.h"

int main() {
    Stack* stack = createEmptyStack();
    Stack* stack2 = createEmptyStack();
    int i;

    // Push/pop tests
    printf("Pushing 1 onto the stack\n");
    push(stack, 1);
    printf("Peeked value (expect 1): %d\n", peek(stack));

    printf("Pushing 4 onto the stack\n");
    push(stack, 4);
    printf("Peeked value (expect 4): %d\n", peek(stack));

    printf("Popped value (expect 4): %d\n", pop(stack));
    printf("Popped value (expect 1): %d\n", pop(stack));

    freeStack(stack);
    freeStack(stack2);
    return 0;
}
