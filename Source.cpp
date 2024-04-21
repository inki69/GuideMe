#include"files.h"
#include"GuideMe.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include<unordered_map>
using namespace std;

int main() {
    files fileHandler;
    string filename = "TransportationMap.txt";
    unordered_map<string, vector<Edge>> adjacencyList =fileHandler. createGraphFromFile(filename);

    // Display the adjacency list
    for (const auto& kvp : adjacencyList) {
        const string& source = kvp.first;
        const vector<Edge>& edges = kvp.second;

        cout << "Source: " << source << endl;
        for (const auto& edge : edges) {
            cout << "  Destination: " << edge.destination << endl;
            cout << "  Uber: " << edge.uber << endl;
            cout << "  Bus: " << edge.bus << endl;
            cout << "  Microbus: " << edge.microbus << endl;
            cout << "  Metro: " << edge.metro << endl;
            cout << "  Train: " << edge.train << endl;
        }
        cout << endl;
    }

    return 0;
}