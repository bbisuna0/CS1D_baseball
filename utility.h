#ifndef UTILITY_H
#define UTILITY_H

#include <QDebug>
#include <QApplication>
#include <QSql>
// #include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>

#include <QSqlDatabase>
#include <QTableView>
#include <QStandardItemModel>
#include <QPainter>
#include <QHeaderView>
#include <unordered_set>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QStringList>
#include <QString>
#include <vector>
#include <string>
#include <set>
#include <QLabel>
#include <QSqlTableModel>
#include "db.h"


// Function declarations
void createUserTable(); // QSqlDatabase &db
bool checkUserTable(); // check if user table exists
void addUser(int ID, QString username, QString password, bool admin); // add user data into database
bool checkPassword(QString uname, QString pass, bool &admin); // check if user table exists
bool tableExists(QSqlDatabase& db, const QString& tableName);
// class utility
// {
// public:
//     utility();
// };


/*

This works but creates a duplicate column with logos

#include <QSqlTableModel>
#include <QModelIndex>
#include <QPixmap>
#include <QIcon>
#include <QVariant>
#include <QString>
#include <QHash>

class TeamLogoModel : public QSqlTableModel
{
    Q_OBJECT

public:
    using QSqlTableModel::QSqlTableModel;

    TeamLogoModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase())
        : QSqlTableModel(parent, db), m_teamNameColumn(-1)
    {
    }

    void setTable(const QString &tableName) override
    {
        QSqlTableModel::setTable(tableName);
        select();
        // Find the column index for the "team_name" column
        for (int i = 0; i < columnCount(); ++i) {
            if (headerData(i, Qt::Horizontal).toString() == "team_name") {
                m_teamNameColumn = i;
                break;
            }
        }
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        if (role == Qt::DecorationRole && index.column() == 0) {
            if (m_teamNameColumn != -1) {
                QString teamName = QSqlTableModel::data(this->index(index.row(), m_teamNameColumn), Qt::DisplayRole).toString();
                if (!teamName.isEmpty()) {
                    if (!m_logoCache.contains(teamName)) {
                        QString logoPath = QString(":/logos/%1.png").arg(teamName.toLower().replace(' ', '-'));
                        QPixmap pixmap(logoPath);
                        if (!pixmap.isNull()) {
                            m_logoCache.insert(teamName, QIcon(pixmap));
                        } else {
                            m_logoCache.insert(teamName, QIcon()); // Store an empty icon if not found
                        }
                    }
                    return m_logoCache.value(teamName);
                }
            }
            return QVariant(); // Return an invalid QVariant if team name not found or column 0
        }
        return QSqlTableModel::data(index, role);
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return QSqlTableModel::columnCount(parent) + 1; // Add one column for the logo
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override
    {
        if (orientation == Qt::Horizontal && role == Qt::DisplayRole && section == 0) {
            return QString("Logo");
        }
        return QSqlTableModel::headerData(section - 1, orientation, role);
    }

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override
    {
        if (column == 0) {
            return createIndex(row, column);
        }
        return QSqlTableModel::index(row, column - 1, parent);
    }

    Qt::ItemFlags flags(const QModelIndex &index) const override
    {
        if (index.column() == 0) {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }
        return QSqlTableModel::flags(index);
    }

private:
    int m_teamNameColumn;
    mutable QHash<QString, QIcon> m_logoCache;
};
*/

#include <QStyledItemDelegate>
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QSize>
#include <QString>
#include <QRect>
#include <QFontMetrics>

class TeamLogoDelegate : public QStyledItemDelegate
{
public:
    TeamLogoDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        if (index.column() == 0) {
            QString teamName = index.model()->data(index, Qt::DisplayRole).toString();
            if (!teamName.isEmpty()) {
                QString logoPath = QString(":/logos/%1.png").arg(teamName.toLower().replace(' ', '-'));
                QPixmap pixmap(logoPath);

                // Draw the background
                painter->save();
                painter->fillRect(option.rect, option.palette.base());
                painter->restore();

                QRect textRect = option.rect;
                QRect imageRect;
                int spacing = 5; // Adjust spacing as needed

                if (!pixmap.isNull()) {
                    int imageWidth = option.rect.height() - 2 * spacing; // Keep image size proportional to row height
                    imageRect = QRect(option.rect.left() + spacing,
                                      option.rect.top() + spacing,
                                      imageWidth,
                                      imageWidth);
                    textRect.setLeft(imageRect.right() + spacing);
                    painter->drawPixmap(imageRect, pixmap);
                }

                // Draw the text
                painter->save();
                painter->drawText(textRect, option.displayAlignment, teamName);
                painter->restore();
            } else {
                QStyledItemDelegate::paint(painter, option, index); // Default painting if team name is empty
            }
        } else {
            QStyledItemDelegate::paint(painter, option, index); // Default painting for other columns
        }
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        if (index.column() == 0) {
            QString teamName = index.model()->data(index, Qt::DisplayRole).toString();
            if (!teamName.isEmpty()) {
                QString logoPath = QString(":/logos/%1.png").arg(teamName.toLower().replace(' ', '-'));
                QPixmap pixmap(logoPath);
                QFontMetrics fm = option.fontMetrics;
                int textWidth = fm.horizontalAdvance(teamName);
                int imageHeight = option.rect.height();
                int spacing = 5;

                if (!pixmap.isNull()) {
                    return QSize(imageHeight + spacing + textWidth + 2 * spacing, imageHeight + 2 * spacing);
                } else {
                    return QSize(textWidth + 2 * spacing, fm.height() + 2 * spacing);
                }
            }
        }
        return QStyledItemDelegate::sizeHint(option, index);
    }
};


