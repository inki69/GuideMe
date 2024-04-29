#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include<unordered_map>

using namespace std;

//Struct that represents an edge
struct Edge {
    
    string destination;     // Destination city
    unordered_map<string, double> transportationPrices;

    Edge(const string& dest, const unordered_map<string, double>& prices) :
        destination(dest), transportationPrices(prices) {}
};
class files
{

public:
    unordered_map<string, vector<Edge>> createGraphFromFile(const string& filename);
    
};