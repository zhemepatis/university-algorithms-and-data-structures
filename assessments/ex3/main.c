#include <stdio.h>
#include <time.h>

#include "queue.h"
#include "stack.h"
#include "io.h"

#define DAY_NUM 20

double getRandomNum(int lowerBound, int upperBound);

double lifoCalculateAccountingPrice(stack *storage, stack *prices);
void lifoSellCrops(stack *storage, stack *prices, double amount);

double fifoDailyProfit(queue *storage, queue *prices, double amount, double salesMarkup);


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
    stack *lifoCropAmounts = stackCreate(DAY_NUM);
    stack *lifoCropPrices = stackCreate(DAY_NUM);
    double overallFifoProfit = .0;
    double overallLifoProfit = .0;
    
    queue fifoCropAmounts;
    initialiseQueue(&fifoCropAmounts);
    queue fifoCropPrices;
    initialiseQueue(&fifoCropPrices);

    double cropsLeft = .0;
    double overallCropsSold = .0;

    fprintf(out, "\t--- DAILY REPORTS ---\n\n");
    for(int i = 0; i < DAY_NUM; ++i) {
        double cropsBought = getRandomNum(amountRate*(1.0-maxAmountDeviation), amountRate*(1.0+maxAmountDeviation));
        push(lifoCropAmounts, cropsBought);
        enqueue(&fifoCropAmounts, cropsBought);
        cropsLeft += cropsBought;

        double purchasePrice = getRandomNum(priceRate*(1.0-maxPriceDeviation), priceRate*(1.0+maxPriceDeviation));
        push(lifoCropPrices, purchasePrice);
        enqueue(&fifoCropPrices, purchasePrice);

        double cropsSold = getRandomNum(0, 100)/100*cropsLeft;
        overallCropsSold += cropsSold;
        
        double lifoSellingPrice = lifoCalculateAccountingPrice(lifoCropAmounts, lifoCropPrices);
        lifoSellCrops(lifoCropAmounts, lifoCropPrices, cropsSold);
        double lifoProfit = lifoSellingPrice * cropsSold * (1 + salesMarkup);
        overallLifoProfit += lifoProfit;

        double fifoProfit = fifoDailyProfit(&fifoCropAmounts, &fifoCropPrices, cropsSold, salesMarkup);
        overallFifoProfit += fifoProfit;

        cropsLeft -= cropsSold;
        printDailyReport(out, i+1, cropsBought, purchasePrice, cropsSold, lifoProfit, fifoProfit);
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

double getRandomNum(int lowerBound, int upperBound) {
    srand(time(0));
    return rand() % (upperBound - lowerBound + 1) + lowerBound;
}

double lifoCalculateAccountingPrice(stack *storage, stack *prices) {
    stack *tempStorage = stackClone(storage);
    stack *tempPrices = stackClone(prices);
    int size = stackCount(tempStorage);

    double overallBought = .0;
    double overallSpent = .0;
    
    for(int i = 0; i < size; ++i) {
        double currAmount = pop(tempStorage);
        overallBought += currAmount;
        double currPrice = pop(tempPrices);
        overallSpent += currPrice*currAmount;
    }

    return overallSpent/overallBought;
}

void lifoSellCrops(stack *storage, stack *prices, double amount) {
    while(amount != 0){
        double currPart = pop(storage);

        if(currPart > amount) {
            currPart -= amount;
            amount = 0.0;
            push(storage, currPart);
        }
        else if(currPart <= amount) {
            amount -= currPart;
            double temp = pop(prices); // needed to delete price
        }
    }
}

double fifoDailyProfit(queue *storage, queue *prices, double amount, double salesMarkup) {
    double profit = .0;

    while(amount != 0.0) {
        double currPart;
        dequeue(storage, &currPart);

        if(currPart > amount) {
            double tempPrice;
            peekQueue(*prices, &tempPrice);
            profit += amount*tempPrice;

            currPart -= amount;
            amount = 0.0;

            queue tempQueue = cloneQueue(*storage);
            destroyQueue(storage);
            initialiseQueue(storage);

            int queueSize = queueLength(tempQueue);
            enqueue(storage, currPart);
            for(int i = 0; i < queueSize; ++i) {
                double temp;
                dequeue(&tempQueue, &temp);
                enqueue(storage, temp);
            }

            destroyQueue(&tempQueue);
        }
        else if(currPart <= amount) {
            amount -= currPart;

            double tempPrice;
            dequeue(prices, &tempPrice); // needed to delete price
            profit += currPart*tempPrice;
        }
    }

    return profit*(1+salesMarkup);
} 
