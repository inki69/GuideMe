#include"files.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
using namespace std;

// Class to represent the transportation map
class GuideMe {
public:

    // Function to add a transportation link between two cities
    void addEdge(unordered_map<string, vector<Edge>>& graph, const string& source, const Edge& edge);

    // Function to update transportation cost between two cities
    //void updatEdge(string& source, string& destination, string transportation, int newCost);

    // Function to delete a transportation link between two cities
    void deleteEdge(unordered_map<string, vector<Edge>>& graph, const string& source, const string& destination, const vector<string>& transportation);
    void deleteEdgehelper(unordered_map<string, vector<Edge>>& graph,const string& source, const string& destination, const string& transportation);

    // Function to check if the transportation map is complete
    bool isCompleteMap(unordered_map<string, vector<Edge>>& graph);

    //Function  to check if the transportation map is connected
    bool isConnectedMap(unordered_map<string, vector<Edge>>& graph);


    // Function to perform Breadth First Search (BFS)
    void bfs(string& source, unordered_map<string, vector<Edge>>& graph);


    // Function to perform Depth First Search (DFS)
    //vector<string> dfs(string& source);

    // Function to find all available transportation options within given budget
    //vector<vector<string>> findAvailableRoutes(string& source, string& destination, int budget);
};