#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSet>

class StadiumSelectionDialog : public QDialog {
public:
    StadiumSelectionDialog(QWidget* parent = nullptr) : QDialog(parent) {
        setWindowTitle("Select Stadiums to Visit");

        QVBoxLayout* mainLayout = new QVBoxLayout(this);

        QHBoxLayout* listLayout = new QHBoxLayout();

        availableList = new QListWidget();
        selectedList = new QListWidget();

        listLayout->addWidget(availableList);
        listLayout->addWidget(selectedList);

        mainLayout->addLayout(listLayout);

        QHBoxLayout* buttonLayout = new QHBoxLayout();

        addButton = new QPushButton("Add");
        removeButton = new QPushButton("Remove");
        okButton = new QPushButton("OK");
        cancelButton = new QPushButton("Cancel");

        buttonLayout->addWidget(addButton);
        buttonLayout->addWidget(removeButton);
        buttonLayout->addStretch();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);

        mainLayout->addLayout(buttonLayout);

        connect(addButton, &QPushButton::clicked, this, &StadiumSelectionDialog::addSelected);
        connect(removeButton, &QPushButton::clicked, this, &StadiumSelectionDialog::removeSelected);
        connect(okButton, &QPushButton::clicked, this, &StadiumSelectionDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &StadiumSelectionDialog::reject);

        populateAvailableListFromModel();
    }

    QStringList getSelectedStadiums() const {
        QStringList selected;
        for (int i = 0; i < selectedList->count(); ++i) {
            selected.append(selectedList->item(i)->text());
        }
        return selected;
    }

private:
    void populateAvailableListFromModel() {
        QSqlTableModel model;
        model.setTable("stadium_distances");
        model.select();

        QSet<QString> uniqueStadiums;
        for (int i = 0; i < model.rowCount(); ++i) {
            QSqlRecord record = model.record(i);
            QString origin = record.value("origin").toString();
            QString destination = record.value("destination").toString();

            uniqueStadiums.insert(origin);
            uniqueStadiums.insert(destination);
        }

        for (const QString& stadium : uniqueStadiums) {
            availableList->addItem(stadium);
        }
        availableList->sortItems();
    }

    void addSelected() {
        QListWidgetItem* item = availableList->currentItem();
        if (item) {
            selectedList->addItem(item->clone());
            delete availableList->takeItem(availableList->currentRow());
        }
        availableList->sortItems();
    }

    void removeSelected() {
        QListWidgetItem* item = selectedList->currentItem();
        if (item) {
            availableList->addItem(item->clone());
            delete selectedList->takeItem(selectedList->currentRow());
        }
        availableList->sortItems();
    }

    QListWidget* availableList;
    QListWidget* selectedList;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* okButton;
    QPushButton* cancelButton;
};

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

class GraphMST {
private:
    vector<string> vertices;
    map<string, int> vertexIndex;
    vector<vector<int>> adjMatrix;
    vector<TripEntry> trip;
    int total_cost;

public:

    int totalCost() {
        return total_cost;
    }

    std::vector<TripEntry> getTrips() {
        return trip;
    }


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
        //cout << "Kruskal's MST:\n";
        for (auto& [cost, u, v] : edges) {
            if (unite(u, v)) {
                cout << vertices[u] << " - " << vertices[v] << " (" << cost << " miles)\n";
                TripEntry trip_detail;
                trip_detail.origin = QString::fromStdString(vertices[u]);
                trip_detail.destination = QString::fromStdString(vertices[v]);
                trip_detail.distance = cost;
                trip_detail.type = "forward";
                trip.push_back(trip_detail);
                totalCost += cost;
            }
        }
        total_cost = totalCost;
        //cout << "Total Mileage of MST: " << totalCost << " miles\n";
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
    vector<TripEntry> trip;
    int total_cost;

public:
    int totalCost() {
        return total_cost;
    }

    std::vector<TripEntry> getTrips() {
        return trip;
    }

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

