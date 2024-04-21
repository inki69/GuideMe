#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include"files.h"
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


        Edge newEdge(destination, uber, bus, microbus, metro, train);
        addEdge(adjacencyList, source, newEdge);
        addEdge(adjacencyList, destination, Edge(source, newEdge.uber, newEdge.bus, newEdge.microbus, newEdge.metro, newEdge.train));
        /* adjacencyList[source].push_back(newEdge);
         bool exist = false;
         string old;
         for (const auto& kvp : adjacencyList) {
             if (kvp.first == destination) {
                 exist = true;
                 old = kvp.first;
             }
         }
         if (exist) {
             adjacencyList[old].push_back(Edge(source, newEdge.uber, newEdge.bus, newEdge.microbus, newEdge.metro, newEdge.train));
         }
         else {

            adjacencyList[newEdge.destination].push_back(Edge(source, newEdge.uber, newEdge.bus, newEdge.microbus, newEdge.metro, newEdge.train));
         }
         */
    }


    file.close();
    return adjacencyList;
}



// Function to add an edge to the adjacency list
void files::addEdge(unordered_map<string, vector<Edge>>& adjList, const string& source, const Edge& edge) {
    adjList[source].push_back(edge);
    adjList[edge.destination].push_back(Edge(source, edge.uber, edge.bus, edge.microbus, edge.metro, edge.train));
}
