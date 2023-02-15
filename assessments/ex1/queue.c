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
    if(queueLength(data) == MAX_QUEUE_LENGTH)
        return 1;
    
    return 0;
}

int enqueue(queue *data, int value) {
    if(queueIsFull(*data))
        return 0;

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

    return 1;
}

int dequeue(queue *data, int *storage) {
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

int peekQueue(queue data, int *storage) {
    if(queueIsEmpty(data))
        return 0;

    *storage = data.front->value;
    return 1;
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

void destroyQueue(queue *data) {
    while(data->front != NULL) {
        queue_node *nextNodePtr = data->front->next;
        free(data->front);
        data->front = nextNodePtr;
    }
    data->rear = NULL;
}

void makeEmptyQueue(queue data) {
    queue_node *currentNodePtr = data.front;

    while(currentNodePtr != NULL) {
        currentNodePtr->value = 0;
        currentNodePtr = currentNodePtr->next;
    }
}

queue cloneQueue(queue data) {
    
}