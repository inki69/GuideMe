#ifndef TRANSPORTATION_MAP_H
#define TRANSPORTATION_MAP_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>

// Structure to represent a city
struct City {
    std::string name;
    std::unordered_map<std::string, int> connections; // Connected cities and their transportation costs
};

// Class to represent the transportation map
class TransportationMap {
public:
    // Constructor
    TransportationMap();

    // Destructor
    ~TransportationMap();

    // Function to add a new city to the map
    void addCity(const std::string& cityName);

    // Function to add a transportation link between two cities
    void addTransportation(const std::string& source, const std::string& destination, int cost);

    // Function to update transportation cost between two cities
    void updateTransportation(const std::string& source, const std::string& destination, int newCost);

    // Function to delete a transportation link between two cities
    void deleteTransportation(const std::string& source, const std::string& destination);

    // Function to check if the transportation map is complete
    bool isCompleteMap() const;

    // Function to perform Breadth First Search (BFS)
    std::vector<std::string> bfs(const std::string& source) const;

    // Function to perform Depth First Search (DFS)
    std::vector<std::string> dfs(const std::string& source) const;

    // Function to find all available transportation options within given budget
    std::vector<std::vector<std::string>> findAvailableOptions(const std::string& source, const std::string& destination, int budget) const;

private:
    std::unordered_map<std::string, City*> cities; // Map of cities
    bool isConnected(const std::string& source, const std::string& destination) const; // Function to check if two cities are connected
};

#endif // TRANSPORTATION_MAP_H

