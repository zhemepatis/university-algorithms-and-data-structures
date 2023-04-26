#include "stack.h"

stack* stackCreate(int capacity){

    if (capacity >= 0){
        stack *pointer = (stack*) malloc(sizeof(stack));
        pointer->data = (DATA*) malloc(sizeof(DATA) * capacity);
        pointer->capacity = capacity;
        pointer->SP = -1;
        return pointer;
    }
    else
        return NULL;
}

char stackIsEmpty(stack *pointer){
    
    if (pointer->SP == -1)
        return 1;
    else
        return 0;
}

char stackIsFull(stack *pointer){

    if (pointer->capacity == pointer->SP + 1)
        return 1;
    else
        return 0;
}

int stackCount(stack *pointer){

    return pointer->SP + 1;
}

char push(stack *pointer, DATA data){

    if(pointer->capacity == pointer->SP + 1)
        return -1;
    
    pointer->SP++;
    pointer->data[pointer->SP] = data;

    return 0;
}

DATA pop(stack *pointer){

    if(pointer->SP == -1)
        return 0;

    DATA temp = pointer->data[pointer->SP];
    pointer->data[pointer->SP] = 0;
    pointer->SP--;

    return temp;
}

void stackDestroy(stack **pointer){

    free((*pointer)->data);
    *pointer = NULL;
}

char *stackToString(stack *pointer){

    char *string = (char*)malloc(sizeof(char) * pointer->capacity);
    int j = 0;

    for(int i=pointer->SP;i>=0;i--){
        string[j] = pointer->data[i];
        j++;
    }

    string[j] = '\0';

    return string;
}

stack *stackClone(stack *pointer){

    stack *new = (stack*) malloc(sizeof(stack));
    new->data = (DATA*) malloc(sizeof(DATA) * pointer->capacity);
    new->capacity = pointer->capacity;
    new->SP = pointer->SP;

    for(int i=0;i<=pointer->SP;i++)
        new->data[i] = pointer->data[i];

    return new;
}

void stackMakeEmpty(stack *pointer){

    for(int i=0;i<=pointer->SP;i++)
        pointer->data[i] = 0;

    pointer->SP = -1;
}
