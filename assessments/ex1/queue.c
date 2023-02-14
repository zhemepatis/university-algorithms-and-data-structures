#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

Queue *createQueue() {
    Queue *node = malloc(sizeof(Queue));
    initialiseNode(node);

    return node;
}

void initialiseNode(Queue *node) {
    node->next = NULL;
    node->value = 0;
}

int isEmpty(Queue *node) {
    if(node->next == NULL)
        return 1;
    
    return 0;
}

int isFull() {


}

void push(Queue *node, int value) {
    Queue *currentNodePtr = node;

    while(currentNodePtr->next != NULL) {
        currentNodePtr = currentNodePtr->next;
    }

    currentNodePtr->value = value;
    currentNodePtr->next = malloc(sizeof(Queue));
    initialiseNode(currentNodePtr->next);
}

int pop(Queue **node) {
    int result = (*node)->value;
    *node = (*node)->next;

    return result;
}

int peek(Queue *node) {
    return node->value;
}

int length(Queue *node) {
    Queue *currentNodePtr = node;
    int length = 0;

    while(currentNodePtr->next != NULL) {
        ++length;
        currentNodePtr = currentNodePtr->next;
    }

    return length;
}

void destroy() {
  
}