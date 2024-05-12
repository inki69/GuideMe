#include"files.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

//class to represent the transportation map
class GuideMe {
public:

    void addEdge(unordered_map<string, vector<Edge>>& graph);
    bool addEdgeHelper(unordered_map<string, vector<Edge>>& graph, const string source, const string destination, const string transportationType, const int price, bool& flag);

    void updateEdge(unordered_map<string, vector<Edge>>& graph);
    bool updateEdgehelper(unordered_map<string, vector<Edge>>& graph, const string source, const string destination, string transportation, int newCost);

    void deleteEdge(unordered_map<string, vector<Edge>>& graph);
    bool deleteEdgehelper(unordered_map<string, vector<Edge>>& graph, const string source, const string destination, const string transportation);

    bool isCompleteMap(unordered_map<string, vector<Edge>>& graph);

    bool isConnectedMap(unordered_map<string, vector<Edge>>& graph);

    void BFS(unordered_map<string, vector<Edge>>& graph);

    void DFS(unordered_map<string, vector<Edge>>& graph);

    void findAllPaths(const unordered_map<string, vector<Edge>>& graph);

    void dfsAllPaths(string current, const string destination, double currentBudget,
        unordered_map<string, vector<Edge>> graph,
        unordered_set<string>& visited,
        vector<pair<string, string>>& path,
        double totalCost);

   
};
