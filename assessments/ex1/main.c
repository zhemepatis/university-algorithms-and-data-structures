#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void displayData(char *str, queue data);

int main() {
    // initialiseQueue
    queue testQueue;
    initialiseQueue(&testQueue);
    displayData("Initialisation", testQueue);

    // enqueue and queueIsFull
    enqueue(&testQueue, 1);
    displayData("1 enqueue", testQueue);
    enqueue(&testQueue, 2);
    displayData("2 enqueue", testQueue);
    enqueue(&testQueue, 3);
    displayData("3 enqueue", testQueue);
    enqueue(&testQueue, 4);
    displayData("4 enqueue", testQueue);
    enqueue(&testQueue, 5);
    displayData("5 enqueue", testQueue);

    makeEmptyQueue(testQueue);

    // peek
    int result;
    peekQueue(testQueue, &result);
    printf("Peek: %d\n\n", result);

    // dequeue, queueIsEmpty, destroytQueue
    dequeue(&testQueue, &result);
    displayData("1 dequeue", testQueue);

    destroyQueue(&testQueue);
    displayData("Queue destruction 1", testQueue);

    destroyQueue(&testQueue);
    displayData("Queue destruction 2", testQueue);

    dequeue(&testQueue, &result);
    displayData("2 dequeue", testQueue);

    return 0;
}

void displayData(char *str, queue data) {
    printf("*** %s ***\n", str);

    printf("Length: %d\n", queueLength(data));

    printf("Front: %d\n", data.front);
    if(data.front != NULL)
        printf("Front value: %d\n", (data.front)->value);

    printf("Rear: %d\n", data.rear);
    if(data.rear != NULL)
        printf("Rear value: %d\n", (data.rear)->value);

    printf("\n");
}