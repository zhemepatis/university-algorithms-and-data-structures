#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void displayData(char *str, queue data);

int main() {
    queue displayDataQueue;
    initialiseQueue(&displayDataQueue);
    displayData("Initialisation", displayDataQueue);

    enqueue(&displayDataQueue, 1);
    displayData("1 enqueue", displayDataQueue);

    enqueue(&displayDataQueue, 2);
    displayData("2 enqueue", displayDataQueue);

    enqueue(&displayDataQueue, 3);
    displayData("3 enqueue", displayDataQueue);

    printf("Peek: %d\n\n", peek(displayDataQueue));

    int result;
    dequeue(&displayDataQueue, &result);
    displayData("1 dequeue", displayDataQueue);

    dequeue(&displayDataQueue, &result);
    displayData("2 dequeue", displayDataQueue);

    dequeue(&displayDataQueue, &result);
    displayData("3 dequeue", displayDataQueue);

    destroyQueue(&displayDataQueue);
    displayData("Queue destruction 1", displayDataQueue);

    enqueue(&displayDataQueue, 10);
    enqueue(&displayDataQueue, 11);
    enqueue(&displayDataQueue, 12);
    destroyQueue(&displayDataQueue);
    displayData("Queue destruction 2", displayDataQueue);

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