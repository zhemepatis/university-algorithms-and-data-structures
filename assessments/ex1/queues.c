#include <stdio.h>
#include <stdlib.h>

#include "queues.h"

Queue_node *createQueue() {
    Queue_node *node = malloc(sizeof(Queue_node));
    initialiseNode(node);

    return node;
}

void initialiseNode(Queue_node *node) {
    node->next = NULL;
    node->value = 0;
}

int isEmpty(Queue_node *node) {
    if(node->next == NULL)
        return 1;
    
    return 0;
}

int isFull() {


}

void push(Queue_node *node, int value) {
    Queue_node *currentNodePtr = node;

    while(currentNodePtr->next != NULL) {
        currentNodePtr = currentNodePtr->next;
    }

    currentNodePtr->value = value;
    currentNodePtr->next = malloc(sizeof(Queue_node));
    initialiseNode(currentNodePtr->next);
}

int pop(Queue_node **node) {
    int result = (*node)->value;
    *node = (*node)->next;

    return result;
}

void peek() {

}

int length() {

}

void destroy() {

}