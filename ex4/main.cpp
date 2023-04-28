#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

void printErr(string msg);
void printArr(double **arr, int arrSize);

int getElementIndex(vector <string> vector, string element);
void reallocArr(double ***arr, int newSize);
void freeArr(double ***arr, int size);

int main(int argc, char **argv) {
    if(argc != 3) {
        printErr("too few arguments provided");
        return 0;
    }

    string dataFileName = argv[1];
    string resultFileName = argv[2];

    ifstream fd (dataFileName);
    cout << "Opening input file: " << dataFileName << '\n';
    if(!fd.is_open()) {
        string msg = "unable to open " + dataFileName;
        printErr(msg);
        return 0;
    }
    
    ofstream fr (resultFileName);
    cout << "Opening output file: " << resultFileName << '\n';
    if(!fr.is_open()) {
        string msg = "unable to open " + resultFileName;
        printErr(msg);
        return 0;
    }

    vector <string> cityList;
    double **tripCosts = new double*;
    while(!fd.eof()) {
        string firstCity, secondCity;
        double cost;

        fd >> firstCity >> secondCity >> cost;

        int firstCityIndex = getElementIndex(cityList, firstCity);
        if(firstCityIndex == -1) {
            firstCityIndex = cityList.size();
            cityList.push_back(firstCity);

            reallocArr(&tripCosts, cityList.size());
        } 

        int secondCityIndex = getElementIndex(cityList, secondCity);
        if(secondCityIndex == -1) {
            secondCityIndex = cityList.size();
            cityList.push_back(secondCity);

            reallocArr(&tripCosts, cityList.size());
        }

        tripCosts[firstCityIndex][secondCityIndex] = cost;
        tripCosts[secondCityIndex][firstCityIndex] = cost;
    }
    // printArr(tripCosts, cityList.size());

    
    freeArr(&tripCosts, cityList.size());

    return 0;
}

void printErr(string msg) {
    cout << "Error: " << msg << '\n';
}

void printArr(double **arr, int arrSize) {
    cout << "\nPRINTING ARRAY \n";

    for(int i = 0; i < arrSize; ++i) {
        for(int j = 0; j < arrSize; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int getElementIndex(vector <string> vector, string element) {
    auto it = find(vector.begin(), vector.end(), element);

    if(it != vector.end())
        return abs(distance(it, vector.begin()));

    return -1;
}

void reallocArr(double ***arr, int newSize) {
    *arr = (double **) realloc(*arr, newSize*sizeof(double *));
    for(int i = 0; i < newSize; ++i) {
        (*arr)[i] = (double *) realloc((*arr)[i], newSize*sizeof(double));
    }
}

void freeArr(double ***arr, int size) {
    for(int i = 0; i < size; ++i) {
        free((*arr)[i]);
    }
    free(*arr);
}