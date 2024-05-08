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
    unordered_map<string, vector<Edge>> graph;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return graph;
    }

    int numEdges;
    file >> numEdges; //reading number of edges

    string line, source, destination;

    //consuming the newline character after reading numEdges
    getline(file, line);

    //reading transportation options from file
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, source, ' ');
        ss.ignore(2); //ignoring two characters (dash and space)
        ss >> destination;

        unordered_map<string, double> transportationPrices;
        string transportationType;
        double price;

        while (ss >> transportationType >> price) {
            transportationPrices[transportationType] = price;
        }
        
        Edge newEdge(destination, transportationPrices);
        graph[source].push_back(newEdge);

        //creating a new Edge object with the reverse direction (destination to source)
        unordered_map<string, double> reverseTransportationPrices;
        for (const auto& pair : newEdge.transportationPrices) {
            reverseTransportationPrices[pair.first] = pair.second;
        }
        Edge reverseEdge(source, reverseTransportationPrices);
        graph[newEdge.destination].push_back(reverseEdge);
    }

    file.close();
    return graph;
}

void files::writeGraphToFile(const unordered_map<string, vector<Edge>>& graph, const string& filename) {
    ofstream file(filename);
    //writing the number of edges to the file
    file << graph.size() << endl;
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << " for writing." << endl;
        return;
    }

    unordered_set<string> visitedSources;  //tracking visited sources

    for (const auto& pair : graph) {
        const string& source = pair.first;
        const vector<Edge>& edges = pair.second;

        for (const Edge& edge : edges) {
            if (visitedSources.count(edge.destination) > 0) {
                //skip if the source has been entered as a destination before
                continue;
            }

            file << source << " - " << edge.destination << " ";

            for (const auto& pricePair : edge.transportationPrices) {
                file << pricePair.first << " " << pricePair.second << " ";
            }

            file << endl;

            visitedSources.insert(source);  //marking source as visited
        }
    }

    file.close();
}
