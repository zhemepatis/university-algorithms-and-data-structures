#include <stdio.h>

int sum(int num1, int num2);
int divisionWithRemainder(int num1, int num2, double *result);

int main() {
    int a = 4;
    int b = 5;
    int result = sum(a, b);

    printf("%d\n", result);

    return 0;
}

int sum(int num1, int num2) {
    return  num1 + num2;
}

int divisionWithRemainder(int num1, int num2, double *result) {
    if (!result || !num2)
        return 1;

    *result = (double) num1 / (double) num2;

    return 0;
}
