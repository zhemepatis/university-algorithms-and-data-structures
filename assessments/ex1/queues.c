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