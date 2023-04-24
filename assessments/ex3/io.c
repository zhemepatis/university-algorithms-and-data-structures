#include <stdio.h>
#include <string.h>

#include "io.h"

FILE *openFile(char *filename, char *mode) {
    FILE *stream = fopen(filename, mode);

    printf("Opening input file: %s\n", filename);
    if(!stream) {
        char* msg = strcat("unable to open ", filename);
        printErr(msg);
        return 0;
    }

    return stream;
}

double getLineInput(FILE *stream) {
    double input;
    fscanf(stream, "%lf%*[^\n]%*c", &input);
    return input;
}

void printErr(char *msg) {
    printf("Error: %s\n", msg);
}

void printDailyReport(FILE *stream, int day, double cropsBought, double purchasePrice, double cropsSold, double lifoSellingPrice, double fifoSellingPrice, double profit) {
    fprintf(stream, "DAY - %d\n", day);
    fprintf(stream, "\tCrops were bought: %.2lf (t)\n", cropsBought);
    fprintf(stream, "\tPurchase price: %.2lf (eur)\n", purchasePrice);
    fprintf(stream, "\tCrops sold: %.2lf (t)\n", cropsSold);
    fprintf(stream, "\tSelling price (LIFO): %.2lf (eur)\n", lifoSellingPrice);
    fprintf(stream, "\tSelling price (FIFO): %.2lf (eur)\n", fifoSellingPrice);
    fprintf(stream, "\tDaily profit: %.2lf (eur)\n", profit);
}

void printSummaryReport(FILE *stream, double cropsSold, double profit) {
    fprintf(stream, "\tOverall crops sold: %.2f (t)\n", cropsSold);
    fprintf(stream, "\tOverall profit: %.2f (eur)\n", profit);
}
