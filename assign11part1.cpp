/*
Programmed By: Bernard Bisuna and Arshia Majdi
Class CS1D
Assignment: 11 part 1 - Dijkstra

Sample Output:

-----------------------------------------
Dijkstra Paths
-----------------------------------------
Dijkstra’s Shortest Paths from Denver:
Path to Seattle: Denver -> Seattle (Distance: 1331 miles)
Path to San Francisco: Denver -> San Francisco (Distance: 1267 miles)
Path to Los Angeles: Denver -> Los Angeles (Distance: 1015 miles)
Path to Kansas City: Denver -> Kansas City (Distance: 599 miles)
Path to Chicago: Denver -> Chicago (Distance: 1003 miles)
Path to Boston: Denver -> Chicago -> Boston (Distance: 1986 miles)
Path to New York: Denver -> Chicago -> New York (Distance: 1790 miles)
Path to Atlanta: Denver -> Kansas City -> Atlanta (Distance: 1463 miles)
Path to Miami: Denver -> Kansas City -> Atlanta -> Miami (Distance: 2124 miles)
Path to Dallas: Denver -> Kansas City -> Dallas (Distance: 1095 miles)
Path to Houston: Denver -> Kansas City -> Dallas -> Houston (Distance: 1334 miles)


-----------------------------------------
Print Discovery, Cross, and Back Edges
-----------------------------------------
Traversal Path from Denver to Visit All Cities:
Discovery Edge: Denver -> Kansas City (599 miles, Total Cost to Kansas City: 599 miles)
Discovery Edge: Kansas City -> Dallas (496 miles, Total Cost to Dallas: 496 miles)
Discovery Edge: Dallas -> Houston (239 miles, Total Cost to Houston: 239 miles)
Discovery Edge: Houston -> Atlanta (810 miles, Total Cost to Atlanta: 810 miles)
Discovery Edge: Atlanta -> Miami (661 miles, Total Cost to Miami: 661 miles)
Discovery Edge: Atlanta -> New York (888 miles, Total Cost to New York: 1549 miles)
Discovery Edge: New York -> Boston (214 miles, Total Cost to Boston: 214 miles)
Discovery Edge: Boston -> Chicago (983 miles, Total Cost to Chicago: 983 miles)
Back Edge: Chicago -> Denver (1003 miles, Total Cost to Denver: 2018 miles)
Discovery Edge: Denver -> Los Angeles (1015 miles, Total Cost to Los Angeles: 2018 miles)
Discovery Edge: Los Angeles -> San Francisco (381 miles, Total Cost to San Francisco: 381 miles)
Discovery Edge: San Francisco -> Seattle (807 miles, Total Cost to Seattle: 807 miles)
Total Discovery Distance: 7093 miles

*/

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <climits>
#include <stack>

using namespace std;

class GraphDijkstra {
private:
    vector<string> vertices;
    map<string, int> vertexIndex;
    vector<vector<int>> adjMatrix;

public:
    GraphDijkstra(const vector<string>& nodes) {
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
        adjMatrix[v][u] = cost; // Remove this line if making graph directed
    }

    void dijkstra(const string& source) {
        int n = vertices.size();
        vector<int> dist(n, INT_MAX);
        vector<int> prev(n, -1);
        vector<bool> visited(n, false);

        int srcIdx = vertexIndex[source];
        dist[srcIdx] = 0;

        // Min-priority queue: (distance, vertex index)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, srcIdx});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();

            if (visited[u]) continue;
            visited[u] = true;

            for (int v = 0; v < n; ++v) {
                if (adjMatrix[u][v] != -1 && !visited[v]) {
                    int alt = dist[u] + adjMatrix[u][v];
                    if (alt < dist[v]) {
                        dist[v] = alt;
                        prev[v] = u;
                        pq.push({alt, v});
                    }
                }
            }
        }

