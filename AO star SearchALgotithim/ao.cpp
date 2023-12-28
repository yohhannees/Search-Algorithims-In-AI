#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>

using namespace std;

map<string, int> Cost(const map<string, int>& H, const map<string, vector<string>>& condition, int weight = 1) {
    map<string, int> cost;
    
    if (condition.count("AND")) {
        vector<string> AND_nodes = condition.at("AND");
        string Path_A = "";
        int PathA = 0;
        for (const string& node : AND_nodes) {
            PathA += H.at(node) + weight;
            Path_A += node + " AND ";
        }
        Path_A.pop_back(); Path_A.pop_back(); Path_A.pop_back();  // Remove the last " AND "
        cost[Path_A] = PathA;
    }
    
    if (condition.count("OR")) {
        vector<string> OR_nodes = condition.at("OR");
        string Path_B = "";
        int PathB = INT_MAX;
        for (const string& node : OR_nodes) {
            PathB = min(PathB, H.at(node) + weight);
            Path_B += node + " OR ";
        }
        Path_B.pop_back(); Path_B.pop_back(); Path_B.pop_back();  // Remove the last " OR "
        cost[Path_B] = PathB;
    }
    
    return cost;
}

map<string, map<string, int>> update_cost(map<string, int>& H, const map<string, map<string, vector<string>>>& Conditions, int weight = 1) {
    map<string, map<string, int>> least_cost;
    
    for (const pair<string, map<string, vector<string>>>& entry : Conditions) {
        string key = entry.first;
        const map<string, vector<string>>& condition = entry.second;

        least_cost[key] = Cost(H, condition, weight);
        
        int minVal = INT_MAX;
        for (const pair<string, int>& costPair : least_cost[key]) {
            minVal = min(minVal, costPair.second);
        }
        H[key] = minVal;
    }
    
    return least_cost;
}

string shortest_path(const string& Start, const map<string, map<string, int>>& Updated_cost, const map<string, int>& H) {
    if (Updated_cost.count(Start) == 0) {
        return Start;
    }
    
    int minCost = INT_MAX;
    string nextKey;
    for (const pair<string, int>& entry : Updated_cost.at(Start)) {
        if (entry.second < minCost) {
            minCost = entry.second;
            nextKey = entry.first;
        }
    }
    
    vector<string> nodes;
    string delimiter = " ";
    size_t pos = 0;
    while ((pos = nextKey.find(delimiter)) != string::npos) {
        nodes.push_back(nextKey.substr(0, pos));
        nextKey.erase(0, pos + delimiter.length());
    }
    nodes.push_back(nextKey);
    
    string path = Start + " <-- (" + nextKey + ") ";
    if (nodes.size() > 1) {
        path += "[" + shortest_path(nodes[0], Updated_cost, H) + " + " + shortest_path(nodes[nodes.size() - 1], Updated_cost, H) + "]";
    } else {
        path += shortest_path(nodes[0], Updated_cost, H);
    }
    
    return path;
}

int main() {
    map<string, int> H = {
        {"A", -1},
        {"B", 5},
        {"C", 2},
        {"D", 4},
        {"E", 7},
        {"F", 9},
        {"G", 3},
        {"H", 0},
        {"I", 0},
        {"J", 0}
    };

    map<string, map<string, vector<string>>> Conditions = {
        {"A", {{"OR", {"B"}}, {"AND", {"C", "D"}}}},
        {"B", {{"OR", {"E", "F"}}}},
        {"C", {{"OR", {"G"}}, {"AND", {"H", "I"}}}},
        {"D", {{"OR", {"J"}}}}
    };

    int weight = 1;

    cout << "Updated Cost:" << endl;
    map<string, map<string, int>> Updated_cost = update_cost(H, Conditions, weight);
    for (const auto& pair : Updated_cost) {
        const string& key = pair.first;
        const map<string, int>& cost_map = pair.second;

        cout << key << ": ";
        for (const auto& cost_pair : cost_map) {
            const string& path = cost_pair.first;
            int cost = cost_pair.second;
            cout << path << " (" << cost << ") ";
        }
        cout << endl;
    }

    cout << "Shortest Path: " << shortest_path("A", Updated_cost, H) << endl;

    return 0;
}
