#include "GuideMe.h"
#include <unordered_set>
#include <set>
void GuideMe::addEdge(unordered_map<string, vector<Edge>>& graph, const string& source, const Edge& edge) {
    graph[source].push_back(edge);

    // Create a new Edge object with the reverse direction (destination to source)
    unordered_map<string, double> reverseTransportationPrices;
    for (const auto& pair : edge.transportationPrices) {
        reverseTransportationPrices[pair.first] = pair.second;
    }
    Edge reverseEdge(source, reverseTransportationPrices);
    graph[edge.destination].push_back(reverseEdge);
}

//vector<vector<string>> GuideMe::findAvailableRoutes(string& source, string& destination, int budget) {
//
//}

//void GuideMe::updatEdge(string& source, string& destination, string transportation, int newCost) {
//
//}
void GuideMe::deleteEdge(unordered_map<string, vector<Edge>>& graph, const string& source, const string& destination, const vector<string>& transportations) {
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
            }
        }
    }
    cerr << "Error: Edge not found or specified transportation type not present!" << endl;
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


void GuideMe::bfs(string& source, unordered_map<string, vector<Edge>>& graph) {
    queue<string> q;
    unordered_set<string> visited;

    q.push(source);
    visited.insert(source);

    while (!q.empty()) {
        string currentSource = q.front();
        q.pop();
        cout << currentSource << " ";

        for (const auto& edge : graph[currentSource]) {
            string destination = edge.destination;
            if (visited.find(destination) == visited.end()) {
                visited.insert(destination);
                q.push(destination);
            }
        }
    }

}
//
//int calculateNumNodes(unordered_map<string, vector<Edge>>& graph) {
//    set<string> nodes;
//    for (const auto& pair : graph) {
//        nodes.insert(pair.first); // Inserting the source node into the set
//    }
//    return nodes.size();
//}

//vector<string> GuideMe::dfs(string& source) {
//
//}




