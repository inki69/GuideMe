#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include"files.h"
#include"GuideMe.h"

using namespace std;

unordered_map<string, vector<Edge>> files::createGraphFromFile(const string& filename) {
    ifstream file(filename);
    unordered_map<string, vector<Edge>> adjacencyList;
    GuideMe method;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return adjacencyList;
    }

    int numEdges;
    file >> numEdges; // Read number of edges

    string line, source, destination;

    // Consume the newline character after reading numEdges
    getline(file, line);

    // Read transportation options from file
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, source, ' ');
        ss.ignore(2);
        ss >> destination;

        double uber = -1, bus = -1, microbus = -1, metro = -1, train = -1;
        string transportationType;
        double price;

        while (ss >> transportationType >> price) {
            if (transportationType == "Uber") {
                uber = price;
            }
            else if (transportationType == "Bus") {
                bus = price;
            }
            else if (transportationType == "Microbus") {
                microbus = price;
            }
            else if (transportationType == "Metro") {
                metro = price;
            }
            else if (transportationType == "Train") {
                train = price;
            }
        }


        Edge newEdge(destination, uber, bus, microbus, metro, train);
        method.addEdge(adjacencyList, source, newEdge);
    }


    file.close();
    return adjacencyList;
}
