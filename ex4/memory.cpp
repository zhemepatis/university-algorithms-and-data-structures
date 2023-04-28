#include <iostream>
#include <algorithm>

#include "./memory.hpp"

void reallocArr(double ***arr, int newSize) {
    *arr = (double **) realloc(*arr, newSize*sizeof(double *));

    for(int i = 0; i < newSize; ++i) {
        (*arr)[i] = (double *) realloc((*arr)[i], newSize*sizeof(double));
    }
    
    double *startPtr = (*arr)[newSize-1];
    double *endPtr = &((*arr)[newSize-1][newSize-1]);
    fill(startPtr, endPtr, 0);
}

void freeArr(double ***arr, int size) {
    for(int i = 0; i < size; ++i) {
        free((*arr)[i]);
    }
    free(*arr);
}