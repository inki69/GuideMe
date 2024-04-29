#include"files.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

// Class to represent the transportation map
class GuideMe {
public:

    void addEdge(unordered_map<string, vector<Edge>>& graph, const string& source, const string& destination, const string& transportationType, const int& price);
    void addEdgeHelper(unordered_map<string, vector<Edge>>& graph, const string& source, const string& destination, const string& transportationType, const int& price);

    void updateEdge(unordered_map<string, vector<Edge>>& graph) ;
    void updateEdgehelper(unordered_map<string, vector<Edge>>& graph, const string& source, const string& destination, string transportation, int newCost);

    void deleteEdge(unordered_map<string, vector<Edge>>& graph);
    void deleteEdgehelper(unordered_map<string, vector<Edge>>& graph, const string& source, const string& destination, const string& transportation);

    bool isCompleteMap(unordered_map<string, vector<Edge>>& graph);

    bool isConnectedMap(unordered_map<string, vector<Edge>>& graph);

    void BFS(unordered_map<string, vector<Edge>>& graph);

    void findAllPaths(const string& source, const string& destination, const unordered_map<string, vector<Edge>>& graph);

    void dfsAllPaths(const string& current, const string& destination, const unordered_map<string, vector<Edge>>& graph, unordered_set<string>& visited, vector<string>& path);
        
    void printPath(const vector<string>& path);

    void DFS(const unordered_map<string, vector<Edge>>& graph);

    void DFSHelper(const unordered_map<string, vector<Edge>>& graph, const string& city, unordered_map<string, bool>& visited);
};



