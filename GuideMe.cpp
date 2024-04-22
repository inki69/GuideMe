#include "GuideMe.h"
 
void GuideMe::addEdge(unordered_map<string, vector<Edge>>& adjList, const string& source, const Edge& edge) {
    adjList[source].push_back(edge);

    // Create a new Edge object with the reverse direction (destination to source)
    unordered_map<string, double> reverseTransportationPrices;
    for (const auto& pair : edge.transportationPrices) {
        reverseTransportationPrices[pair.first] = pair.second;
    }
    Edge reverseEdge(source, reverseTransportationPrices);
    adjList[edge.destination].push_back(reverseEdge);
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

bool GuideMe::isCompleteMap(unordered_map<string, vector<Edge>>& adjList) {
    for (const auto& pair : adjList) {
        const vector<Edge>& edges = pair.second;
        //Check if every other node is connected to this node
        for (const auto& other_pair : adjList) {
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

//bool GuideMe::isConnectedMap(unordered_map<string, vector<Edge>>& adjList) {
//
//}

//vector<string> GuideMe::bfs(string& source) {
//
//}
//
//vector<string> GuideMe::dfs(string& source) {
//
//}




