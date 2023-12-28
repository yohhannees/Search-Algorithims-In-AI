import heapq

# Define the grid with the given values
grid = [[1, 1, 1, 0, 1, 1, 1, 0, 1, 0],
        [1, 0, 1, 1, 1, 1, 0, 1, 0, 0],
        [1, 0, 0, 0, 0, 1, 0, 0, 0, 1],
        [1, 0, 1, 1, 1, 1, 0, 1, 1, 1],
        [1, 1, 1, 0, 0, 0, 1, 0, 0, 1]]

# Define the dimensions of the grid
rows = len(grid)
cols = len(grid[0])

# Define the possible movements (up, down, left, right, diagonal)
dx = [-1, 1, 0, 0, -1, -1, 1, 1]
dy = [0, 0, -1, 1, -1, 1, -1, 1]

# Define the heuristic function (Manhattan distance)
def heuristic(x, y, dest):
    return abs(x - dest[0]) + abs(y - dest[1])

# Define the A* search algorithm
def a_star_search(grid, src, dest):
    # Create a priority queue to store nodes to be explored
    priority_queue = []
    
    # Create a dictionary to store the cost of reaching each node
    cost = {}
    
    # Create a dictionary to store the path to each node
    path = {}
    
    # Initialize the cost and path dictionaries
    for i in range(rows):
        for j in range(cols):
            cost[(i, j)] = float('inf')
            path[(i, j)] = None
    
    # Push the source node to the priority queue with cost 0
    heapq.heappush(priority_queue, (0, src))
    cost[src] = 0
    
    while priority_queue:
        # Pop the node with the lowest cost from the priority queue
        current_cost, current_node = heapq.heappop(priority_queue)
        
        # Check if the current node is the destination
        if current_node == dest:
            break
        
        # Explore the neighbors of the current node
        for i in range(8):
            new_x = current_node[0] + dx[i]
            new_y = current_node[1] + dy[i]
            
            # Check if the new position is within the grid boundaries
            if 0 <= new_x < rows and 0 <= new_y < cols:
                # Calculate the cost to reach the neighbor
                neighbor_cost = current_cost + grid[new_x][new_y] + heuristic(new_x, new_y, dest)
                
                # Check if the neighbor has not been visited or the new cost is lower
                if neighbor_cost < cost[(new_x, new_y)]:
                    # Update the cost and path to the neighbor
                    cost[(new_x, new_y)] = neighbor_cost
                    path[(new_x, new_y)] = current_node
                    
                    # Push the neighbor to the priority queue with the new cost
                    heapq.heappush(priority_queue, (neighbor_cost, (new_x, new_y)))
    
    # Reconstruct the path from the destination to the source
    shortest_path = []
    current_node = dest
    while current_node:
        shortest_path.append(current_node)
        current_node = path[current_node]
    
    # Reverse the path to get the correct order
    shortest_path.reverse()
    
    return shortest_path

# Define the source and destination nodes
src = (8, 0)
dest = (0, 0)

# Perform A* search on the grid
path = a_star_search(grid, src, dest)

# Print the shortest path
print("Shortest path from", src, "to", dest, "is:", path)