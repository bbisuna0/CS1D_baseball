/**********************************************************
 * graph.h
 *_________________________________________________________
 * Graph class with BFS, DFS, Dijkstra, and MST support
 * Qt/CMake compatible version
 *_________________________________________________________
 * Arshia Majdi
 * Bernard
 * CS1D - Professor Lebowitz
 * Apr 30, 2025
 **********************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <QString>
#include <QVector>
#include <QQueue>
#include <QSet>
#include <QMap>
#include <QDebug>
#include <QPair>
#include <QList>
#include <algorithm>
#include <functional>
#include <queue>
#include <unordered_map>
#include <set>
#include <QTextEdit>

// Template Graph class
template<typename T>
class Graph {
    struct edge; // forward declaration

    struct vertex {
        vertex* next;
        QVector<edge*> edges;
        bool visited_dijkstra;
        bool visited_prim;
        T value;
        double distance_from_og;

        vertex() : next(nullptr), visited_dijkstra(false), visited_prim(false), value(T()), distance_from_og(0.0) {}
        vertex(const T& val) : next(nullptr), visited_dijkstra(false), visited_prim(false), value(val), distance_from_og(0.0) {}
    };

    struct edge {
        double weight;
        vertex* v1;
        vertex* v2;
        edge() : weight(0.0), v1(nullptr), v2(nullptr) {}

        vertex* opposite(vertex* v) const {
            if (v == v1) return v2;
            if (v == v2) return v1;
            return nullptr;
        }
    };

    QVector<vertex*> vertices;
    QVector<vertex*> dijkstra_cloud;
    QVector<vertex*> prim_cloud;
    vertex* start_vertexPtr = nullptr;

    vertex* find_vertex(const T& val) const {
        for (auto v : vertices) {
            if (v->value == val) return v;
        }
        return nullptr;
    }

public:
    Graph() {}
    ~Graph() {
        for (auto v : vertices) {
            for (auto e : v->edges) delete e;
            delete v;
        }
    }

    void add_vertex(const T& vertex1, const T& vertex2, double weight) {
        vertex* v1 = find_vertex(vertex1);
        if (!v1) {
            v1 = new vertex(vertex1);
            vertices.push_back(v1);
        }
        vertex* v2 = find_vertex(vertex2);
        if (!v2) {
            v2 = new vertex(vertex2);
            vertices.push_back(v2);
        }
        for (auto existing : v1->edges) {
            if (existing->v2 == v2) return;
        }
        edge* e = new edge();
        e->weight = weight;
        e->v1 = v1;
        e->v2 = v2;
        v1->edges.push_back(e);
    }

    void add_undirected_edges(const T& vertex1, const T& vertex2, double distance) {
        add_vertex(vertex1, vertex2, distance);
        add_vertex(vertex2, vertex1, distance);
    }

    void print_graph() const {
        for (auto v : vertices) {
            qDebug() << v->value;
            for (auto e : v->edges) {
                qDebug() << " -> " << e->v2->value;
            }
        }
    }

    void Dijkstra(const T& start_vertex, QTextEdit* output = nullptr) {
        vertex* start_ptr = find_vertex(start_vertex);
        if (!start_ptr) return;
        start_ptr->distance_from_og = 0;
        auto cmp = [](vertex* v1, vertex* v2) { return v1->distance_from_og > v2->distance_from_og; };
        std::priority_queue<vertex*, QVector<vertex*>, decltype(cmp)> min_heap(cmp);
        min_heap.push(start_ptr);

        while (dijkstra_cloud.size() < vertices.size()) {
            if (min_heap.empty()) break;
            vertex* min_vertex = min_heap.top(); min_heap.pop();
            if(min_vertex->visited_dijkstra) continue;
            min_vertex->visited_dijkstra = true;
            dijkstra_cloud.push_back(min_vertex);
            for (auto e : min_vertex->edges) {
                vertex* check_vertex  = e->opposite(min_vertex);
                if (!check_vertex->visited_dijkstra) {
                    double new_dist = min_vertex->distance_from_og + e->weight;
                    if(check_vertex->distance_from_og == 0 || new_dist < check_vertex->distance_from_og)
                        check_vertex->distance_from_og = new_dist;
                    min_heap.push(check_vertex);
                }
            }
        }

        for (auto current_vertex_ptr : dijkstra_cloud) {
            QString result = QString::fromStdString(start_vertex) + " -> " + QString::fromStdString(current_vertex_ptr->value) +
                             " (" + QString::number(current_vertex_ptr->distance_from_og) + ")";
            if (output)
                output->append(result);
            else
                qDebug() << result;
        }
    }

    void mst(const T& start_vertex, QTextEdit* output = nullptr) {
        vertex* start = find_vertex(start_vertex);
        if (!start) return;

        for (auto v : vertices) v->visited_prim = false;
        prim_cloud.clear();

        start->visited_prim = true;
        prim_cloud.push_back(start);

        struct EdgeCmp { bool operator()(edge* a, edge* b) const { return a->weight > b->weight; } };
        std::priority_queue<edge*, QVector<edge*>, EdgeCmp> eq;

        for (auto e : start->edges) eq.push(e);

        double total_weight = 0;

        while (!eq.empty() && prim_cloud.size() < vertices.size()) {
            edge* temp_edge = eq.top(); eq.pop();
            vertex* u = temp_edge->v1;
            vertex* v = temp_edge->opposite(u);
            if (v && !v->visited_prim) {
                v->visited_prim = true;
                prim_cloud.push_back(v);
                QString edgeText = QString::fromStdString(u->value) + " -> " + QString::fromStdString(v->value) +
                                   " (weight: " + QString::number(temp_edge->weight) + ")";
                if (output)
                    output->append(edgeText);
                else
                    qDebug() << edgeText;
                total_weight += temp_edge->weight;
                for (auto e2 : v->edges) eq.push(e2);
            }
        }
        QString totalText = "Total weight of MST: " + QString::number(total_weight);
        if (output)
            output->append(totalText);
        else
            qDebug() << totalText;
    }

    void run_dfs(const T& start_val, QTextEdit* output) {
        std::unordered_map<T,bool> visited;
        std::set<std::pair<T,T>> printed;
        double totalDistance = 0;
        vertex* start = find_vertex(start_val);
        if (!start || !output) return;

        std::function<void(vertex*)> dfs = [&](vertex* u) {
            visited[u->value] = true;
            QVector<QPair<vertex*, double>> nbrs;
            for (auto e: u->edges) nbrs.append(qMakePair(e->v2, e->weight));
            std::sort(nbrs.begin(), nbrs.end(), [](auto &a, auto &b){ return a.second < b.second; });
            for (auto &pr: nbrs) {
                vertex* v = pr.first;
                double dist = pr.second;
                auto edge_pair = std::make_pair(u->value, v->value);
                if (!visited[v->value]) {
                    printed.insert(edge_pair);
                    output->append(QString::fromStdString(u->value) + " -> " + QString::fromStdString(v->value) + ": Discovery");
                    totalDistance += dist;
                    dfs(v);
                } else if (printed.find(edge_pair)==printed.end() && printed.find({v->value,u->value})==printed.end()) {
                    printed.insert(edge_pair);
                    output->append(QString::fromStdString(u->value) + " -> " + QString::fromStdString(v->value) + ": Back");
                }
            }
        };
        dfs(start);
        output->append("Total distance on discovery edges: " + QString::number(totalDistance));
    }

    void run_bfs(const T& start_val, QTextEdit* output) {
        std::unordered_map<T,bool> visited;
        std::set<std::pair<T,T>> printed;
        double totalDistance = 0;
        vertex* start = find_vertex(start_val);
        if (!start || !output) return;

        QQueue<vertex*> q;
        visited[start->value] = true;
        q.enqueue(start);

        while (!q.isEmpty()) {
            vertex* u = q.dequeue();
            QVector<QPair<vertex*,double>> nbrs;
            for (auto e: u->edges) nbrs.append(qMakePair(e->v2, e->weight));
            std::sort(nbrs.begin(), nbrs.end(), [](auto &a, auto &b){ return a.second < b.second; });
            for (auto &pr: nbrs) {
                vertex* v = pr.first;
                double dist = pr.second;
                auto edge_pair = std::make_pair(u->value, v->value);
                if (!visited[v->value]) {
                    visited[v->value] = true;
                    q.enqueue(v);
                    printed.insert(edge_pair);
                    output->append(QString::fromStdString(u->value) + " -> " + QString::fromStdString(v->value) + ": Discovery");
                    totalDistance += dist;
                } else if (printed.find(edge_pair)==printed.end() && printed.find({v->value,u->value})==printed.end()) {
                    printed.insert(edge_pair);
                    output->append(QString::fromStdString(u->value) + " -> " + QString::fromStdString(v->value) + ": Cross");
                }
            }
        }
        output->append("Total distance on discovery edges: " + QString::number(totalDistance));
    }
};

#endif // GRAPH_H
