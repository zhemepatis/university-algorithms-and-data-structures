#include <stdio.h>

#include "queue.h"

int main() {
    Queue *testNode = createQueue();
    printf("Value: %d\n", testNode->value);
    printf("ptr: %p\n", testNode->next);
    printf("length: %d\n", length(testNode));
    printf("\n");



    push(testNode, 69);
    printf("Value: %d\n", testNode->value);
    printf("ptr: %p\n", testNode->next);
    printf("length: %d\n", length(testNode));
    printf("\n");


    push(testNode, 420);
    printf("Value: %d\n", testNode->value);
    printf("ptr: %p\n", testNode->next);
    printf("length: %d\n", length(testNode));
    printf("\n");


    int queueElement = pop(&testNode);
    printf("Value: %d\n", testNode->value);
    printf("ptr: %p\n", testNode->next);
    printf("result: %d\n", queueElement);
    printf("length: %d\n", length(testNode));
    printf("\n");

    return 0;
}