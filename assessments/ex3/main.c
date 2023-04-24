#include <stdio.h>
#include <string.h>

#include "queue.h"
#include "stack.h"

#define DAY_NUM 20

FILE *openFile(char *filename, char *mode);
double getLineInput(FILE *stream);

void printErr(char *msg);
void printDailyReport(FILE *stream, int day, double cropsBought, double purchasePrice, double cropsSold, double lifoSellingPrice, double fifoSellingPrice, double profit);
void printSummaryReport(FILE *stream, double cropsSold, double profit);

double getRandomNum(int lowerBound, int upperBound);


int main(int argc, char **argv) {
    if(argc != 3) {
        printErr("too few arguments provided");
        return 0;
    }

    // getting input from data file
    char* inputFileName = argv[1];
    FILE *in = openFile(inputFileName, "r");
    char* outputFileName = argv[2];
    FILE *out = openFile(outputFileName, "w");

    double amountRate = getLineInput(in);
    double priceRate = getLineInput(in);
    double maxAmountDeviation = getLineInput(in) / 100;
    double maxPriceDeviation = getLineInput(in) / 100;
    double salesMarkup = getLineInput(in) / 100;

    // calculations
    stack lifoSaleModel;
    queue fifoSaleModel;
    double cropsLeft = .0;
    double overallFifoProfit = .0;
    double overallLifoProfit = .0;
    double overallCropsSold = .0;

    fprintf(out, "\t--- DAILY REPORTS ---\n\n");
    for(int i = 0; i < DAY_NUM; ++i) {
        double cropsBought = getRandomNum(amountRate*(1.0-maxAmountDeviation), amountRate*(1.0+maxAmountDeviation));
        cropsLeft += cropsBought;
        double purchasePrice = getRandomNum(priceRate*(1.0-maxPriceDeviation), priceRate*(1.0+maxPriceDeviation));
        double cropsSold = getRandomNum(0, 100)/100*cropsLeft;
        overallCropsSold += cropsSold;
        double lifoSellingPrice = 0.0;
        double fifoSellingPrice = 0.0;
        double profit = 0.0;

        cropsLeft -= cropsSold;
        printDailyReport(out, i+1, cropsBought, purchasePrice, cropsSold, lifoSellingPrice, fifoSellingPrice, profit);
    }
    
    // printing summary 
    fprintf(out, "\n\n\t--- SUMMARY ---\n\n");
    
    fprintf(out, "FIFO MODEL\n");
    printSummaryReport(out, overallCropsSold, overallFifoProfit);
    fprintf(out, "LIFO MODEL\n");
    printSummaryReport(out, overallCropsSold, overallLifoProfit);

    if(overallFifoProfit > overallLifoProfit)
        fprintf(out, "\nMore beneficial solution: FIFO.");
    else if(overallFifoProfit < overallLifoProfit)
        fprintf(out, "\nMore beneficial solution: LIFO.");
    else
        fprintf(out, "\nBoth solutions are equally beneficial.");

    return 0;
}

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

double getRandomNum(int lowerBound, int upperBound) {
    return rand() % (upperBound - lowerBound + 1) + lowerBound;
}
