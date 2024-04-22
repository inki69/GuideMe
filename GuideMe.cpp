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
/*
vector<vector<string>> GuideMe::findAvailableRoutes(string& source, string& destination, int budget) {

}

void GuideMe::updatEdge(string& source, string& destination, string transportation, int newCost) {

}
void GuideMe::void deleteEdge(string& source, string& destination, string transportation) {

}

bool GuideMe::isCompleteMap() {

}

vector<string> GuideMe::bfs(string& source) {

}

vector<string> GuideMe::dfs(string& source) {

}
*/



