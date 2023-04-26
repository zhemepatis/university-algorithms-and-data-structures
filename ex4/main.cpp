#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

void printErr(string msg);

int getElementIndex(vector <string> vector, string element);

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
    double tripCosts[100][100] = {0};
    while(!fd.eof()) {
        string firstCity, secondCity;
        double cost;

        fd >> firstCity >> secondCity >> cost;

        int firstCityIndex = getElementIndex(cityList, firstCity);
        if(firstCityIndex == -1) {
            firstCityIndex = cityList.size();
            cityList.push_back(firstCity);
        } 

        int secondCityIndex = getElementIndex(cityList, secondCity);
        if(secondCityIndex == -1) {
            secondCityIndex = cityList.size();
            cityList.push_back(secondCity);
        }

        tripCosts[firstCityIndex][secondCityIndex] = cost;
        tripCosts[secondCityIndex][firstCityIndex] = cost;
    }

    int cityNum = cityList.size();
    for(int i = 0; i < cityNum; ++i) {
        for(int j = 0; j < cityNum; ++j) {
            cout << tripCosts[i][j] << " ";
        }
        cout << endl;
    }
    



    return 0;
}

void printErr(string msg) {
    cout << "Error: " << msg << '\n';
}

int getElementIndex(vector <string> vector, string element) {
    auto it = find(vector.begin(), vector.end(), element);

    if(it != vector.end())
        return abs(distance(it, vector.begin()));

    return -1;
}