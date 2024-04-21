#include"files.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include<unordered_map>
using namespace std;



int main() {
    files fileHandler;
    Edge edge1 = {"giza",230,60,0,30,0 };
    Edge edge2 = { "giza",0,500,345,0,0 };
    Edge edge3 = { "benisuef",0,15,20,0,0 };
    Edge edge4 = { "cairo",0,450,0,0,250 };
    Edge edge5 = { "benisuef",0,315,200,0,0 };
    unordered_map<string, vector<Edge>> adjlist;
    fileHandler.addEdge(adjlist, "cairo", edge1);
    fileHandler.addEdge(adjlist, "dahab", edge2);
    fileHandler.addEdge(adjlist, "cairo", edge3);
    fileHandler.addEdge(adjlist, "asyut", edge4);
    fileHandler.addEdge(adjlist, "dahab", edge5);
    
    string filename = "TransportationMap.txt";
    unordered_map<string, vector<Edge>> adjacencyList =fileHandler. createGraphFromFile(filename);

    // Display the adjacency list
    for (const auto& kvp : adjlist) {
        const string& source = kvp.first;
        const vector<Edge>& edges = kvp.second;

        cout << "Source: " << source << endl;
        for (const auto& edge : edges) {
            cout << "  Destination: " << edge.destination << endl;
            /*cout << "  Uber: " << edge.uber << endl;
            cout << "  Bus: " << edge.bus << endl;
            cout << "  Microbus: " << edge.microbus << endl;
            cout << "  Metro: " << edge.metro << endl;
            cout << "  Train: " << edge.train << endl;*/
        }
        cout << endl;
    }

    return 0;
}