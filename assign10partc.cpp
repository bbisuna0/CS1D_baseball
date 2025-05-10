/*Assignment 10 - Part C - Strongly Connected Graph
Programmed by: Bernard Bisuna
Class: CS1D

Sample Output:

Running DFS on original graph:
Original Discovery Edge: Chicago -> Boston (983)
Original Discovery Edge: Boston -> New York (214)
Original Cross Edge: New York -> Chicago (787)
Original Discovery Edge: New York -> Atlanta (888)
Original Discovery Edge: Atlanta -> Miami (661)
Original Discovery Edge: Miami -> Houston (1187)
Original Discovery Edge: Houston -> Dallas (239)
Original Discovery Edge: Dallas -> Kansas City (496)
Original Cross Edge: Kansas City -> Chicago (533)
Original Discovery Edge: Kansas City -> Denver (599)
Original Cross Edge: Denver -> Chicago (1003)
Original Discovery Edge: Denver -> San Francisco (1267)
Original Discovery Edge: San Francisco -> Los Angeles (381)
Original Cross Edge: Los Angeles -> Denver (1015)
Original Cross Edge: Kansas City -> Atlanta (864)
Original Cross Edge: Kansas City -> New York (1260)
Original Cross Edge: Dallas -> Atlanta (781)
Original Cross Edge: Houston -> Atlanta (810)
Original Discovery Edge: Chicago -> Seattle (2097)

Running DFS on reversed graph:
Reversed Discovery Edge: Chicago -> Kansas City (533)
Reversed Discovery Edge: Kansas City -> Dallas (496)
Reversed Discovery Edge: Dallas -> Houston (239)
Reversed Discovery Edge: Houston -> Miami (1187)
Reversed Discovery Edge: Miami -> Atlanta (661)
Reversed Cross Edge: Atlanta -> Dallas (781)
Reversed Cross Edge: Atlanta -> Houston (810)
Reversed Cross Edge: Atlanta -> Kansas City (864)
Reversed Discovery Edge: Atlanta -> New York (888)
Reversed Discovery Edge: New York -> Boston (214)
Reversed Cross Edge: Boston -> Chicago (983)
Reversed Cross Edge: New York -> Kansas City (1260)
Reversed Discovery Edge: Chicago -> Denver (1003)
Reversed Discovery Edge: Denver -> Los Angeles (1015)
Reversed Discovery Edge: Los Angeles -> San Francisco (381)
Reversed Discovery Edge: San Francisco -> Seattle (807)
Reversed Cross Edge: Seattle -> Chicago (2097)
Reversed Cross Edge: San Francisco -> Denver (1267)

Graph is strongly connected ✅

*/
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <tuple>
#include <algorithm>

using namespace std;

class DirectedGraph {
private:
    vector<string> vertices;
    map<string, int> vertexIndex;
    vector<vector<pair<int, int>>> adj;     // (to, weight)
    vector<vector<pair<int, int>>> revAdj;  // (to, weight)
    set<pair<string, string>> printed;

public:
    DirectedGraph(const vector<string>& nodes) {
        vertices = nodes;
        int n = nodes.size();
        adj.resize(n);
        revAdj.resize(n);
        for (int i = 0; i < n; ++i)
            vertexIndex[nodes[i]] = i;
    }

    void addEdge(const string& from, const string& to, int weight) {
        int u = vertexIndex[from];
        int v = vertexIndex[to];
        adj[u].emplace_back(v, weight);
        revAdj[v].emplace_back(u, weight); // reversed graph
    }

    void dfsWithEdges(int u, vector<bool>& visited, vector<bool>& finished,
                      const vector<vector<pair<int, int>>>& graph, const string& graphName) {
        visited[u] = true;

        // Sort neighbors by weight before visiting
        vector<pair<int, int>> sortedNeighbors = graph[u];
        sort(sortedNeighbors.begin(), sortedNeighbors.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.second < b.second;
             });

        for (auto& [v, weight] : sortedNeighbors) {
            string from = vertices[u];
            string to = vertices[v];

            if (!visited[v]) {
                cout << graphName << " Discovery Edge: " << from << " -> " << to << " (" << weight << ")\n";
                printed.insert({from, to});
                dfsWithEdges(v, visited, finished, graph, graphName);
            } else if (!finished[v]) {
                if (!printed.count({from, to})) {
                    cout << graphName << " Cross Edge: " << from << " -> " << to << " (" << weight << ")\n";
                    printed.insert({from, to});
                }
            }
        }

        finished[u] = true;
    }

    bool isStronglyConnected(string startName) {
        int start = vertexIndex[startName];

        cout << "Running DFS on original graph:\n";
        vector<bool> visited(vertices.size(), false);
        vector<bool> finished(vertices.size(), false);
        printed.clear();
        dfsWithEdges(start, visited, finished, adj, "Original");

        if (any_of(visited.begin(), visited.end(), [](bool v) { return !v; })) {
            cout << "\nNot strongly connected (original): some vertices not reached.\n";
            return false;
        }

        cout << "\nRunning DFS on reversed graph:\n";
        fill(visited.begin(), visited.end(), false);
        fill(finished.begin(), finished.end(), false);
        printed.clear();
        dfsWithEdges(start, visited, finished, revAdj, "Reversed");

        if (any_of(visited.begin(), visited.end(), [](bool v) { return !v; })) {
            cout << "\nNot strongly connected (reversed): some vertices not reached.\n";
            return false;
        }

        cout << "\nGraph is strongly connected ✅\n";
        return true;
    }
};

int main() {
    vector<string> cities = {
        "Miami", "Houston", "Atlanta", "Dallas", "Kansas City", "Los Angeles",
        "San Francisco", "Seattle", "Chicago", "Boston", "New York", "Denver"
    };

    DirectedGraph g(cities);

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
        g.addEdge(from, to, dist);
    }

    g.isStronglyConnected("Chicago");

    return 0;
}
