/* Programmed by: Breanna Bisuna, Bernard Bisuna
Course: CS1D
Assignment 9, part B - BFS using Adjacency Matrix
Sample Output:

BFS Traversal (from Dallas):
Level 0: Dallas
Discovery Edge: Dallas -> Houston
Discovery Edge: Dallas -> Kansas City
Discovery Edge: Dallas -> Atlanta
Discovery Edge: Dallas -> Los Angeles
Level 1: Houston, Kansas City, Atlanta, Los Angeles
Cross Edge: Houston -> Atlanta
Discovery Edge: Houston -> Miami
Discovery Edge: Kansas City -> Chicago
Discovery Edge: Kansas City -> Denver
Cross Edge: Kansas City -> Atlanta
Discovery Edge: Kansas City -> New York
Cross Edge: Kansas City -> Los Angeles
Cross Edge: Atlanta -> Miami
Cross Edge: Atlanta -> New York
Discovery Edge: Los Angeles -> San Francisco
Cross Edge: Los Angeles -> Denver
Level 2: Miami, Chicago, Denver, New York, San Francisco
Cross Edge: Chicago -> New York
Discovery Edge: Chicago -> Boston
Cross Edge: Chicago -> Denver
Discovery Edge: Chicago -> Seattle
Cross Edge: Denver -> San Francisco
Cross Edge: Denver -> Seattle
Cross Edge: New York -> Boston
Cross Edge: San Francisco -> Seattle
Level 3: Boston, Seattle
Total Discovery Distance: 9991 miles
-----------------------------------------
Only print discovery edges
-----------------------------------------
BFS Traversal (from Dallas):
Level 0: Dallas
Discovery Edge: Dallas -> Houston
Discovery Edge: Dallas -> Kansas City
Discovery Edge: Dallas -> Atlanta
Discovery Edge: Dallas -> Los Angeles
Level 1: Houston, Kansas City, Atlanta, Los Angeles
Discovery Edge: Houston -> Miami
Discovery Edge: Kansas City -> Chicago
Discovery Edge: Kansas City -> Denver
Discovery Edge: Kansas City -> New York
Discovery Edge: Los Angeles -> San Francisco
Level 2: Miami, Chicago, Denver, New York, San Francisco
Discovery Edge: Chicago -> Boston
Discovery Edge: Chicago -> Seattle
Level 3: Boston, Seattle
Total Discovery Distance: 9991 miles


*/
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

class GraphBFS {
private:
    vector<string> vertices;
    map<string, int> vertexIndex;
    vector<vector<int>> adjMatrix;
    set<pair<string, string>> printed;
    int totalDiscoveryDistance = 0;

public:
    GraphBFS(const vector<string>& nodes) {
        vertices = nodes;
        int n = nodes.size();
        adjMatrix.resize(n, vector<int>(n, -1));
        for (int i = 0; i < n; i++) {
            vertexIndex[nodes[i]] = i;
        }
    }

    void addEdge(const string& from, const string& to, int cost) {
        int u = vertexIndex[from];
        int v = vertexIndex[to];
        adjMatrix[u][v] = cost;
        adjMatrix[v][u] = cost;
    }

    void bfs(const string& start, bool discovery_only = false) {
        set<string> visited;
        queue<string> q;
        printed.clear();
        totalDiscoveryDistance = 0;

        visited.insert(start);
        q.push(start);
        cout << "BFS Traversal (from Dallas):\n";
        cout << "Level 0: " << start << "\n";

        string priorityStart = start;
        int level = 1;

        while (!q.empty()) {
            int levelSize = q.size();
            vector<string> nextLevel;

            vector<pair<string, int>> thisLevel;

            for (int i = 0; i < levelSize; ++i) {
                string curr = q.front();
                q.pop();

                int u = vertexIndex[curr];

                // collect neighbors with cost
                vector<pair<string, int>> neighbors;
                for (int v = 0; v < vertices.size(); ++v) {
                    if (adjMatrix[u][v] != -1) {
                        neighbors.push_back({vertices[v], adjMatrix[u][v]});
                    }
                }

                // sort by mileage
                sort(neighbors.begin(), neighbors.end(), [](auto& a, auto& b) {
                    return a.second < b.second;
                });

                for (auto& [neighbor, cost] : neighbors) {
                    if (!visited.count(neighbor)) {
                        visited.insert(neighbor);
                        q.push(neighbor);
                        nextLevel.push_back(neighbor);
                        if (!printed.count({curr, neighbor}) && !printed.count({neighbor, curr})) {
                            cout << "Discovery Edge: " << curr << " -> " << neighbor << "\n";
                            totalDiscoveryDistance += cost;
                            printed.insert({curr, neighbor});
                        }
                    } else {
                        if (!printed.count({curr, neighbor}) && !printed.count({neighbor, curr})) {
                            if (!discovery_only)
                                cout << "Cross Edge: " << curr << " -> " << neighbor << "\n";
                            printed.insert({curr, neighbor});
                        }
                    }
                }
            }

            if (!nextLevel.empty()) {
                cout << "Level " << level++ << ": ";
                for (const string& s : nextLevel) cout << s << ", ";
                cout << "\b\b  \n";
                priorityStart = nextLevel.front(); // update level start priority
            }
        }

        cout << "Total Discovery Distance: " << totalDiscoveryDistance << " miles\n";
    }
};

int main() {

// Shared city names
vector<string> cities = {
    "Seattle", "San Francisco", "Los Angeles", "Denver", "Kansas City", "Chicago",
    "Boston", "New York", "Atlanta", "Miami", "Dallas", "Houston"
};
        
GraphBFS bfsGraph(cities);
for (auto& [from, to, dist] : vector<tuple<string, string, int>>{
    {"Seattle", "San Francisco", 807},
    {"Seattle", "Denver", 1331},
    {"Seattle", "Chicago", 2097},
    {"San Francisco", "Los Angeles", 381},
    {"San Francisco", "Denver", 1267},
    {"Los Angeles", "Denver", 1015},
    {"Los Angeles", "Kansas City", 1663},
    {"Los Angeles", "Dallas", 1435},
    {"Denver", "Chicago", 1003},
    {"Denver", "Kansas City", 599},
    {"Chicago", "Boston", 983},
    {"Chicago", "New York", 787},
    {"Chicago", "Kansas City", 533},
    {"Boston", "New York", 214},
    {"New York", "Atlanta", 888},
    {"New York", "Kansas City", 1260},
    {"Atlanta", "Kansas City", 864},
    {"Atlanta", "Dallas", 781},
    {"Atlanta", "Houston", 810},
    {"Atlanta", "Miami", 661},
    {"Kansas City", "Dallas", 496},
    {"Dallas", "Houston", 239},
    {"Houston", "Miami", 1187}
}) {
    bfsGraph.addEdge(from, to, dist);
}

bfsGraph.bfs("Dallas");
cout << "-----------------------------------------\n";
cout << "Only print discovery edges\n";
cout << "-----------------------------------------\n";

bfsGraph.bfs("Dallas",true);

return 0;
}
