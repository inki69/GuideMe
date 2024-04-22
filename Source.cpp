#include"files.h"
#include"GuideMe.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include<unordered_map>
using namespace std;

int main() {
    files fileReader;
    unordered_map<string, vector<Edge>> graph = fileReader.createGraphFromFile("TransportationMap.txt");
    GuideMe method;

    // Print the original adjacency list
    cout << "Original Adjacency List:" << endl;
    for (const auto& entry : graph) {
        cout << "From " << entry.first << " to:" << endl;
        for (const auto& edge : entry.second) {
            cout << "    " << edge.destination << ": ";
            for (const auto& pair : edge.transportationPrices) {
                cout << pair.first << " $" << pair.second << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    // Prompt the user to provide input for updating transportation options
    string source, destination;
    cout << "Enter source city: ";
    cin >> source;
    cout << "Enter destination city: ";
    cin >> destination;

    string transportation;
    cout << "Enter the transportation type you want to update : ";
    cin >> transportation;

    int newCost;
    cout << "Enter the updated price for " << transportation << " from " << source << " to " << destination << ": ";
    cin >> newCost;

    // Update transportation options
    GuideMe guide;
    guide.updateEdge(graph, source, destination, transportation, newCost);

    for (const auto& entry : graph) {
        const string& source = entry.first;
        const vector<Edge>& edges = entry.second;
        for (const auto& edge : edges) {
            cout << "From " << source << " to " << edge.destination << ":" << endl;
            for (const auto& pair : edge.transportationPrices) {
                cout << "  " << pair.first << ": " << pair.second << endl;
            }
        }
    }
   
    return 0;
}
