/* Programmed by: Breanna Bisuna, Bernard Bisuna
Course: CS1D
Assignment 9, part A - DFS using Adjacency List
Sample Output:

DFS Traversal:
Discovery Edge: Dallas -> Houston
Discovery Edge: Houston -> Atlanta
Discovery Edge: Atlanta -> Miami
Back Edge: Miami -> Houston
Back Edge: Atlanta -> Dallas
Discovery Edge: Atlanta -> Kansas City
Back Edge: Kansas City -> Dallas
Discovery Edge: Kansas City -> Chicago
Discovery Edge: Chicago -> New York
Discovery Edge: New York -> Boston
Back Edge: Boston -> Chicago
Back Edge: New York -> Atlanta
Back Edge: New York -> Kansas City
Discovery Edge: Chicago -> Denver
Back Edge: Denver -> Kansas City
Discovery Edge: Denver -> Los Angeles
Discovery Edge: Los Angeles -> San Francisco
Discovery Edge: San Francisco -> Seattle
Back Edge: Seattle -> Denver
Back Edge: Seattle -> Chicago
Back Edge: San Francisco -> Denver
Back Edge: Los Angeles -> Dallas
Back Edge: Los Angeles -> Kansas City
Total Discovery Distance: 7314
-----------------------------------------
Only print discovery edges
-----------------------------------------
DFS Traversal:
Discovery Edge: Dallas -> Houston
Discovery Edge: Houston -> Atlanta
Discovery Edge: Atlanta -> Miami
Discovery Edge: Atlanta -> Kansas City
Discovery Edge: Kansas City -> Chicago
Discovery Edge: Chicago -> New York
Discovery Edge: New York -> Boston
Discovery Edge: Chicago -> Denver
Discovery Edge: Denver -> Los Angeles
Discovery Edge: Los Angeles -> San Francisco
Discovery Edge: San Francisco -> Seattle
Total Discovery Distance: 7314

*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

// Linked list node for adjacency list
struct AdjNode {
    string vertex;
    int weight;
    AdjNode* next;
    AdjNode(const string& v, int w) : vertex(v), weight(w), next(nullptr) {}
};

// Vertex structure in arr[]
struct Vertex {
    string name;
    AdjNode* adjHead;
    Vertex(const string& n) : name(n), adjHead(nullptr) {}
};

class Graph {
private:
    vector<Vertex*> vertices;
    unordered_map<string, int> vertexIndex;
    set<pair<string, string>> printed;
    unordered_map<string, string> parent;
    int totalDiscoveryDistance = 0;

public:
    Graph(const vector<string>& names) {
        for (const auto& name : names) {
            vertices.push_back(new Vertex(name));
            vertexIndex[name] = vertices.size() - 1;
        }
    }

    void addEdge(const string& from, const string& to, int weight) {
        insertSorted(vertices[vertexIndex[from]]->adjHead, to, weight);
        insertSorted(vertices[vertexIndex[to]]->adjHead, from, weight);  // undirected
    }

    void insertSorted(AdjNode*& head, const string& to, int weight) {
        AdjNode* newNode = new AdjNode(to, weight);
        if (!head || weight < head->weight || (weight == head->weight && to < head->vertex)) {
            newNode->next = head;
            head = newNode;
            return;
        }

        AdjNode* current = head;
        while (current->next && (current->next->weight < weight || 
              (current->next->weight == weight && current->next->vertex < to))) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    void dfs(const string& start, bool discovery_only = false) {
        set<string> visited;
        printed.clear();
        parent.clear();
        totalDiscoveryDistance = 0;

        cout << "DFS Traversal:\n";
        dfsUtil(start, visited, discovery_only);
        cout << "Total Discovery Distance: " << totalDiscoveryDistance << "\n";
    }

private:
    void dfsUtil(const string& node, set<string>& visited, bool discovery_only) {
        visited.insert(node);

        AdjNode* neighbor = vertices[vertexIndex[node]]->adjHead;
        while (neighbor) {
            const string& dest = neighbor->vertex;
            int weight = neighbor->weight;

            if (!visited.count(dest)) {
                parent[dest] = node;
                if (!printed.count({node, dest}) && !printed.count({dest, node})) {
                    cout << "Discovery Edge: " << node << " -> " << dest << "\n";
                    totalDiscoveryDistance += weight;
                    printed.insert({node, dest});
                }
                dfsUtil(dest, visited, discovery_only);
            } else if (parent[node] != dest) {
                if (!printed.count({node, dest}) && !printed.count({dest, node})) {
                    if (!discovery_only)
                        cout << "Back Edge: " << node << " -> " << dest << "\n";
                    printed.insert({node, dest});
                }
            }

            neighbor = neighbor->next;
        }
    }

    // Clean up dynamic memory
public:
    ~Graph() {
        for (auto v : vertices) {
            AdjNode* curr = v->adjHead;
            while (curr) {
                AdjNode* temp = curr;
                curr = curr->next;
                delete temp;
            }
            delete v;
        }
    }
};

// Example usage
int main() {
    // Shared city names
    vector<string> cities = {
        "Seattle", "San Francisco", "Los Angeles", "Denver", "Kansas City", "Chicago",
        "Boston", "New York", "Atlanta", "Miami", "Dallas", "Houston"
    };
    Graph g(cities);

    // Part A: DFS using Adjacency List
    g.addEdge("Seattle", "San Francisco", 807);
    g.addEdge("Seattle", "Denver", 1331);
    g.addEdge("Seattle", "Chicago", 2097);
    g.addEdge("San Francisco", "Los Angeles", 381);
    g.addEdge("San Francisco", "Denver", 1267);
    g.addEdge("Los Angeles", "Denver", 1015);
    g.addEdge("Los Angeles", "Kansas City", 1663);
    g.addEdge("Los Angeles", "Dallas", 1435);
    g.addEdge("Denver", "Chicago", 1003);
    g.addEdge("Denver", "Kansas City", 599);
    g.addEdge("Chicago", "Boston", 983);
    g.addEdge("Chicago", "New York", 787);
    g.addEdge("Chicago", "Kansas City", 533);
    g.addEdge("Boston", "New York", 214);
    g.addEdge("New York", "Atlanta", 888);
    g.addEdge("New York", "Kansas City", 1260);
    g.addEdge("Atlanta", "Kansas City", 864);
    g.addEdge("Atlanta", "Dallas", 781);
    g.addEdge("Atlanta", "Houston", 810);
    g.addEdge("Atlanta", "Miami", 661);
    g.addEdge("Kansas City", "Dallas", 496);
    g.addEdge("Dallas", "Houston", 239);
    g.addEdge("Houston", "Miami", 1187);

    g.dfs("Dallas");

    cout << "-----------------------------------------\n";
    cout << "Only print discovery edges\n";
    cout << "-----------------------------------------\n";
    
    g.dfs("Dallas", true);

    return 0;
}
