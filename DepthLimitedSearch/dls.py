def depth_limited_search(node, goal, depth_limit):
    if node == goal:
        return True
    elif depth_limit == 0:
        return False
    else:
        for child in graph[node]:
            if depth_limited_search(child, goal, depth_limit - 1):
                return True
        return False

# Define the graph
graph = [[] for _ in range(7)]

# Add edges to the graph
graph[0].append(3)
graph[3].append(1)
graph[3].append(6)
graph[3].append(4)
graph[1].append(6)
graph[4].append(2)
graph[4].append(5)
graph[2].append(1)
graph[5].append(2)
graph[5].append(6)
graph[6].append(4)

# Define the goal state(s)
goal = 6

# Define the depth limit
depth_limit = 3

# Perform depth-limited search from node 0 to the goal state
result = depth_limited_search(0, goal, depth_limit)

# Print the result
if result:
    print("Goal state", goal, "is reachable within the depth limit.")
else:
    print("Goal state", goal, "is not reachable within the depth limit.")