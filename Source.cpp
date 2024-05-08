#include"files.h"
#include"GuideMe.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <sstream>
#include<unordered_map>
#include <iomanip>
using namespace std;

int main() {
    files fileReader;
    unordered_map<string, vector<Edge>> graph = fileReader.createGraphFromFile("TransportationMap.txt");
    GuideMe method;
    cout << setw(70) << "************ Welcome To GuideMe ************" << endl;
    int choice;

    do {

        cout << "==Main Menu==\n\n";
        cout << "1. Traverse Using DFS\n";
        cout << "2. Traverse Using BFS\n";
        cout << "3. Add Transportation\n";
        cout << "4. Update Transportation\n";
        cout << "5. Delete Transportation\n";
        cout << "6. Check If The Graph Is Connected\n";
        cout << "7. Check If The Graph Is Complete\n";
        cout << "8. Tour The Country\n";
        cout << "9. Exit\n";

        cin >> choice;



        switch (choice) {
        case 1:
            system("cls");
            method.DFS(graph);
            
            break;
        case 2:
            system("cls");
            method.BFS(graph);
            break;
        case 3:
            system("cls");
            method.addEdge(graph);
            break;
        case 4:
            system("cls");
            method.updateEdge(graph);
            break;
        case 5:
            system("cls");
            method.deleteEdge(graph);
            break;
        case 6:
            system("cls");
            if (method.isConnectedMap(graph)) {
                cout << "The graph is connected.\n";
            }
            else cout << "The graph is not connected.\n";

            break;
        case 7:
            system("cls");
            if (method.isCompleteMap(graph)) {
                cout << "The graph is completed.\n";
            }
            else cout << "The graph is not completed.\n";
            break;
        case 8:
            system("cls");
            method.findAllPaths(graph);
            break;

        case 9:
            cout << "Exiting the system.....\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 9);

    fileReader.writeGraphToFile(graph, "write.txt");
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

    for (const auto& entry : graph) {
        const string& source = entry.first;
        const vector<Edge>& edges = entry.second;
        for (const auto& edge : edges) {
            cout << "From " << source << " to " << edge.destination << ":" << endl;
            for (const auto& pair : edge.transportationPrices) {
                cout << "  " << pair.first << ": " << pair.second << endl;
            }
        }
    }

    return 0;
}
