#ifndef QUEUE_H
    #define QUEUE_H

    typedef struct Queue {
        int value;
        struct Queue *next;
    } Queue;

    Queue *createQueue();
    void initialiseNode(Queue *node);
    void push(Queue *node, int value);
    int pop(Queue **node);
    int length(Queue *node);

#endif