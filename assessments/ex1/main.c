#include <stdio.h>

#include "queues.h"

int main() {
    Queue_node *testNode = createQueue();

    printf("Value: %d\n", testNode->value);
    printf("ptr: %p\n", testNode->next);

    return 0;
}