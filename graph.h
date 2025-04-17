#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <queue>
#include <set>
#include <algorithm>
#include <functional>
#include <QString>
#include <QTextEdit>

const int VEC_SIZE = 100;

template<typename T>
class Graph {
private:
    struct Node {
        std::pair<T, double> myPair;
        Node* next;
        Node* prev;
        Node() : next(nullptr), prev(nullptr) {}
    };

    std::vector<std::pair<T, Node*>> adjacent_list;
    std::unordered_map<T, int> cityToIndex;
    std::vector<T> indexToCity;
    std::vector<std::vector<double>> adjMatrix;
    int cityCount = 0;

public:
    Graph() {
        adjacent_list.clear();
        adjMatrix.resize(VEC_SIZE, std::vector<double>(VEC_SIZE, -1));
    }

    void add_vertex(const T& vertex1, const T& vertex2, double distance_between) {
        Node* newNode = new Node;
        newNode->myPair = {vertex2, distance_between};

        auto it = std::find_if(adjacent_list.begin(), adjacent_list.end(),
                               [&](const std::pair<T, Node*>& entry) { return entry.first == vertex1; });

        if (it == adjacent_list.end()) {
            adjacent_list.push_back({vertex1, newNode});
        } else {
            Node* head = it->second;
            Node* current = head;
            while (current != nullptr) {
                if (current->myPair.first == vertex2)
                    return;
                current = current->next;
            }

            if (newNode->myPair.second < head->myPair.second) {
                newNode->next = head;
                head->prev = newNode;
                it->second = newNode;
            } else {
                Node* prev = head;
                Node* curr = head->next;
                while (curr != nullptr && curr->myPair.second < newNode->myPair.second) {
                    prev = curr;
                    curr = curr->next;
                }
                newNode->next = curr;
                newNode->prev = prev;
                prev->next = newNode;
                if (curr != nullptr) curr->prev = newNode;
            }
        }
    }

    Node* get_adj_list(const T& vertex) {
        for (const auto& pair : adjacent_list) {
            if (pair.first == vertex)
                return pair.second;
        }
        return nullptr;
    }

    void run_dfs(const T& start_vertex, QTextEdit* output) {
        std::unordered_map<T, bool> visited;
        std::set<std::pair<T, T>> printed;
        double totalDistance = 0;

        std::function<void(const T&)> dfs = [&](const T& current) {
            visited[current] = true;
            Node* neighbor = get_adj_list(current);
            std::vector<std::pair<T, double>> sorted_neighbors;

            while (neighbor != nullptr) {
                sorted_neighbors.push_back(neighbor->myPair);
                neighbor = neighbor->next;
            }

            std::sort(sorted_neighbors.begin(), sorted_neighbors.end(),
                      [](const std::pair<T, double>& a, const std::pair<T, double>& b) {
                          return a.second < b.second;
                      });

            for (const auto& [next, dist] : sorted_neighbors) {
                if (!visited[next]) {
                    printed.insert({current, next});
                    output->append(QString::fromStdString(current + " -> " + next + ": Discovery"));
                    totalDistance += dist;
                    dfs(next);
                } else if (printed.find({current, next}) == printed.end() &&
                           printed.find({next, current}) == printed.end()) {
                    printed.insert({current, next});
                    output->append(QString::fromStdString(current + " -> " + next + ": Back"));
                }
            }
        };

        if (!visited[start_vertex]) {
            dfs(start_vertex);
        }

        output->append("\nTotal distance on discovery edges: " + QString::number(totalDistance));
    }

    void add_undirected_edge(const T& vertex1, const T& vertex2, double distance) {
        add_vertex(vertex1, vertex2, distance);
        add_vertex(vertex2, vertex1, distance);

        if (cityToIndex.find(vertex1) == cityToIndex.end()) {
            cityToIndex[vertex1] = cityCount++;
            indexToCity.push_back(vertex1);
        }
        if (cityToIndex.find(vertex2) == cityToIndex.end()) {
            cityToIndex[vertex2] = cityCount++;
            indexToCity.push_back(vertex2);
        }
        int i = cityToIndex[vertex1];
        int j = cityToIndex[vertex2];
        adjMatrix[i][j] = distance;
        adjMatrix[j][i] = distance;
    }

    void run_bfs(const std::string vertex, QTextEdit* output) {
        std::set<std::pair<T, T>> printed;
        std::vector<bool> visited(cityCount, false);
        std::queue<int> q;
        int start = cityToIndex[vertex];
        visited[start] = true;
        q.push(start);
        double totalDistance = 0;

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            std::vector<std::pair<double, int>> neighbors;
            for (int i = 0; i < cityCount; ++i) {
                if (adjMatrix[current][i] != -1) {
                    neighbors.push_back({adjMatrix[current][i], i});
                }
            }
            std::sort(neighbors.begin(), neighbors.end());

            for (auto& [dist, neighbor] : neighbors) {
                T from = indexToCity[current];
                T to = indexToCity[neighbor];

                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                    printed.insert({from, to});
                    totalDistance += dist;
                    output->append(QString::fromStdString(from + " -> " + to + ": Discovery"));
                } else if (printed.find({from, to}) == printed.end() &&
                           printed.find({to, from}) == printed.end()) {
                    printed.insert({from, to});
                    output->append(QString::fromStdString(from + " -> " + to + ": Cross"));
                }
            }
        }

        output->append("\nTotal distance on discovery edges: " + QString::number(totalDistance));
    }
};

#endif
