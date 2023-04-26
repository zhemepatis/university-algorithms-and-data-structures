#ifndef QUEUE_H
    #define QUEUE_H
    #define MAX_QUEUE_LENGTH 10
    #define MAX_NODE_COUNT_IN_STRING 8
    #define MAX_INT_DIGITS 11

    typedef struct node {
        int value;
        struct node *next;
    } queue_node;

    typedef struct queue {
        queue_node *front;
        queue_node *rear;
    } queue;

    void initialiseQueue(queue *data);
    int enqueue(queue *data, int value);
    int dequeue(queue *data, int *storage);
    int peekQueue(queue data, int *storage);
    int queueLength(queue data);
    void destroyQueue(queue *data);
    int queueIsEmpty(queue data);
    int queueIsFull(queue data);
    void makeEmptyQueue(queue data);
    queue cloneQueue(queue data);
    char *convertQueueToString(queue data);

#endif