#include"files.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;


int main() {


    files fileHandler; // Create an instance of the files class
    vector<Edge> edges = fileHandler.createGraphFromFile("TransportationMap.txt");

    // Print the graph
    for (const Edge& edge : edges) {
        cout << "From " << edge.source << " to " << edge.destination << ":";
        cout << " Uber Price: " << edge.uberPrice << ", Bus Price: " << edge.busPrice;
        cout << ", Microbus Price: " << edge.microbusPrice << ", Metro Price: " << edge.metroPrice;
        cout << ", Train Price: " << edge.trainPrice << endl;
    }

    return 0;
}