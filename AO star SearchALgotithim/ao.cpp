#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Cost to find the AND and OR path
map<string, int> Cost(map<string, int>& H, map<string, vector<string>>& condition, int weight = 1) {
    map<string, int> cost;
    
    if (condition.count("AND")) {
        vector<string> AND_nodes = condition["AND"];
        string Path_A = "";
        for (int i = 0; i < AND_nodes.size(); i++) {
            Path_A += AND_nodes[i];
            if (i != AND_nodes.size() - 1) {
                Path_A += " AND ";
            }
        }
        int PathA = 0;
        for (const string& node : AND_nodes) {
            PathA += H[node] + weight;
        }
        cost[Path_A] = PathA;
    }
    
    if (condition.count("OR")) {
        vector<string> OR_nodes = condition["OR"];
        string Path_B = "";
        for (int i = 0; i < OR_nodes.size(); i++) {
            Path_B += OR_nodes[i];
            if (i != OR_nodes.size() - 1) {
                Path_B += " OR ";
            }
        }
        int PathB = INT_MAX;
        for (const string& node : OR_nodes) {
            PathB = min(PathB, H[node] + weight);
        }
        cost[Path_B] = PathB;
    }
    
    return cost;
}

// Update the cost
map<string, map<string, int>> update_cost(map<string, int>& H, map<string, map<string, vector<string>>>& Conditions, int weight = 1) {
    vector<string> Main_nodes;
    for (const auto& entry : Conditions) {
        Main_nodes.push_back(entry.first);
    }
    reverse(Main_nodes.begin(), Main_nodes.end());
    
    map<string, map<string, int>> least_cost;
    
    for (const string& key : Main_nodes) {
        map<string, vector<string>>& condition = Conditions[key];
        cout << key << ": " << endl;
        cout << Conditions[key] << " >>> " << Cost(H, condition, weight) << endl;
        map<string, int> c = Cost(H, condition, weight);
        H[key] = min_element(c.begin(), c.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        })->second;
        least_cost[key] = Cost(H, condition, weight);
    }
    
    return least_cost;
}

// Print the shortest path
string shortest_path(string Start, map<string, map<string, int>>& Updated_cost, map<string, int>& H) {
    string Path = Start;
    
    if (Updated_cost.count(Start)) {
        int Min_cost = min_element(Updated_cost[Start].begin(), Updated_cost[Start].end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        })->second;
        
        string key = "";
        for (const auto& entry : Updated_cost[Start]) {
            if (entry.second == Min_cost) {
                key = entry.first;
                break;
            }
        }
        
        vector<string> Next;
        size_t pos = 0;
        string delimiter = " ";
        while ((pos = key.find(delimiter)) != string::npos) {
            Next.push_back(key.substr(0, pos));
            key.erase(0, pos + delimiter.length());
        }
        Next.push_back(key);
        
        if (Next.size() == 1) {
            Start = Next[0];
            Path += " <-- " + shortest_path(Start, Updated_cost, H);
        } else {
            Path += " <-- (" + key + ") ";
            
            Start = Next[0];
            Path += "[" + shortest_path(Start, Updated_cost, H) + " + ";
            
            Start = Next[Next.size() - 1];
            Path += shortest_path(Start, Updated_cost, H) + "]";
        }
    }
    
    return Path;
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
    cout << string(75, '*') << endl;
    cout << "Shortest Path:" << endl;
    cout << shortest_path("A", Updated_cost, H) << endl;

    return 0;
}