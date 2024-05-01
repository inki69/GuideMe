#include "GuideMe.h"
#include <unordered_set>
#include <set>
#include <vector>
#include <string>
using namespace std;


void GuideMe::addEdge(unordered_map<string, vector<Edge>>& graph) {
    string source, destination, transportationType;
    int price;
    char userChoice;

    do {
        cout << "Enter source city: ";
        cin >> source;
        cout << "Enter destination city: ";
        cin >> destination;
        cout << "Enter transportation type:";
        cin >> transportationType;
        cout << "Enter the price:";
        cin >> price;

        addEdgeHelper(graph, source, destination, transportationType, price);
        addEdgeHelper(graph, destination, source, transportationType, price);

        cout << "Do you want to add another transportation? (y/n): ";
        cin >> userChoice;
    } while (userChoice == 'y' || userChoice == 'Y');


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

//void GuideMe::DFS(const unordered_map<string, vector<Edge>>& graph) {
//    unordered_map<string, bool> visited; //visited map to keep track of visited cities/nodes
//    string startCity;
//
//    cout << "Enter the starting city: ";
//    cin >> startCity;
//
//    //checking if starting city exists in the graph or no
//    if (graph.find(startCity) == graph.end()) {
//        cerr << "Error: City not found in the graph." << endl; //or cout, doesnt matter in this case
//        return;
//    }
//    //else hybda' mnha
//    DFSHelper(graph, startCity, visited);
//}
//
//void GuideMe::DFSHelper(const unordered_map<string, vector<Edge>>& graph, const string& city, unordered_map<string, bool>& visited) {
//    visited[city] = true;
//    cout << city << " ";
//    cout << endl;
//    //all adjacent cities:
//    for (const Edge& edge : graph.at(city)) {
//        if (!visited[edge.destination]) {
//            DFSHelper(graph, edge.destination, visited);
//        }
//    }
//}

void GuideMe::DFS(unordered_map<string, vector<Edge>>& graph) {
    stack<string> stack;
    unordered_set<string> visited;
    string startCity;

    cout << "Enter the starting city: ";
    cin >> startCity;
    stack.push(startCity);
    visited.insert(startCity);

    while (!stack.empty()) {
        string currentSource = stack.top();
        stack.pop();
        cout << currentSource << " ";
        cout << endl;

        for (const auto& edge : graph[currentSource]) {
            string destination = edge.destination;
            if (visited.find(destination) == visited.end()) {
                visited.insert(destination);
                stack.push(destination);
            }
        }
    }
}

//Enumerate paths with backtracking
void GuideMe::dfsAllPaths(string current, const string& destination, double currentBudget,
    unordered_map<string, vector<Edge>> graph,
    unordered_set<string>& visited,
    vector<pair<string, string>>& path,
    double totalCost) {

    visited.insert(current);

    for (const auto& edge : graph[current]) {
        for (const auto& pair : edge.transportationPrices) {
            const string& currentTransportation = pair.first;
            const double cost = pair.second;

            if (currentBudget - cost >= 0 && visited.find(edge.destination) == visited.end()) { //ytzbat
                path.push_back(make_pair(current, currentTransportation));

                double newBudget = currentBudget - cost;
                double newTotalCost = totalCost + cost;

                if (edge.destination == destination) {
                    printPath(path, newTotalCost,destination);
                }
                else {
                    dfsAllPaths(edge.destination, destination, newBudget, graph, visited, path, newTotalCost);
                }

                path.pop_back(); //Backtrack
            }
        }
    }

    visited.erase(current); //Backtrack feha moshkla ig
}

void GuideMe::printPath(const vector<pair<string, string>>& path, double totalCost,const string destination) {
    for (const auto& p : path) {
        cout << p.first << " (" << p.second << ") -> ";
    }
    cout << destination<<" Total cost= " << totalCost << endl;
}

void GuideMe::findAllPaths(const unordered_map<string, vector<Edge>>& graph) {
    unordered_set<string> visited;
    vector<pair<string, string>> path;
    double totalCost = 0.0;
    string source, destination;
    double budget;

    cout << "Enter source city: ";
    cin >> source;
    cout << "Enter destination city: ";
    cin >> destination;
    cout << "Enter budget: ";
    cin >> budget;

    dfsAllPaths(source, destination, budget, graph, visited, path, totalCost);
}

