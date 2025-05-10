/*Assignment 10 - Part B - BFS Directed Graph
Programmed by: Bernard Bisuna
Class: CS1D

Sample Output:

BFS Traversal (from Chicago):
Level 0: Chicago
Discovery Edge: Chicago -> Boston
Discovery Edge: Chicago -> Seattle
Level 1: Boston, Seattle  
Discovery Edge: Boston -> New York
Discovery Edge: Seattle -> San Francisco
Discovery Edge: Seattle -> Denver
Level 2: New York, San Francisco, Denver  
Cross Edge: New York -> Chicago
Discovery Edge: New York -> Atlanta
Discovery Edge: San Francisco -> Los Angeles
Cross Edge: Denver -> Chicago
Cross Edge: Denver -> San Francisco
Level 3: Atlanta, Los Angeles
Discovery Edge: Atlanta -> Miami
Cross Edge: Los Angeles -> Denver
Level 4: Miami
Discovery Edge: Miami -> Houston
Level 5: Houston
Discovery Edge: Houston -> Dallas
Cross Edge: Houston -> Atlanta
Level 6: Dallas
Discovery Edge: Dallas -> Kansas City
Cross Edge: Dallas -> Atlanta
Cross Edge: Dallas -> Los Angeles
Level 7: Kansas City
Cross Edge: Kansas City -> Chicago
Cross Edge: Kansas City -> Denver
Cross Edge: Kansas City -> Atlanta
Cross Edge: Kansas City -> New York
Cross Edge: Kansas City -> Los Angeles
Total Discovery Distance: 9284 miles
-----------------------------------------
Only print discovery edges
-----------------------------------------
BFS Traversal (from Chicago):
Level 0: Chicago
Discovery Edge: Chicago -> Boston
Discovery Edge: Chicago -> Seattle
Level 1: Boston, Seattle
Discovery Edge: Boston -> New York
Discovery Edge: Seattle -> San Francisco
Discovery Edge: Seattle -> Denver
Level 2: New York, San Francisco, Denver
Discovery Edge: New York -> Atlanta
Discovery Edge: San Francisco -> Los Angeles
Level 3: Atlanta, Los Angeles
Discovery Edge: Atlanta -> Miami
Level 4: Miami  
Discovery Edge: Miami -> Houston
Level 5: Houston
Discovery Edge: Houston -> Dallas
Level 6: Dallas
Discovery Edge: Dallas -> Kansas City
Level 7: Kansas City
Total Discovery Distance: 9284 miles

*/
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <tuple>

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
        adjMatrix[u][v] = cost; // directed only
    }

    void bfs(const string& start, bool discovery_only = false) {
        set<string> visited;
        queue<string> q;
        printed.clear();
        totalDiscoveryDistance = 0;

        visited.insert(start);
        q.push(start);
        cout << "BFS Traversal (from Chicago):\n";
        cout << "Level 0: " << start << "\n";

        int level = 1;

        while (!q.empty()) {
            int levelSize = q.size();
            vector<string> nextLevel;

            for (int i = 0; i < levelSize; ++i) {
                string curr = q.front();
                q.pop();

                int u = vertexIndex[curr];

                vector<pair<string, int>> neighbors;
                for (int v = 0; v < vertices.size(); ++v) {
                    if (adjMatrix[u][v] != -1) {
                        neighbors.emplace_back(vertices[v], adjMatrix[u][v]);
                    }
                }

                sort(neighbors.begin(), neighbors.end(), [](auto& a, auto& b) {
                    return a.second < b.second;
                });

                for (auto& [neighbor, cost] : neighbors) {
                    if (!visited.count(neighbor)) {
                        visited.insert(neighbor);
                        q.push(neighbor);
                        nextLevel.push_back(neighbor);
                        if (!printed.count({curr, neighbor})) {
                            cout << "Discovery Edge: " << curr << " -> " << neighbor << "\n";
                            totalDiscoveryDistance += cost;
                            printed.insert({curr, neighbor});
                        }
                    } else {
                        if (!printed.count({curr, neighbor})) {
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
            }
        }

        cout << "Total Discovery Distance: " << totalDiscoveryDistance << " miles\n";
    }
};

int main() {
    vector<string> cities = {
        "Miami", "Houston", "Atlanta", "Dallas", "Kansas City", "Los Angeles",
        "San Francisco", "Seattle", "Chicago", "Boston", "New York", "Denver"
    };

    GraphBFS bfsGraph(cities);

    vector<tuple<string, string, int>> edges = {
        {"Miami", "Houston", 1187},
        {"Atlanta", "Miami", 661},
        {"Houston", "Atlanta", 810},
        {"Houston", "Dallas", 239},
        {"Dallas", "Atlanta", 781},
        {"Dallas", "Kansas City", 496},
        {"Dallas", "Los Angeles", 1435},
        {"Los Angeles", "Denver", 1015},
        {"San Francisco", "Los Angeles", 381},
        {"Seattle", "San Francisco", 807},
        {"Seattle", "Denver", 1331},
        {"Chicago", "Seattle", 2097},
        {"Chicago", "Boston", 983},
        {"Boston", "New York", 214},
        {"New York", "Chicago", 787},
        {"New York", "Atlanta", 888},
        {"Denver", "San Francisco", 1267},
        {"Denver", "Chicago", 1003},
        {"Kansas City", "Atlanta", 864},
        {"Kansas City", "New York", 1260},
        {"Kansas City", "Chicago", 533},
        {"Kansas City", "Denver", 599},
        {"Kansas City", "Los Angeles", 1663}
    };

    for (const auto& [from, to, dist] : edges) {
        bfsGraph.addEdge(from, to, dist);
    }

    bfsGraph.bfs("Chicago");
    cout << "-----------------------------------------\n";
    cout << "Only print discovery edges\n";
    cout << "-----------------------------------------\n";
    bfsGraph.bfs("Chicago", true);

    return 0;
}
