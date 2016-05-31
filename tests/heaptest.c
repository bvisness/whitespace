#include <stdio.h>

#include "../heap.h"

int main() {
    Heap* heap1 = createEmptyHeap();
    Heap* heap2 = createEmptyHeap();
    int i;

    printf("Adding 3 to heap at index 123\n");
    store(heap1, 123, 3);
    printHeap(heap1);

    printf("Value read from heap at index 123: %d\n", read(heap1, 123));

    printf("Adding 5 to heap at index 234\n");
    store(heap1, 234, 5);
    printHeap(heap1);

    printf("Changing value at address 123 to 13\n");
    store(heap1, 123, 13);
    printHeap(heap1);

    freeHeap(heap1);
    freeHeap(heap2);
    return 0;
}
