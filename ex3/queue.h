#ifndef QUEUE_H
    #define QUEUE_H
    #define MAX_QUEUE_LENGTH 30
    #define MAX_NODE_COUNT_IN_STRING 8
    #define MAX_INT_DIGITS 11

    typedef struct node {
        double value;
        struct node *next;
    } queue_node;

    typedef struct queue {
        queue_node *front;
        queue_node *rear;
    } queue;

    void initialiseQueue(queue *data);
    double enqueue(queue *data, double value);
    int dequeue(queue *data, double *storage);
    int peekQueue(queue data, double *storage);
    int queueLength(queue data);
    void destroyQueue(queue *data);
    int queueIsEmpty(queue data);
    int queueIsFull(queue data);
    void makeEmptyQueue(queue data);
    queue cloneQueue(queue data);
    char *convertQueueToString(queue data);

#endif