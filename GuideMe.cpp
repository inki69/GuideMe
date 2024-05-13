#include "GuideMe.h"
#include <unordered_set>
#include <set>
#include <vector>
#include <string>
using namespace std;


void GuideMe::addEdge(unordered_map<string, vector<Edge>>& graph) {
    string source, destination, transportationType;
    int price;
    bool flag = 0;
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

        addEdgeHelper(graph, source, destination, transportationType, price, flag);
        addEdgeHelper(graph, destination, source, transportationType, price, flag);
        if (flag) cout << "Transportation price addedd to '" << transportationType << "' between " << source << " & " << destination << "\n\n";
        else cout << "Error: Source city or destination not found.. Please try again." << endl;
        cout << "Do you want to add another transportation? (y/n): ";
        cin >> userChoice;
    } while (userChoice == 'y' || userChoice == 'Y');
}
bool GuideMe::addEdgeHelper(unordered_map<string, vector<Edge>>& graph, const string source, const string destination, const string transportationType, const int price, bool& flag) {
    if (graph.find(source) == graph.end()) {
        return false;
    }
    if (graph.find(destination) == graph.end()) {
        return false;
    }
    //checking if there is an existing edge between source and destination
    if (graph.find(source) != graph.end()) {
        vector<Edge>& edges = graph[source];
        for (Edge& edge : edges) {
            if (edge.destination == destination) {
                //edge already exists, update transportation prices
                edge.transportationPrices[transportationType] = price;
                flag = 1;
                return true;
            }
        }
    }

    //if no existing edge found, create a new one and add it to the graph
    Edge newEdge(destination, { {transportationType, price} });
    graph[source].push_back(newEdge);
    flag = 1;
    return true;
}

void GuideMe::updateEdge(unordered_map<string, vector<Edge>>& graph) {
    int newCost;
    string source, destination, transportation;
    char choice;
    bool flag;

    cout << "Enter source city: ";
    cin >> source;
    auto sourceIt = graph.find(source);
    if (sourceIt != graph.end()) {

        cout << "Enter destination city: ";
        cin >> destination;

        auto sourceIt = graph.find(destination);
        if (sourceIt != graph.end()) {

            do {
                cout << "Enter the transportation type you want to update : ";
                cin >> transportation;
                cout << "Enter the updated price for " << transportation << " from " << source << " to " << destination << ": ";
                cin >> newCost;
                flag = updateEdgehelper(graph, source, destination, transportation, newCost);
                flag = updateEdgehelper(graph, destination, source, transportation, newCost);
                if (flag) cout << transportation << " price from " << source << " to " << destination << " updated successfully.\n\n";
                else cout << "Error: Transportation type '" << transportation << "' not found for the specified destination.\n\n";
                cout << "Do you want to update another transportation ? (y/n): ";
                cin >> choice;


            } while ((choice == 'y' || choice == 'Y'));
        }

        else {
            cout << "Error: Destination city '" << destination << "' not reachable from '" << source << "'. Please try again.\n";
        }

    }

    else {
        cout << "Error: Source city '" << source << "' not found. Please try again.\n";
    }
}
bool GuideMe::updateEdgehelper(unordered_map<string, vector<Edge>>& graph, const string source, const string destination, string transportation, int newCost) {
    bool flag=0;
    auto sourceIt = graph.find(source);

    //finding the edge corresponding to the destination and source
    vector<Edge>& edges = sourceIt->second;
    auto edgeIt = edges.end();  //initializing edgeIt to the end iterator as a default value

    //looping over the edges vector
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if (it->destination == destination) {
            edgeIt = it;
            break;
        }
    }

    if (edgeIt == edges.end()) {
        return flag = 0;
    }

    //updating the corresponding transportation price for the specified destination
    auto& transportationPrices = edgeIt->transportationPrices;
    if (transportationPrices.find(transportation) != transportationPrices.end()) {
        transportationPrices[transportation] = newCost;
        return flag = 1;
    }
    else {
        return flag = 0;
    }
}

void GuideMe::deleteEdge(unordered_map<string, vector<Edge>>& graph) {
    string source, destination;
    cout << "Enter source city: ";
    cin >> source;
    bool flag;

    auto it = graph.find(source);
    if (it != graph.end()) {

        cout << "Enter destination city: ";
        cin >> destination;

        auto it = graph.find(destination);
        if (it != graph.end()) {


            char choice;
            do {
                string transportation;
                cout << "Enter transportation type to delete: ";
                cin >> transportation;
                flag=deleteEdgehelper(graph, source, destination, transportation);
                flag=deleteEdgehelper(graph, destination, source, transportation);
                if (flag==1) cout << "Transportation type '" << transportation << "' deleted successfully from edge " << source << " to " << destination <<"\n";
                else cout << "Error: Edge not found or specified transportation type not present! Please try again\n";
                cout << "Do you want to delete another transportation type? (y/n): ";
                cin >> choice;
            } while (choice == 'y' || choice == 'Y');

        }
        else {
            cout << "Error: Destination city not found.. Please try again." << endl;
        }


    }
    else {
        cout << "Error: Source city not found.. Please try again." << endl;
    }
}
bool GuideMe::deleteEdgehelper(unordered_map<string, vector<Edge>>& graph, const string source, const string destination, const string transportation) {
    auto it = graph.find(source);
    vector<Edge>& edges = it->second;

    for (auto& edge : edges) {
        if (edge.destination == destination) {
            auto priceIt = edge.transportationPrices.find(transportation);
            if (priceIt != edge.transportationPrices.end()) {
                edge.transportationPrices.erase(priceIt);
                if (edge.transportationPrices.empty()) {
                    auto it2 = graph.find(source);
                    auto& edgeVector = it2->second;
                    for (auto it2 = edgeVector.begin(); it2 != edgeVector.end(); ++it2) {
                        if (it2->destination == destination) {
                            edgeVector.erase(it2);
                            break; //as there is only 1 edge between a vertex and a destination
                        }
                    }

                }
                return 1;
            }
            else {
                return 0;
            }
        }
    }
}

