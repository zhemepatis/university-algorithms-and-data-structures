#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

int main() {
    queue testQueue;
    initialiseQueue(&testQueue);
    printf("%s\n", convertQueueToString(testQueue));

    for(int i = 1; i <= MAX_QUEUE_LENGTH+1; ++i)
        enqueue(&testQueue, i);

    printf("%s\n", convertQueueToString(testQueue));
    
    return 0;
}

void displayData(char *str, queue data) {
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