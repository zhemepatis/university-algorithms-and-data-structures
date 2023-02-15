#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void printQueue(queue data);

int main() {
    queue firstQueue;
    initialiseQueue(&firstQueue);

    printQueue(firstQueue);

    for(int i = 1; i <= MAX_QUEUE_LENGTH+1; ++i)
        enqueue(&firstQueue, i);

    printQueue(firstQueue);

    queue secondQueue = cloneQueue(firstQueue);
    printQueue(secondQueue);

    int result;
    dequeue(&firstQueue, &result);
    dequeue(&firstQueue, &result);
    printQueue(firstQueue);

    makeEmptyQueue(firstQueue);
    printQueue(firstQueue);
    printQueue(secondQueue);

    destroyQueue(&firstQueue);
    destroyQueue(&secondQueue);
    printQueue(firstQueue);
    printQueue(secondQueue);
    
    return 0;
}

void printQueue(queue data) {
    printf("%s\n", convertQueueToString(data));
}