        //cout << "DFS Traversal (Directed):\n";
        dfsUtil(start, visited);
        //cout << "Total Discovery Distance: " << totalDiscoveryDistance << "\n";
        total_cost = totalDiscoveryDistance;
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
                    //cout << "Discovery Edge: " << node << " -> " << dest << "\n";
                    TripEntry trip_detail;
                    trip_detail.origin = QString::fromStdString(node);
                    trip_detail.destination = QString::fromStdString(dest);
                    trip_detail.distance = weight;
                    trip_detail.type = "discovery";
                    trip.push_back(trip_detail);
                    totalDiscoveryDistance += weight;
                    printed.insert({node, dest});
                }
                dfsUtil(dest, visited);
            } else if (finishTime.count(dest)) {
                if (!printed.count({node, dest})) {
                    //cout << "Cross Edge: " << node << " -> " << dest << "\n";
                    TripEntry trip_detail;
                    trip_detail.origin = QString::fromStdString(node);
                    trip_detail.destination = QString::fromStdString(dest);
                    trip_detail.distance = weight;
                    trip_detail.type = "cross";
                    trip.push_back(trip_detail);
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
    vector<TripEntry> trip;
    int total_cost;

public:
    int totalCost() {
        return total_cost;
    }

    std::vector<TripEntry> getTrips() {
        return trip;
    }

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
        //cout << "BFS Traversal (from Chicago):\n";
        //cout << "Level 0: " << start << "\n";
        TripEntry trip_detail;
        trip_detail.origin = QString::fromStdString("Level");
        trip_detail.destination = QString::number(0);
        trip_detail.distance = 0;
        trip_detail.type = "level";
        trip.push_back(trip_detail);

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
                            //cout << "Discovery Edge: " << curr << " -> " << neighbor << "\n";
                            TripEntry trip_detail;
                            trip_detail.origin = QString::fromStdString(curr);
                            trip_detail.destination = QString::fromStdString(neighbor);
                            trip_detail.distance = cost;
                            trip_detail.type = "discovery";
                            trip.push_back(trip_detail);
                            totalDiscoveryDistance += cost;
                            printed.insert({curr, neighbor});
                        }
                    } else {
                        if (!printed.count({curr, neighbor})) {
                            if (!discovery_only)
                                //cout << "Cross Edge: " << curr << " -> " << neighbor << "\n";
                            {
                                TripEntry trip_detail;
                                trip_detail.origin = QString::fromStdString(curr);
                                trip_detail.destination = QString::fromStdString(neighbor);
                                trip_detail.distance = cost;
                                trip_detail.type = "cross";
                                trip.push_back(trip_detail);
                            }
                            printed.insert({curr, neighbor});
                        }
                    }
                }
            }

            if (!nextLevel.empty()) {
                //cout << "Level " << level++ << ": ";
                level++;
                TripEntry trip_detail;
                trip_detail.origin = QString::fromStdString("Level");
                trip_detail.destination = QString::number(level);
                trip_detail.distance = 0;
                trip_detail.type = "level";
                trip.push_back(trip_detail);
                //for (const string& s : nextLevel) cout << s << ", ";
                //cout << "\b\b  \n";
            }
        }
        total_cost = totalDiscoveryDistance;
        //cout << "Total Discovery Distance: " << totalDiscoveryDistance << " miles\n";
    }
};

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
    vector<TripEntry> trip;
    int total_cost;

public:
    int totalCost() {
        return total_cost;
    }

    std::vector<TripEntry> getTrips() {
        return trip;
    }

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
        //cout << "Dijkstra’s Shortest Paths from " << source << ":\n";
        TripEntry trip_detail;
        trip_detail.origin = QString::fromStdString("Starting:");
        trip_detail.destination = QString::fromStdString(source);
        trip_detail.distance = 0;
        trip_detail.type = "level";
        trip.push_back(trip_detail);
        for (int i = 0; i < n; ++i) {
            if (i == srcIdx) continue;
            //cout << "Path to " << vertices[i] << ": ";
            TripEntry trip_detail;
            trip_detail.type = "path";
            string travelpath;

            if (dist[i] == INT_MAX) {
                //cout << "Unreachable\n";
                trip_detail.destination = QString::fromStdString("Unreachable");
                continue;
            }

            stack<string> path;
            for (int at = i; at != -1; at = prev[at]) {
                path.push(vertices[at]);
            }

            // if (!path.empty())
            //     trip_detail.origin = QString::fromStdString(path.top());
            while (!path.empty()) {
                string dest = path.top();
                travelpath += path.top();
                path.pop();
                if (!path.empty())
                    travelpath += " -> ";
                else
                    trip_detail.origin = QString::fromStdString(dest);
            }

            //cout << " (Distance: " << dist[i] << " miles)\n";
            trip_detail.distance = dist[i];
            trip_detail.destination = QString::fromStdString(travelpath);
            trip.push_back(trip_detail);
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
        total_cost = totalDiscovery;
    }


};

#endif // UTILITY_H
