#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"

void printQueue(queue data);

int main() {
    queue firstQueue;
    initialiseQueue(&firstQueue);

    // testing queue initialisation
    assert(!firstQueue.front && !firstQueue.rear);

    // testing enqueue function
    int value = 0;
    enqueue(&firstQueue, value);
    assert(firstQueue.front == firstQueue.rear && (firstQueue.front)->value == value);

    queue_node *frontPtr = firstQueue.front;
    int frontValue = (firstQueue.front)->value;
    for(int i = 1; i <= MAX_QUEUE_LENGTH; ++i) {
        value = i;
        enqueue(&firstQueue, value);

        if(i != MAX_QUEUE_LENGTH)
            assert((firstQueue.rear)->value == value && (firstQueue.front)->value == frontValue && firstQueue.front == frontPtr);
    }

    printQueue(firstQueue);

    // testing how enqueue function behaves when exceeding queue length limit
    assert((firstQueue.rear)->value != value && (firstQueue.front)->value == frontValue && firstQueue.front == frontPtr);

    // testing queue cloning
    queue secondQueue = cloneQueue(firstQueue);
    assert((firstQueue.front)->value == (secondQueue.front)->value && (firstQueue.rear)->value == (secondQueue.rear)->value && firstQueue.front != secondQueue.front & firstQueue.rear != secondQueue.rear);

    // testing dequeue function
    int result;
    for(int i = 0; i < MAX_QUEUE_LENGTH; ++i) {
        value = i;
        assert(dequeue(&firstQueue, &result) && value == result);
    }

    // checking front and rear pointers when queue is fully dequeued
    assert(!firstQueue.front && !firstQueue.rear);

    // testing how dequeue function behaves when exceeding queue length limit
    assert(!dequeue(&firstQueue, &result));

    // testing makeEmptyQueue()
    makeEmptyQueue(secondQueue);
    assert((secondQueue.front)->value == 0 && (secondQueue.rear)->value == 0);

    // testing destroyQueue()
    destroyQueue(&secondQueue);
    assert(!firstQueue.front && !firstQueue.rear);

    printQueue(firstQueue);
    
    return 0;
}

void printQueue(queue data) {
    printf("%s\n", convertQueueToString(data));
}