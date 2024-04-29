#include "GuideMe.h"
#include <unordered_set>
#include <set>
#include <vector>
#include <string>
using namespace std;

void GuideMe::addEdge(unordered_map<string, vector<Edge>>& graph, const string& source, const string& destination, const string& transportationType, const int& price) {
    addEdgeHelper(graph, source, destination, transportationType, price);
    addEdgeHelper(graph, destination, source, transportationType, price);
}

void GuideMe::addEdgeHelper(unordered_map<string, vector<Edge>>& graph, const string& source, const string& destination, const string& transportationType, const int& price) {
    // Check if there is an existing edge between source and destination
    if (graph.find(source) != graph.end()) {
        vector<Edge>& edges = graph[source];
        for (Edge& edge : edges) {
            if (edge.destination == destination) {
                // Edge already exists, update transportation prices
                edge.transportationPrices[transportationType] = price;
                return; // Exit the function
            }
        }
    }

    // If no existing edge found, create a new one and add it to the graph
    Edge newEdge(destination, { {transportationType, price} });
    graph[source].push_back(newEdge);
}


void GuideMe::updateEdge(unordered_map<string, vector<Edge>>& graph) {

    int newCost;
    string transportation;
    char choice;
    do {

        string source, destination;
        cout << "Enter source city: ";
        cin >> source;
        cout << "Enter destination city: ";
        cin >> destination;
        cout << "Enter the transportation type you want to update : ";
        cin >> transportation;
        cout << "Enter the updated price for " << transportation << " from " << source << " to " << destination << ": ";
        cin >> newCost;
        updateEdgehelper(graph, source, destination, transportation, newCost);
        updateEdgehelper(graph, destination, source, transportation, newCost);
        cout << "Do you want to update another transportation ? (y/n): ";
        cin >> choice;


    } while ((choice == 'y' || choice == 'Y'));


}

void GuideMe::updateEdgehelper(unordered_map<string, vector<Edge>>& graph, const string& source, const string& destination, string transportation, int newCost) {


    auto sourceIt = graph.find(source);
    if (sourceIt == graph.end()) {
        cerr << "Error: Source city '" << source << "' not found." << endl;
        return;
    }

    // Find the edge corresponding to the destination and source
    vector<Edge>& edges = sourceIt->second;
    auto edgeIt = edges.end();  // Initialize edgeIt to the end iterator as a default value

    // Iterate over the edges vector
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        // Check if the destination of the current Edge matches the provided destination
        if (it->destination == destination) {
            // If found, update edgeIt and break out of the loop
            edgeIt = it;
            break;
        }
    }


    if (edgeIt == edges.end()) {
        cerr << "Error: Destination city '" << destination << "' not reachable from '" << source << "'." << endl;
        return;
    }

    // Update the corresponding transportation price for the specified destination
    auto& transportationPrices = edgeIt->transportationPrices;
    if (transportationPrices.find(transportation) != transportationPrices.end()) {
        transportationPrices[transportation] = newCost;
        cout << transportation << " price from " << source << " to " << destination << " updated successfully." << endl;
    }
    else {
        cerr << "Error: Transportation type '" << transportation << "' not found for the specified destination." << endl;
    }
}

void GuideMe::deleteEdge(unordered_map<string, vector<Edge>>& graph) {
    string source, destination;
    cout << "Enter source city: ";
    cin >> source;
    cout << "Enter destination city: ";
    cin >> destination;


    vector<string> transportations;
    char choice;
    do {
        string transportation;
        cout << "Enter transportation type to delete: ";
        cin >> transportation;
        transportations.push_back(transportation);
        cout << "Do you want to delete another transportation type? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    for (const auto& transportation : transportations) {
        deleteEdgehelper(graph, source, destination, transportation);
        deleteEdgehelper(graph, destination, source, transportation);
    }
}

void GuideMe::deleteEdgehelper(unordered_map<string, vector<Edge>>& graph, const string& source, const string& destination, const string& transportation) {
    auto it = graph.find(source);
    if (it != graph.end()) {
        vector<Edge>& edges = it->second;
        for (auto& edge : edges) {
            if (edge.destination == destination) {
                auto priceIt = edge.transportationPrices.find(transportation);
                if (priceIt != edge.transportationPrices.end()) {
                    edge.transportationPrices.erase(priceIt);
                    cout << "Transportation type '" << transportation << "' deleted successfully from edge " << source << " to " << destination << endl;
                    return;
                }
                else {

                    cout << "Error: Edge not found or specified transportation type not present!" << endl;
                    deleteEdge(graph);

                }
            }
        }
    }
    else {

        cout << "Error: Edge not found or specified transportation type not present!" << endl;
        deleteEdge(graph);

    }

    //// Prompt user for input again until valid inputs are provided
    //string newSource, newDestination, newTransportation;
    //cout << "Enter correct source: ";
    //cin >> newSource;
    //cout << "Enter correct destination: ";
    //cin >> newDestination;
    //vector<string> transportations;

    //char choice;
    //do {
    //   
    //    cout << "Enter transportation type to delete: ";
    //    cin >> newTransportation;
    //    transportations.push_back(newTransportation);
    //    cout << "Do you want to delete another transportation type? (y/n): ";
    //    cin >> choice;
    //} while (choice == 'y' || choice == 'Y');

    //// Recursively call deleteEdgehelper with new inputs
    //deleteEdgehelper(graph, newSource, newDestination, newTransportation);
}

