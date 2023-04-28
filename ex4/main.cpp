#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <math.h>

using namespace std;

void printErr(string msg);
void printArr(double **arr, int arrSize);

void reallocArr(double ***arr, int newSize);
void freeArr(double ***arr, int size);

int getElementIndex(vector <string> vector, string element);

class GraphNode {
    public: 
        int index;
        double sum;
        vector <int> route;
};

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

    // getting data
    vector <string> cityList;
    double **tripCosts = NULL;
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
    int cityNum = cityList.size();


    int destIndex = 2;
    int srcIndex = 3;
    
    // searching for the cheapest route
    stack <GraphNode> nodes;
    GraphNode firstNode;

    firstNode.index = srcIndex;
    firstNode.sum = 0;
    firstNode.route.push_back(srcIndex);

    nodes.push(firstNode);

    bool isVisited[cityNum] = {false};
    double result = -1;
    vector <int> cheapestRoute;

    while(!nodes.empty()) {
        GraphNode currNode = nodes.top();
        nodes.pop();

        int currCityIndex = currNode.index;
        double currSum = currNode.sum;
        vector <int> travelledRoute = currNode.route;


        if(currCityIndex == destIndex && (result == -1 || result > currSum)) {
            result = currSum;
            cout << "Current node: " << currCityIndex << " " << currSum << endl;

            cheapestRoute.clear();
            copy(travelledRoute.begin(), travelledRoute.end(), back_inserter(cheapestRoute));

            continue;
        }

        for(int i = 0; i < cityNum; ++i) {
            if(!isVisited[i] && tripCosts[currCityIndex][i] != 0) {        
                GraphNode tempNode;

                tempNode.index = i;
                tempNode.sum = currSum + tripCosts[currCityIndex][i];
                travelledRoute.push_back(i);
                copy(travelledRoute.begin(), travelledRoute.end(), back_inserter(tempNode.route));

                nodes.push(tempNode);
                
                isVisited[i] = true;
            }
        }
    }
    freeArr(&tripCosts, cityList.size());

    // printing results
    int routeLength = cheapestRoute.size();
    fr << "Cheapest route: ";
    for(int i = 0; i < routeLength; ++i) {
        fr << cityList[cheapestRoute[i]] << " ";
    }
    fr << "\nRoute price: " << result;

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

int getElementIndex(vector <string> vector, string element) {
    auto it = find(vector.begin(), vector.end(), element);

    if(it != vector.end())
        return abs(distance(it, vector.begin()));

    return -1;
}