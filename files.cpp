#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "files.h"
#include "GuideMe.h"

using namespace std;

unordered_map<string, vector<Edge>> files::createGraphFromFile(const string& filename) {
    ifstream file(filename);
    unordered_map<string, vector<Edge>> adjacencyList;

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
        ss.ignore(2); // Ignore two characters (dash and space)
        ss >> destination;

        unordered_map<string, double> transportationPrices;
        string transportationType;
        double price;

        while (ss >> transportationType >> price) {
            transportationPrices[transportationType] = price;
        }

        Edge newEdge(destination, transportationPrices);
        fileEdge(adjacencyList, source, newEdge);
    }

    file.close();
    return adjacencyList;
}

void files::fileEdge(unordered_map<string, vector<Edge>>& graph, const string& source, const Edge& edge) {
    graph[source].push_back(edge);

    // Create a new Edge object with the reverse direction (destination to source)
    unordered_map<string, double> reverseTransportationPrices;
    for (const auto& pair : edge.transportationPrices) {
        reverseTransportationPrices[pair.first] = pair.second;
    }
    Edge reverseEdge(source, reverseTransportationPrices);
    graph[edge.destination].push_back(reverseEdge);
}