bool GuideMe::isCompleteMap(unordered_map<string, vector<Edge>>& graph) {
    for (const auto& pair : graph) {
        const vector<Edge>& edges = pair.second;
        //Check if every other node is connected to this node
        for (const auto& other_pair : graph) {
            if (pair.first != other_pair.first) {
                bool found = false;
                for (const auto& edge : edges) {
                    if (edge.destination == other_pair.first) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    //  If any other node is not connected to this node, graph is not complete
                    return false;
                }
            }
        }
    }
    return true;
}

bool GuideMe::isConnectedMap(unordered_map<string, vector<Edge>>& graph) {

    if (graph.empty()) return false; // If the graph has no nodes, it's not connected

    unordered_set<string> visited; // Set to store visited nodes
    queue<string> queue; // Queue for BFS traversal

    // Start BFS traversal from the first node in the adjacency list
    queue.push(graph.begin()->first);
    visited.insert(graph.begin()->first);

    // BFS traversal
    while (!queue.empty()) {
        string current = queue.front();
        queue.pop();

        // Visit all neighbors of the current node
        for (const Edge& edge : graph[current]) {
            if (visited.find(edge.destination) == visited.end()) {
                queue.push(edge.destination);
                visited.insert(edge.destination);
            }
        }
    }

    // Check if all nodes are visited
    return visited.size() == graph.size();


}

void GuideMe::BFS(unordered_map<string, vector<Edge>>& graph) {
    queue<string> q;
    unordered_set<string> visited;
    string startCity;

    cout << "Enter the starting city: ";
    cin >> startCity;
    q.push(startCity);
    visited.insert(startCity);

    while (!q.empty()) {
        string currentSource = q.front();
        q.pop();
        cout << currentSource << " ";
        cout << endl;

        for (const auto& edge : graph[currentSource]) {
            string destination = edge.destination;
            if (visited.find(destination) == visited.end()) {
                visited.insert(destination);
                q.push(destination);
            }
        }
    }

}

void GuideMe::DFS(const unordered_map<string, vector<Edge>>& graph) {
    unordered_map<string, bool> visited; //visited map to keep track of visited cities/nodes
    string startCity;

    cout << "Enter the starting city: ";
    cin >> startCity;

    //checking if starting city exists in the graph or no
    if (graph.find(startCity) == graph.end()) {
        cerr << "Error: City not found in the graph." << endl; //or cout, doesnt matter in this case
        return;
    }
    //else hybda' mnha
    DFSHelper(graph, startCity, visited);
}

void GuideMe::DFSHelper(const unordered_map<string, vector<Edge>>& graph, const string& city, unordered_map<string, bool>& visited) {
    visited[city] = true;
    cout << city << " ";
    cout << endl;
    //all adjacent cities:
    for (const Edge& edge : graph.at(city)) {
        if (!visited[edge.destination]) {
            DFSHelper(graph, edge.destination, visited);
        }
    }
}

void GuideMe::printPath(const vector<string>& path) {
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

// Modified DFS to find all paths between two vertices in an undirected graph
void GuideMe::dfsAllPaths(const string& current, const string& destination, const unordered_map<string, vector<Edge>>& graph, unordered_set<string>& visited, vector<string>& path) {
    visited.insert(current);
    path.push_back(current);

    if (current == destination) {
        printPath(path);
    }
    else {
        for (const auto& edge : graph.at(current)) {
            string nextDestination = edge.destination;
            if (visited.find(nextDestination) == visited.end()) {
                dfsAllPaths(nextDestination, destination, graph, visited, path);
            }
        }
    }

    visited.erase(current);
    path.pop_back();
}

// Function to find all paths between two vertices in an undirected graph
void GuideMe::findAllPaths(const string& source, const string& destination, const unordered_map<string, vector<Edge>>& graph) {
    unordered_set<string> visited;
    vector<string> path;

    dfsAllPaths(source, destination, graph, visited, path);
}



