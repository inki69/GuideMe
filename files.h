#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include<unordered_map>
using namespace std;
// Structure to represent an edge (transportation option) in the graph
struct Edge {
    
    string destination;     // Destination city
    double uber;    // Price of Uber transportation
    double bus;     // Price of Bus transportation
    double microbus;// Price of Microbus transportation
    double metro;   // Price of Metro transportation
    double train;   // Price of Train transportation

    Edge(string dest, double uber, double bus, double microbus, double metro, double train)
        :  destination(dest), uber(uber), bus(bus),
        microbus(microbus), metro(metro), train(train) {}

};
class files
{

    // Function to read data from file and create a graph
public:
    unordered_map<string, vector<Edge>> createGraphFromFile(const string& filename);
    void addEdge(unordered_map<string, vector<Edge>>& adjList, const string& source, const Edge& edge);
};