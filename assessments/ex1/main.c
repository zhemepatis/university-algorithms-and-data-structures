#include <stdio.h>

#include "queues.h"

int main() {
    Queue_node *testNode = createQueue();

    printf("Value: %d\n", testNode->value);
    printf("ptr: %p\n", testNode->next);

    push(testNode, 69);


    printf("Value: %d\n", testNode->value);
    printf("ptr: %p\n", testNode->next);

    push(testNode, 420);

    printf("Value: %d\n", testNode->value);
    printf("ptr: %p\n", testNode->next);

    int queueElement = pop(&testNode);

    printf("Value: %d\n", testNode->value);
    printf("ptr: %p\n", testNode->next);
    printf("result: %d\n", queueElement);


    return 0;
}