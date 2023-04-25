#ifndef IO_H
    #define IO_H

    FILE *openFile(char *filename, char *mode);
    double getLineInput(FILE *stream);

    void printErr(char *msg);
    void printDailyReport(FILE *stream, int day, double cropsBought, double purchasePrice, double cropsSold, double lifoProfit, double fifoProfit);
    void printSummaryReport(FILE *stream, double cropsSold, double profit);

#endif