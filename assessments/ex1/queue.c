#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void initialiseQueue(queue *data) {
    data->front = NULL;
    data->rear = NULL;
}

int queueIsEmpty(queue data) {
    if(!data.front && !data.rear)
        return 1;

    return 0;
}

int queueIsFull(queue data) {

}

void enqueue(queue *data, int value) {
    // check whether it is not full

    queue_node *newNodePtr = malloc(sizeof(queue_node));
    newNodePtr->value = value;
    newNodePtr->next = NULL;

    if(data->rear != NULL) {
        queue_node *lastNodePtr = data->rear;
        lastNodePtr->next = newNodePtr;
    }

    data->rear = newNodePtr;

    if(data->front == NULL)
        data->front = data->rear;
}

int dequeue(queue *data, int *storage) {
    // chekcing whether queue isn't empty
    if(queueIsEmpty(*data))
        return 0;

    queue_node *currentFrontPtr = data->front;
    *storage = currentFrontPtr->value;

    data->front = currentFrontPtr->next;
    if(data->front == NULL)
        data->rear = NULL;
        
    free(currentFrontPtr);
    return 1;  
}

int peek(queue data) {
    return data.front->value;
}

int queueLength(queue data) {
    int length = 0;
    queue_node *currentNodePtr = data.front;

    while(currentNodePtr != NULL) {
        ++length;
        currentNodePtr = currentNodePtr->next;
    }

    return length;
}

void destroyQueue() {
    
}