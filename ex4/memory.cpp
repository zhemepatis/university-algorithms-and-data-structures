#include <iostream>
#include <algorithm>

#include "./memory.hpp"

void reallocArr(double ***arr, int newSize) {
    double **newArr = new double *[newSize];

    for(int i = 0; i < newSize; ++i) {
        newArr[i] = new double [newSize];
    }

    for(int i = 0; i < newSize-1; ++i) {
        for(int j = 0; j < newSize-1; ++j) {
            newArr[i][j] = (*arr)[i][j];
        }
        newArr[i][newSize-1] = 0;
        newArr[newSize-1][i] = 0;
    }

    freeArr(arr, newSize-1);
    *arr = newArr;
}

void freeArr(double ***arr, int size) {
    for(int i = 0; i < size; ++i) {
        delete [] (*arr)[i];
    }
    delete [] *arr;
}