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

    printf("Starting capacity of heap: %d\n", heap2->capacity);
    for (i = 0; i < 256; i++) {
        store(heap2, i, i);
    }
    printf("Capacity after 256 inserts (should be same as above): %d\n", heap2->capacity);
    store(heap2, 257, 257);
    printf("Capacity after one more insert (should be double starting): %d\n", heap2->capacity);

    freeHeap(heap1);
    freeHeap(heap2);
    return 0;
}
