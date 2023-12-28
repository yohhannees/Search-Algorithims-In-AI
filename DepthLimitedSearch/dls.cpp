#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>  // Include this header for std::sort
#include <climits>

using namespace std;

vector<int> uniform_cost_search(vector<vector<int>>& graph, map<pair<int, int>, int>& cost, vector<int>& goal, int start) {
    vector<int> answer(graph.size(), INT_MAX);
    vector<int> visited(graph.size(), 0);
    vector<pair<int, int>> queue;
    int count = 0;

    queue.push_back({0, start});
    answer[start] = 0;

    while (!queue.empty()) {
        pair<int, int> p = queue.back();
        int index = p.second;

        if (answer[index] == INT_MAX) {
            count++;
        }

        if (answer[index] > p.first) {
            answer[index] = p.first;
        }

        queue.pop_back();
        sort(queue.begin(), queue.end(), greater<pair<int, int>>());  // Using std::sort

        if (count == goal.size()) {
            return answer;
        }

        if (!visited[p.second]) {
            for (int i = 0; i < graph[p.second].size(); i++) {
                queue.push_back({(p.first + cost[{p.second, graph[p.second][i]}]) * -1, graph[p.second][i]});
            }
        }

        visited[p.second] = 1;
    }

    return answer;
}

int main() {
    vector<vector<int>> graph(8);
    map<pair<int, int>, int> cost;

    graph[0].push_back(1);
    graph[0].push_back(3);
    graph[3].push_back(1);
    graph[3].push_back(6);
    graph[3].push_back(4);

    cost[{0, 1}] = 2;
    cost[{0, 3}] = 5;
    cost[{3, 1}] = 5;
    cost[{3, 6}] = 6;
    cost[{3, 4}] = 2;

    vector<int> goal = {6};
    int start = 0;

    vector<int> answer = uniform_cost_search(graph, cost, goal, start);

    for (int i = 0; i < answer.size(); i++) {
        cout << "Minimum cost from " << start << " to " << i << " is = " << answer[i] << endl;
    }

    return 0;
}
