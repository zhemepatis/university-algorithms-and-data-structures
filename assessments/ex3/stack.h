#ifndef STACK_H
    #define STACK_H

    #define DATA int
    //norint pakeisti steko saugomu duomenu tipa

    #include <stdlib.h>

    typedef struct stack {
        DATA *data;
        int capacity, SP;
    } stack;

    stack *stackCreate(int capacity);
    char stackIsEmpty(stack *pointer);
    char stackIsFull(stack *pointer);
    int stackCount(stack *pointer);
    char push(stack *pointer, DATA data);
    DATA pop(stack *pointer);
    void stackDestroy(stack **pointer);
    char *stackToString(stack *pointer);
    stack *stackClone(stack *pointer);
    void stackMakeEmpty(stack *pointer);

#endif