//bool GuideMe::isCompleteMap(unordered_map<string, vector<Edge>>& graph) {
//    for (const auto& pair : graph) {
//        const vector<Edge>& edges = pair.second;
//        //checking if every other node is connected to this node
//        for (const auto& other_pair : graph) {
//            if (pair.first != other_pair.first) {
//                bool found = false;
//                for (const auto& edge : edges) {
//                    if (edge.destination == other_pair.first) {
//                        found = true;
//                        break;
//                    }
//                }
//                if (!found) {
//                    //if any other node is not connected to this node, graph is not complete
//                    return false;
//                }
//            }
//        }
//    }
//    return true;
//}
bool GuideMe::isCompleteMap(unordered_map<string, vector<Edge>>& graph) {

    int actualEdges = 0;
    int numNodes = graph.size();
    int expectedEdges = (numNodes * (numNodes - 1)) / 2;
    for (const auto& pair : graph) {
        actualEdges += pair.second.size(); // Counting the number of edges for each node
    }
    actualEdges /= 2;
    return actualEdges == expectedEdges;

}
bool GuideMe::isConnectedMap(unordered_map<string, vector<Edge>>& graph) {

    if (graph.empty()) return false; //if the graph has no nodes, it's not connected

    unordered_set<string> visited; //storing visited nodes
    queue<string> queue; //queue for BFS traversal

    //starting BFS from the first node in the adjacency list
    queue.push(graph.begin()->first);
    visited.insert(graph.begin()->first);

    //BFS
    while (!queue.empty()) {
        string current = queue.front();
        queue.pop();

        //visiting all neighbors of the current node
        for (const Edge& edge : graph[current]) {
            if (visited.find(edge.destination) == visited.end()) {
                queue.push(edge.destination);
                visited.insert(edge.destination);
            }
        }
    }

    //checking if all nodes are visited
    return visited.size() == graph.size();
}

void GuideMe::BFS(unordered_map<string, vector<Edge>>& graph) {
    queue<string> q;
    unordered_set<string> visited;
    string startCity;

    cout << "Enter the starting city: ";
    cin >> startCity;
    auto it = graph.find(startCity);
    if (it != graph.end()) {

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

    else {
        cout << "Error: Source city '" << startCity << "' not found.\n";
    }
}

void GuideMe::DFS(unordered_map<string, vector<Edge>>& graph) {
    stack<string> stack;
    unordered_set<string> visited;
    string startCity;

    cout << "Enter the starting city: ";
    cin >> startCity;
    auto it = graph.find(startCity);
    if (it != graph.end()) {

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

    else {
        cout << "Error: Source city '" << startCity << "' not found.\n";
    }
}


 vector <pair<int , vector<pair<string, string>> >> Routes;
//Enumerate paths with backtracking:
void GuideMe::dfsAllPaths(string current, const string destination, double currentBudget,
    unordered_map<string, vector<Edge>> graph,
    unordered_set<string>& visited,
    vector<pair<string, string>>& path,
    double totalCost) {

    visited.insert(current);

    for (const auto& edge : graph[current]) {
        for (const auto& pair : edge.transportationPrices) {
            const string& currentTransportation = pair.first;
            const double cost = pair.second;

            if (currentBudget - cost >= 0 && visited.find(edge.destination) == visited.end()) {
                path.push_back(make_pair(current, currentTransportation));

                double newBudget = currentBudget - cost;
                double newTotalCost = totalCost + cost;

                if (edge.destination == destination) {
                    Routes.push_back(make_pair(newTotalCost , path));
                }
                else {
                    dfsAllPaths(edge.destination, destination, newBudget, graph, visited, path, newTotalCost);
                }

                path.pop_back(); //backtracking
            }
        }
    }

    visited.erase(current);
}



void GuideMe::findAllPaths(const unordered_map<string, vector<Edge>>& graph) {
    unordered_set<string> visited;
    vector<pair<string, string>> path;
    double totalCost = 0.0;
    string source, destination;
    double budget;

    cout << "Enter source city: ";
    cin >> source;
    auto sourceIt = graph.find(source);
    if (sourceIt != graph.end()) {
        cout << "Enter destination city: ";
        cin >> destination;
        auto destIt = graph.find(destination);
        if (destIt != graph.end()) {
            cout << "Enter budget: ";
            cin >> budget;

            dfsAllPaths(source, destination, budget, graph, visited, path, totalCost);
            if (Routes.empty()) {
                cout << "Error, insuffecient budget please try again." << endl;
            }
            else {
                sort(Routes.begin(), Routes.end());

                for (int i = 0; i < Routes.size(); i++) { //loop on the output, all paths(stored in routes)
                    for (int j = 0; j < Routes[i].second.size(); j++) { //loop on each path without the total cost of that path (stored as a .first in routes)
                        cout << Routes[i].second[j].first << " (" << Routes[i].second[j].second << ") -> ";
                    }
                    cout << destination << " Total cost= " << Routes[i].first << endl;
                }
                cout << endl;
                Routes.clear();
            }
        }
        else {
            cout << "Destination city does not exist, please try again." << endl;
        }
    }
    else {
        cout << "Source city does not exist, please try again." << endl;
    }

    
}
