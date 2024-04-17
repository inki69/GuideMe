#include "files.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
vector<Edge> files::createGraphFromFile(const string& filename) {
    ifstream file("TransportationMap.txt");
    vector<Edge> edges;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return edges;
    }

    int numEdges;
    file >> numEdges; // Read number of edges

    string line, source, destination;
    getline(file, line); // Consume the newline character after reading numEdges

    // Read transportation options from file
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, source, '-');
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

        edges.push_back(Edge(source, destination, uber, bus, microbus, metro, train));
        // Assuming the graph is undirected, no need to add reverse edges
    }

    file.close();
    return edges;
}