        // Output results
        cout << "Dijkstra’s Shortest Paths from " << source << ":\n";
        for (int i = 0; i < n; ++i) {
            if (i == srcIdx) continue;
            cout << "Path to " << vertices[i] << ": ";

            if (dist[i] == INT_MAX) {
                cout << "Unreachable\n";
                continue;
            }

            stack<string> path;
            for (int at = i; at != -1; at = prev[at]) {
                path.push(vertices[at]);
            }

            while (!path.empty()) {
                cout << path.top();
                path.pop();
                if (!path.empty()) cout << " -> ";
            }

            cout << " (Distance: " << dist[i] << " miles)\n";
        }
    }

    void dijkstraPath(int srcIdx, vector<int>& dist, vector<int>& prev) {
        int n = vertices.size();
        dist.assign(n, INT_MAX);
        prev.assign(n, -1);
        vector<bool> visited(n, false);

        dist[srcIdx] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, srcIdx});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (visited[u]) continue;
            visited[u] = true;

            for (int v = 0; v < n; ++v) {
                if (adjMatrix[u][v] != -1 && !visited[v]) {
                    int alt = dist[u] + adjMatrix[u][v];
                    if (alt < dist[v]) {
                        dist[v] = alt;
                        prev[v] = u;
                        pq.push({alt, v});
                    }
                }
            }
        }
    }

    void traverseAllFrom(const string& startCity) {
        int totalDiscovery = 0;
        int start = vertexIndex[startCity];
        set<pair<int, int>> visitedEdges;
        set<int> visitedNodes;
        map<int, int> parent;
    
        int current = start;
        visitedNodes.insert(current);
        parent[current] = -1;
    
        cout << "Traversal Path from " << startCity << " to Visit All Cities:\n";
    
        while (visitedNodes.size() < vertices.size()) {
            vector<int> dist, prev;
            dijkstraPath(current, dist, prev);
    
            // Find closest unvisited city
            int minDist = INT_MAX, nextCity = -1;
            for (int i = 0; i < vertices.size(); ++i) {
                if (!visitedNodes.count(i) && dist[i] < minDist) {
                    minDist = dist[i];
                    nextCity = i;
                }
            }
    
            if (nextCity == -1) break;
    
            // Build path from current to nextCity
            vector<int> path;
            for (int at = nextCity; at != -1; at = prev[at])
                path.push_back(at);
            reverse(path.begin(), path.end());
    
            // Traverse the path and classify edges
            for (size_t i = 0; i < path.size() - 1; ++i) {
                int u = path[i], v = path[i + 1];
                pair<int, int> edge1 = {u, v}, edge2 = {v, u};
                bool alreadyVisited = visitedNodes.count(v);
                bool edgeVisited = visitedEdges.count(edge1) || visitedEdges.count(edge2);
    
                if (!edgeVisited) {
                    if (!alreadyVisited) {
                        // Discovery edge
                        cout << "Discovery Edge: " << vertices[u] << " -> " << vertices[v]
                             << " (" << adjMatrix[u][v] << " miles, Total Cost to "
                             << vertices[v] << ": " << dist[nextCity] << " miles)\n";
                        totalDiscovery += adjMatrix[u][v];
                        parent[v] = u;
                    } else {
                        // Back or cross edge
                        int p = u;
                        bool isBack = false;
                        while (p != -1) {
                            if (p == v) {
                                isBack = true;
                                break;
                            }
                            p = parent[p];
                        }
                        string edgeType = isBack ? "Back Edge" : "Cross Edge";
                        cout << edgeType << ": " << vertices[u] << " -> " << vertices[v]
                             << " (" << adjMatrix[u][v] << " miles, Total Cost to "
                             << vertices[v] << ": " << dist[nextCity] << " miles)\n";
                    }
                    visitedEdges.insert(edge1);
                }
            }
    
            current = nextCity;
            visitedNodes.insert(current);
        }
    
        cout << "Total Discovery Distance: " << totalDiscovery << " miles\n";
    }
    
    
};

int main() {
    vector<string> cities = {
        "Seattle", "San Francisco", "Los Angeles", "Denver", "Kansas City", "Chicago",
        "Boston", "New York", "Atlanta", "Miami", "Dallas", "Houston"
    };

    GraphDijkstra graph(cities);

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

    cout << "-----------------------------------------\n";
    cout << "Dijkstra Paths\n";
    cout << "-----------------------------------------\n";
    graph.dijkstra("Denver");

    cout << "\n\n-----------------------------------------\n";
    cout << "Print Discovery, Cross, and Back Edges\n";
    cout << "-----------------------------------------\n";
    graph.traverseAllFrom("Denver");

    return 0;
}
