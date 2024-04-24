#include"files.h"
#include"GuideMe.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include<unordered_map>
using namespace std;

int main() {
    files fileReader;
    unordered_map<string, vector<Edge>> graph = fileReader.createGraphFromFile("TransportationMap.txt");
    GuideMe method;

    int choice;

   // do {
      /*  cout << "Welcome To GuideMe"<<endl;
        cout << "1. Traverse Using DFS" << endl;
        cout << "2. Traverse Using BFS" << endl;
        cout << "3. Add Transportation" << endl;
        cout << "4. Update Transportation" << endl;
        cout << "5. Delete Transportation" << endl;
        cout << "6. Check If The Graph Is Connected" << endl;
        cout << "7. Check If The Graph Is Complete" << endl;
        cout << "8. Tour The Country" << endl;
        cout << "9. Exit" << endl;*/

  //      cin >> choice;

  //      switch (choice) {
  //      case 1:
  //          method.DFS(graph);
  //          break;
  //      case 2:
  //          method.BFS(graph);
  //          break;
  //      case 3:
  //          string source, destination;
  //          Edge edge;
  //          cout << "Enter the source city: ";
  //          cin >> source;
  //          cout << "Enter the destination city: ";
  //          cout << "Enter Transportation type: ";
  //          cout << "Enter Transportation price: ";
  //          method.addEdge(graph,source,edge);
  //          break;
  //      case 4:
  //          break;
  //      case 5:
  //          break;
  //      case 6:
  //          break;
  //      case 7:
  //          break;
  //      case 8:
  //          break;
  //      case 9:
  //          break;
  //      }

  //  }while(true)
  //  

  ////  string source = "Asyut";
  ////  string destination = "Giza";

  ////  // Find all paths from source to destination
  ////cout << "All paths from " << source << " to " << destination << ":\n";
  ////  method.findAllPaths(source, destination, graph);


  //  
  //  // Print the original adjacency list
  //  cout << "Original Adjacency List:" << endl;
  //  for (const auto& entry : graph) {
  //      cout << "From " << entry.first << " to:" << endl;
  //      for (const auto& edge : entry.second) {
  //          cout << "    " << edge.destination << ": ";
  //          for (const auto& pair : edge.transportationPrices) {
  //              cout << pair.first << " $" << pair.second << " ";
  //          }
  //          cout << endl;
  //      }
  //      cout << endl;
  //  }
  //  // Prompt the user to provide input for updating transportation options
  //  string source, destination;
  //  cout << "Enter source city: ";
  //  cin >> source;
  //  cout << "Enter destination city: ";
  //  cin >> destination;

  //  string transportation;
  //  cout << "Enter the transportation type you want to update : ";
  //  cin >> transportation;

  //  int newCost;
  //  cout << "Enter the updated price for " << transportation << " from " << source << " to " << destination << ": ";
  //  cin >> newCost;

  //  // Update transportation options
  //  GuideMe guide;
  //  guide.updateEdge(graph, source, destination, transportation, newCost);

  //  for (const auto& entry : graph) {
  //      const string& source = entry.first;
  //      const vector<Edge>& edges = entry.second;
  //      for (const auto& edge : edges) {
  //          cout << "From " << source << " to " << edge.destination << ":" << endl;
  //          for (const auto& pair : edge.transportationPrices) {
  //              cout << "  " << pair.first << ": " << pair.second << endl;
  //          }
  //      }
  //  }
  
    return 0;
}
