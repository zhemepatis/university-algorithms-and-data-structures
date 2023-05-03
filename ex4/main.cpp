#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <math.h>

#include "./io.hpp"
#include "./memory.hpp"

using namespace std;

class GraphNode {
    public: 
        int index;
        double sum;
        vector <int> route;
};

int getElementIndex(vector <string> elmentList, string element);
int getCity(string label, vector <string> cityList);

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

    // getting route start and destination
    int startIndex = getCity("starting point", cityList);
    int destIndex = getCity("destination", cityList);
    
    // searching for the cheapest route
    stack <GraphNode> nodes;
    GraphNode firstNode;

    firstNode.index = startIndex;
    firstNode.sum = 0;
    firstNode.route.push_back(startIndex);

    nodes.push(firstNode);

    int cityNum = cityList.size();
    bool isVisited[cityNum] = {false};
    isVisited[startIndex] = true;
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

            cheapestRoute.clear();
            copy(travelledRoute.begin(), travelledRoute.end(), back_inserter(cheapestRoute));

            continue;
        }

        for(int i = 0; i < cityNum; ++i) {
            if(!isVisited[i] && tripCosts[currCityIndex][i] != 0) {        
                GraphNode tempNode;

                tempNode.index = i;
                tempNode.sum = currSum + tripCosts[currCityIndex][i];
                copy(travelledRoute.begin(), travelledRoute.end(), back_inserter(tempNode.route));
                tempNode.route.push_back(i);

                nodes.push(tempNode);
                
                isVisited[i] = true;
            }
        }
    }
    freeArr(&tripCosts, cityList.size());

    // printing results
    if(result == -1) {
        fr << "There is no possibility to get from " << cityList[startIndex] << " to " << cityList[destIndex] << '\n';
        return 0;
    }

    int routeLength = cheapestRoute.size();
    fr << "Cheapest route: ";
    for(int i = 0; i < routeLength; ++i) {
        fr << cityList[cheapestRoute[i]] << " ";
    }
    fr << "\nRoute price: " << result;

    return 0;
}

int getCity(string label, vector <string> cityList) {
    int cityNum = cityList.size();
    int cityIndex = -1;

    while(cityIndex == -1) {
        string startingPoint;
        cout << "Enter " << label << ": ";
        cin >> startingPoint;
        cityIndex = getElementIndex(cityList, startingPoint);

        if(cityIndex == -1)
            cout << "Incorrect city name.\n";
    }

    return cityIndex;
}

int getElementIndex(vector <string>  elmentList, string element) {
    vector <string> :: iterator it = find(elmentList.begin(), elmentList.end(), element);

    if(it != elmentList.end())
        return abs(distance(it, elmentList.begin()));

    return -1;
}