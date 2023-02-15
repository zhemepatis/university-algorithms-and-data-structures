#ifndef QUEUE_H
    #define QUEUE_H

    typedef struct node {
        int value;
        struct node *next;
    } queue_node;

    typedef struct queue {
        queue_node *front;
        queue_node *rear;
    } queue;

    void initialiseQueue(queue *data);
    void enqueue(queue *data, int value);
    int dequeue(queue *data, int *storage);
    int peek(queue data);
    int queueLength(queue data);




#endif