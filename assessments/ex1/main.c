#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void test(char *str, queue data);

int main() {
    queue testQueue;
    initialiseQueue(&testQueue);
    test("Initialisation", testQueue);

    enqueue(&testQueue, 69);
    test("1 enqueue", testQueue);

    enqueue(&testQueue, 42);
    test("2 enqueue", testQueue);

    enqueue(&testQueue, 53);
    test("3 enqueue", testQueue);

    printf("Peek: %d\n\n", peek(testQueue));

    int result;
    dequeue(&testQueue, &result);
    test("1 dequeue", testQueue);

    dequeue(&testQueue, &result);
    test("2 dequeue", testQueue);

    dequeue(&testQueue, &result);
    test("3 dequeue", testQueue);

    return 0;
}

void test(char *str, queue data) {
    printf("*** %s ***\n", str);

    printf("Length: %d\n", queueLength(data));

    printf("Front: %d\n", data.front);
    if(data.front != NULL)
        printf("Front value: %d\n", (data.front)->value);

    printf("Rear: %d\n", data.rear);
    if(data.rear != NULL)
        printf("Rear value: %d\n", (data.rear)->value);

    printf("\n");
}