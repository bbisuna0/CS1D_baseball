/*
Programmed By:Bernard Bisuna and Arshia Majdi
Class CS1D
Assignment: 11 part 2 - MST

Sample Output:

Kruskal's MST:
Boston - New York (214 miles)
Dallas - Houston (239 miles)
San Francisco - Los Angeles (381 miles)
Kansas City - Dallas (496 miles)
Kansas City - Chicago (533 miles)
Denver - Kansas City (599 miles)
Atlanta - Miami (661 miles)
Atlanta - Dallas (781 miles)
Chicago - New York (787 miles)
Seattle - San Francisco (807 miles)
Los Angeles - Denver (1015 miles)
Total Mileage of MST: 6513 miles
-----------------------------
Prim's MST:
Seattle - San Francisco (807 miles)
San Francisco - Los Angeles (381 miles)
Los Angeles - Denver (1015 miles)
Denver - Kansas City (599 miles)
Kansas City - Chicago (533 miles)
New York - Boston (214 miles)
Chicago - New York (787 miles)
Dallas - Atlanta (781 miles)
Atlanta - Miami (661 miles)
Kansas City - Dallas (496 miles)
Dallas - Houston (239 miles)
Total Mileage of MST: 6513 miles

*/
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <queue>
#include <set>
#include <functional>

using namespace std;

class GraphMST {
private:
    vector<string> vertices;
    map<string, int> vertexIndex;
    vector<vector<int>> adjMatrix;

public:
    GraphMST(const vector<string>& nodes) {
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

    void computeKruskalMST() {
        int n = vertices.size();
        vector<tuple<int, int, int>> edges;

        // Collect all undirected edges
        for (int u = 0; u < n; ++u) {
            for (int v = u + 1; v < n; ++v) {
                if (adjMatrix[u][v] != -1) {
                    edges.emplace_back(adjMatrix[u][v], u, v);
                }
            }
        }

        // Sort by weight
        sort(edges.begin(), edges.end());

        // Union-Find structure
        vector<int> parent(n), rank(n, 0);
        for (int i = 0; i < n; ++i) parent[i] = i;

        function<int(int)> find = [&](int u) {
            if (u != parent[u])
                parent[u] = find(parent[u]);
            return parent[u];
        };

        auto unite = [&](int u, int v) {
            u = find(u);
            v = find(v);
            if (u == v) return false;
            if (rank[u] < rank[v]) parent[u] = v;
            else if (rank[u] > rank[v]) parent[v] = u;
            else {
                parent[v] = u;
                rank[u]++;
            }
            return true;
        };

        int totalCost = 0;
        cout << "Kruskal's MST:\n";
        for (auto& [cost, u, v] : edges) {
            if (unite(u, v)) {
                cout << vertices[u] << " - " << vertices[v] << " (" << cost << " miles)\n";
                totalCost += cost;
            }
        }

        cout << "Total Mileage of MST: " << totalCost << " miles\n";
    }

    void computePrimMST() {
        int n = vertices.size();
        vector<int> key(n, INT_MAX);
        vector<int> parent(n, -1);
        vector<bool> inMST(n, false);
        key[0] = 0;

        using pii = pair<int, int>;
        priority_queue<pii, vector<pii>, greater<>> pq;
        pq.push({0, 0}); // (key, vertex)

        while (!pq.empty()) {
            int u = pq.top().second; pq.pop();
            if (inMST[u]) continue;
            inMST[u] = true;

            for (int v = 0; v < n; ++v) {
                if (adjMatrix[u][v] != -1 && !inMST[v] && adjMatrix[u][v] < key[v]) {
                    key[v] = adjMatrix[u][v];
                    pq.push({key[v], v});
                    parent[v] = u;
                }
            }
        }

        int totalCost = 0;
        cout << "Prim's MST:\n";
        for (int v = 1; v < n; ++v) {
            if (parent[v] != -1) {
                cout << vertices[parent[v]] << " - " << vertices[v]
                     << " (" << adjMatrix[parent[v]][v] << " miles)\n";
                totalCost += adjMatrix[parent[v]][v];
            }
        }

        cout << "Total Mileage of MST: " << totalCost << " miles\n";
    }
};

int main() {
    vector<string> cities = {
        "Seattle", "San Francisco", "Los Angeles", "Denver", "Kansas City", "Chicago",
        "Boston", "New York", "Atlanta", "Miami", "Dallas", "Houston"
    };

    GraphMST graph(cities);

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
        graph.addEdge(from, to, dist);
    }

    graph.computeKruskalMST();
    cout << "-----------------------------\n";
    graph.computePrimMST();

    return 0;
}
