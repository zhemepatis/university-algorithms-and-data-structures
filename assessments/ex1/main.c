#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void displayData(char *str, queue data);

int main() {
    queue testQueue;
    initialiseQueue(&testQueue);
    displayData("Initialisation", testQueue);

    for(int i = 0; i < 5; ++i) {
        enqueue(&testQueue, i);
    }
    displayData("5 nqueues", testQueue);

    makeEmptyQueue(testQueue);
    displayData("Empty queue", testQueue);

    queue secondQueue = cloneQueue(testQueue);
    displayData("Cloned queue", testQueue);

    int result;
    peekQueue(testQueue, &result);
    printf("Peek: %d\n\n", result);

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