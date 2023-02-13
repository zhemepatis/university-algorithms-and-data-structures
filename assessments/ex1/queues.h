#ifndef QUEUES_H
    #define QUEUES_H

    typedef struct Queue_node {
        int value;
        struct Queue_node *next;
    } Queue_node;

    Queue_node *createQueue();
    void initialiseNode(Queue_node *node);
    void push(Queue_node *node, int value);
    int pop(Queue_node **node);

#endif