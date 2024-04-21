#include "GuideMe.h"

void GuideMe::addEdge(unordered_map<string, vector<Edge>>& adjList, const string& source, const Edge& edge) {
    adjList[source].push_back(edge);
    adjList[edge.destination].push_back(Edge(source, edge.uber, edge.bus, edge.microbus, edge.metro, edge.train));
}

/*
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

vector<vector<string>> GuideMe::findAvailableOptions(string & source, string & destination, int budget) {

}
*/


