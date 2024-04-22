#include"files.h"
#include"GuideMe.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include<unordered_map>
using namespace std;

int main() {
    files fileReader;
    unordered_map<string, vector<Edge>> graph = fileReader.createGraphFromFile("TransportationMap.txt");

    // Print the adjacency list
    for (const auto& entry : graph) {
        cout << "From " << entry.first << " to:" << endl;
        for (const auto& edge : entry.second) {
            cout << "    " << edge.destination << ": ";
            for (const auto& pair : edge.transportationPrices) {
                cout << pair.first << " $" << pair.second << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}