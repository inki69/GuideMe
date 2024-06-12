# GuideMe

# Project description: 
The city-to-City Travel Planner is a comprehensive system designed to 
facilitate seamless travel between cities within a country. Leveraging advanced 
data structures, the system constructs a dynamic map of interconnected 
cities, where transportation options serve as the edges between them. Users 
can manipulate this map through functionalities like adding, editing, or deleting 
transportation links. Additionally, essential graph algorithms such as Depth 
First Search (DFS) and Breadth-First Search (BFS) are implemented to analyze 
and navigate the city network efficiently. 

# Input/Output Scenarios 
Scenario 1: DFS 
• Description: Traversing using DFS. 
• Input: The user enters the starting city. 
• Output: The system traverses the graph printing all the cities in the graph using stack. 

Scenario 2: BFS 
• Description: Traversing using BFS. 
• Input: The user enters the starting city. 
• Output: The system traverses the graph printing all the cities in the graph using queue. 

Scenario 3: ADDING TRANSPORTATION 
• Description: Adding new transportation to the transportation list. 
• Input: The user enters the source and destination cities and the new transportation along with the 
price. 
• Output: The new transportation is added to the transportation list in the edge between the source 
and destination. 

Scenario 4: UPDATING TRANSPORTATION 
• Description: Updating price of an existing transportation 
• Input: The user enters the source, destination, and the transportation along with the new price. 
• Output: The transportation price is updated. 

Scenario 5: DELETE TRANSPORTAION 
• Description: Delete a transportation from the transportation list. 
• Input: The user enters the source, destination, and the transportation he wants to delete. 
• Output: The system deletes the transportation from the edge between the source and the 
destination. 

Scenario 6: IS CONNECTED? 
• Description: Checking whether the graph is connected or not by using BFS. 
• Input: User selects the option to check graph connection. 
• Output: System verifies whether the transportation network forms a connected graph or not. 

Scenario 7: IS COMPLETE? 
• Description: Checking whether the graph is complete or not. 
• Input: User selects the option to check graph completeness. 
• Output: System verifies whether the transportation network forms a complete graph or not. 

Scenario 8: TOUR THE COUNTRY. 
• Description: Determine two cities as source and destination and the amount of money then show 
a list of all the available options with mentioning the route 
• Input: The user enters the source, destination, and specified budget. 
• Output: The function calculates and displays all feasible paths from the source city to the 
destination city within the specified budget. Each path includes the sequence of cities visited 
along with the transportation mode used between them, as well as the total cost of the path. The 
function iterates over all possible paths from the source to the destination, considering 
transportation options within the specified budget. It then sorts the paths based on total cost and 
displays them in ascending order of cost.


