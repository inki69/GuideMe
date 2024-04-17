#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
// Structure to represent an edge (transportation option) in the graph
struct Edge {
    string source;          // Source city
    string destination;     // Destination city
    double uberPrice;    // Price of Uber transportation
    double busPrice;     // Price of Bus transportation
    double microbusPrice;// Price of Microbus transportation
    double metroPrice;   // Price of Metro transportation
    double trainPrice;   // Price of Train transportation

    Edge(const string& src, const string& dest, double uber, double bus, double microbus, double metro, double train)
        : source(src), destination(dest), uberPrice(uber), busPrice(bus),
        microbusPrice(microbus), metroPrice(metro), trainPrice(train) {}
};
class files
{

    // Function to read data from file and create a graph
public:
    vector<Edge> createGraphFromFile(const string& filename);
};


