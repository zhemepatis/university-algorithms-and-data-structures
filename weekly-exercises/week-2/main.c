#include <stdio.h>
#include <math.h>

#define TRUE (1==1)
#define FALSE (!TRUE)

typedef struct tagPOINT {
    int  x;
    int  y;
} POINT;

float calculateSideLength(POINT firstPoint, POINT secondPoint) {
    return sqrt((pow((firstPoint.x-secondPoint.x),2) + pow((firstPoint.y-secondPoint.y),2)));
}

int isRightTriangle (POINT A, POINT B, POINT C) {
    float firstSide = pow(calculateSideLength(A, B), 2);
    float secondSide = pow(calculateSideLength(B, C), 2);
    float thirdSide = pow(calculateSideLength(C, A), 2);
    
    if (firstSide && secondSide && thirdSide && (firstSide + secondSide == thirdSide || firstSide + thirdSide == secondSide || secondSide + thirdSide == firstSide)) {
        return TRUE;
    } 
    else {
        return FALSE;
    }
}

int main() {
    POINT firstPoint, secondPoint, thirdPoint;
    
    firstPoint.x = 0;
    firstPoint.y = 0;

    secondPoint.x = 1;
    secondPoint.y = 0;

    thirdPoint.x = 0;
    thirdPoint.y = 2;

    printf("%d\n", isRightTriangle(firstPoint, secondPoint, thirdPoint));



    return 0;
}