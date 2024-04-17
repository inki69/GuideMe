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

// Function to read data from file and create a graph
vector<Edge> createGraphFromFile(const string& filename) {
    ifstream file("TransportationMap.txt");
    vector<Edge> edges;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return edges;
    }

    int numEdges;
    file >> numEdges; // Read number of edges

    string line,source,destination;
    getline(file, line); // Consume the newline character after reading numEdges

    // Read transportation options from file
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, source, '-');
        ss >> destination;

        double uber = -1, bus = -1, microbus = -1, metro = -1, train = -1;
        string mode;
        double price;

        while (ss >> mode >> price) {
            if (mode == "Uber") {
                uber = price;
            }
            else if (mode == "Bus") {
                bus = price;
            }
            else if (mode == "Microbus") {
                microbus = price;
            }
            else if (mode == "Metro") {
                metro = price;
            }
            else if (mode == "Train") {
                train = price;
            }
        }

        edges.push_back(Edge(source, destination, uber, bus, microbus, metro, train));
        // Assuming the graph is undirected, no need to add reverse edges
    }

    file.close();
    return edges;
}

int main() {
    vector<Edge> edges = createGraphFromFile("TransportationMap.txt");

    // Print the graph
    for (const Edge& edge : edges) {
        cout << "From " << edge.source << " to " << edge.destination << ":";
        cout << " Uber Price: " << edge.uberPrice << ", Bus Price: " << edge.busPrice;
        cout << ", Microbus Price: " << edge.microbusPrice << ", Metro Price: " << edge.metroPrice;
        cout << ", Train Price: " << edge.trainPrice << endl;
    }

    return 0;
}
