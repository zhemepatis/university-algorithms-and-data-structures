#include <stdio.h>

#include "queue.h"

int main() {
    Queue *testNode = createQueue();
    printf("***Initialisation***\n");
    printf("Peek: %d\n", peek(testNode));
    printf("Head value: %d\n", testNode->value);
    printf("Head ptr: %p\n", testNode->next);
    printf("Queue length: %d\n", length(testNode));
    printf("\n");


    push(testNode, 69);
    printf("***Pushed first value***\n");
    printf("Peek: %d\n", peek(testNode));
    printf("Head value: %d\n", testNode->value);
    printf("Head ptr: %p\n", testNode->next);
    printf("Queue length: %d\n", length(testNode));
    printf("\n");


    push(testNode, 420);
    printf("***Pushed second value***\n");
    printf("Peek: %d\n", peek(testNode));
    printf("Head value: %d\n", testNode->value);
    printf("Head ptr: %p\n", testNode->next);
    printf("Queue length: %d\n", length(testNode));
    printf("\n");


    int queueElement = pop(&testNode);
    printf("***Popped first value***\n");
    printf("Peek: %d\n", peek(testNode));
    printf("Head value: %d\n", testNode->value);
    printf("Head ptr: %p\n", testNode->next);
    printf("Queue length: %d\n", length(testNode));
    printf("\n");

    return 0;
}