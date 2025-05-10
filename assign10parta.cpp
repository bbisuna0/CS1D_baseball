/*Assignment 10 - Part A - DFS Directed Graph
Programmed by: Bernard Bisuna
Class: CS1D

Sample Output:

DFS Traversal (Directed):
Discovery Edge: Dallas -> Kansas City
Discovery Edge: Kansas City -> Chicago
Discovery Edge: Chicago -> Boston
Discovery Edge: Boston -> New York
Discovery Edge: New York -> Atlanta
Discovery Edge: Atlanta -> Miami
Discovery Edge: Miami -> Houston
Discovery Edge: Chicago -> Seattle
Discovery Edge: Seattle -> San Francisco
Discovery Edge: San Francisco -> Los Angeles
Discovery Edge: Los Angeles -> Denver
Cross Edge: Seattle -> Denver
Cross Edge: Kansas City -> Denver
Cross Edge: Kansas City -> Atlanta
Cross Edge: Kansas City -> New York
Cross Edge: Kansas City -> Los Angeles
Cross Edge: Dallas -> Atlanta
Cross Edge: Dallas -> Los Angeles
Total Discovery Distance: 9262

*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

// Adjacency list node
struct AdjNode {
    string vertex;
    int weight;
    AdjNode* next;
    AdjNode(const string& v, int w) : vertex(v), weight(w), next(nullptr) {}
};

// Vertex structure
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
    unordered_map<string, int> discoverTime;
    unordered_map<string, int> finishTime;
    int totalDiscoveryDistance = 0;
    int time = 0;

public:
    Graph(const vector<string>& names) {
        for (const auto& name : names) {
            vertices.push_back(new Vertex(name));
            vertexIndex[name] = vertices.size() - 1;
        }
    }

    void addEdge(const string& from, const string& to, int weight) {
        insertSorted(vertices[vertexIndex[from]]->adjHead, to, weight);  // Directed only
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

    void dfs(const string& start) {
        set<string> visited;
        printed.clear();
        parent.clear();
        discoverTime.clear();
        finishTime.clear();
        totalDiscoveryDistance = 0;
        time = 0;

        cout << "DFS Traversal (Directed):\n";
        dfsUtil(start, visited);
        cout << "Total Discovery Distance: " << totalDiscoveryDistance << "\n";
    }

private:
    void dfsUtil(const string& node, set<string>& visited) {
        visited.insert(node);
        discoverTime[node] = ++time;

        AdjNode* neighbor = vertices[vertexIndex[node]]->adjHead;
        while (neighbor) {
            const string& dest = neighbor->vertex;
            int weight = neighbor->weight;

            if (!visited.count(dest)) {
                parent[dest] = node;
                if (!printed.count({node, dest})) {
                    cout << "Discovery Edge: " << node << " -> " << dest << "\n";
                    totalDiscoveryDistance += weight;
                    printed.insert({node, dest});
                }
                dfsUtil(dest, visited);
            } else if (finishTime.count(dest)) {
                if (!printed.count({node, dest})) {
                    cout << "Cross Edge: " << node << " -> " << dest << "\n";
                    printed.insert({node, dest});
                }
            }

            neighbor = neighbor->next;
        }

        finishTime[node] = ++time;
    }

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

int main() {
    vector<string> cities = {
        "Miami", "Houston", "Atlanta", "Dallas", "Kansas City", "Los Angeles", "Denver",
        "San Francisco", "Seattle", "Chicago", "Boston", "New York"
    };

    Graph g(cities);

    // Directed edge list as per user's input
    g.addEdge("Miami", "Houston", 1187);
    g.addEdge("Atlanta", "Miami", 661);
    g.addEdge("Houston", "Atlanta", 810);
    g.addEdge("Houston", "Dallas", 239);
    g.addEdge("Dallas", "Atlanta", 781);
    g.addEdge("Dallas", "Kansas City", 496);
    g.addEdge("Dallas", "Los Angeles", 1435);
    g.addEdge("Los Angeles", "Denver", 1015);
    g.addEdge("San Francisco", "Los Angeles", 381);
    g.addEdge("Seattle", "San Francisco", 807);
    g.addEdge("Seattle", "Denver", 1331);
    g.addEdge("Chicago", "Seattle", 2097);
    g.addEdge("Chicago", "Boston", 983);
    g.addEdge("Boston", "New York", 214);
    g.addEdge("New York", "Chicago", 787);
    g.addEdge("New York", "Atlanta", 888);
    g.addEdge("Denver", "San Francisco", 1267);
    g.addEdge("Denver", "Chicago", 1003);
    g.addEdge("Kansas City", "Atlanta", 864);
    g.addEdge("Kansas City", "New York", 1260);
    g.addEdge("Kansas City", "Chicago", 533);
    g.addEdge("Kansas City", "Denver", 599);
    g.addEdge("Kansas City", "Los Angeles", 1663);

    g.dfs("Dallas");

    return 0;
}


/*
Edges:
Miami -> Houston 1187
Atlanta -> Miami 661
Houston -> Atlanta 810
Houston -> Dallas 239
Dallas -> Atlanta 781
Dallas -> Kansas City 496
Dallas -> Los Angeles 1435
Los Angeles -> Denver 1015
San Francisco -> Los Angeles 381
Seattle -> San Francisco 807
Seattle -> Denver 1331
Chicago -> Seattle 2097
Chicago -> Boston 983
Boston -> New York 214
New York -> Chicago 787
New York -> Atlanta 888
Denver -> San Francisco 1267
Denver -> Chicago 1003
Kansas City -> Atlanta 864
Kansas City -> New York 1260
Kansas City -> Chicago 533
Kansas City -> Denver 599
Kansas City -> Los Angeles 1663
*/