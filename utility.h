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
/**
 * @brief Creates the 'user' table in the database.
 */
void createUserTable(); // QSqlDatabase &db

/**
 * @brief Checks if the 'user' table exists in the database.
 * @return True if exists, false otherwise.
 */
bool checkUserTable(); // check if user table exists

/**
 * @brief Checks if the 'stadium_location' table exists in the database.
 * @return True if exists, false otherwise.
 */
bool checkStadiumLocationTable();

/**
 * @brief Adds a new user to the 'user' table.
 * @param ID User ID (not used, auto-incremented).
 * @param username Username.
 * @param password Password.
 * @param admin Whether the user is an admin.
 */
void addUser(int ID, QString username, QString password, bool admin); // add user data into database

/**
 * @brief Checks if a username/password combination is valid.
 * @param uname Username.
 * @param pass Password.
 * @param admin Output boolean whether the user is admin.
 * @return True if credentials are valid.
 */
bool checkPassword(QString uname, QString pass, bool &admin); // check if user table exists

/**
 * @brief Checks if a specific table exists in a database.
 * @param db Database reference.
 * @param tableName Name of the table.
 * @return True if the table exists.
 */
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

/**
 * @class TeamLogoDelegate
 * @brief Custom delegate to render team logos and names in the first column of a view.
 *
 * This delegate overrides the default painting behavior to display a logo (loaded from a resource path)
 * alongside the team name. It also adjusts size hints accordingly to ensure proper layout.
 */
class TeamLogoDelegate : public QStyledItemDelegate
{
public:
    /**
     * @brief Constructs a TeamLogoDelegate.
     * @param parent Optional parent object.
     */
    TeamLogoDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}


    /**
     * @brief Custom paint function to draw logo and team name.
     * @param painter Painter used for rendering.
     * @param option Style options for the item.
     * @param index Model index of the item.
     */
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


    /**
     * @brief Provides size hint for the custom cell.
     * @param option Style options for the item.
     * @param index Model index of the item.
     * @return Suggested size for the cell.
     */
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


/**
 * @class TeamOnlySelectionDialog
 * @brief Dialog to select teams based on the "teams" database table.
 *
 * This dialog allows users to select from a list of team names. The list is populated
 * from the `teams` table. Selected teams can be retrieved after the dialog is accepted.
 */
class TeamOnlySelectionDialog : public QDialog {
public:
    /**
     * @brief Constructor.
     * @param parent Optional parent widget.
     */
    TeamOnlySelectionDialog(QWidget* parent = nullptr) : QDialog(parent) {
        setWindowTitle("Select Teams to Visit");

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

        connect(addButton, &QPushButton::clicked, this, &TeamOnlySelectionDialog::addSelected);
        connect(removeButton, &QPushButton::clicked, this, &TeamOnlySelectionDialog::removeSelected);
        connect(okButton, &QPushButton::clicked, this, &TeamOnlySelectionDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &TeamOnlySelectionDialog::reject);

        populateAvailableListFromModel();
    }


    /**
     * @brief Returns the selected teams.
     * @return List of selected team names.
     */
    QStringList getSelectedStadiums() const {
        QStringList selected;
        for (int i = 0; i < selectedList->count(); ++i) {
            selected.append(selectedList->item(i)->text());
        }
        return selected;
    }

private:
    /// Populates available teams from the "teams" SQL table.
    void populateAvailableListFromModel() {
        QSqlTableModel model;
        model.setTable("teams");
        model.select();

        QSet<QString> uniqueStadiums;
        for (int i = 0; i < model.rowCount(); ++i) {
            QSqlRecord record = model.record(i);
            // QString origin = record.value("origin").toString();
            // QString destination = record.value("destination").toString();
            QString origin = record.value("team_name").toString();
            QString stadium_name = record.value("stadium_name").toString();

            uniqueStadiums.insert(origin);
            // uniqueStadiums.insert(destination);
        }

        for (const QString& stadium : uniqueStadiums) {
            availableList->addItem(stadium);
        }
        availableList->sortItems();
    }

    /// Moves the currently selected item from available to selected.
    void addSelected() {
        QListWidgetItem* item = availableList->currentItem();
        if (item) {
            selectedList->addItem(item->clone());
            delete availableList->takeItem(availableList->currentRow());
        }
        availableList->sortItems();
    }

    /// Moves the currently selected item from selected back to available.
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


/**
 * @class StadiumSelectionDialog
 * @brief Dialog to select stadiums based on the "stadium_distances" database table.
 *
 * This dialog allows users to select from a list of stadiums. The list is derived
 * from the `origin` and `destination` fields in the `stadium_distances` table.
 */
class StadiumSelectionDialog : public QDialog {
public:
    /**
     * @brief Constructor.
     * @param parent Optional parent widget.
     */
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


    /**
     * @brief Returns the selected stadiums.
     * @return List of selected stadium names.
     */
    QStringList getSelectedStadiums() const {
        QStringList selected;
        for (int i = 0; i < selectedList->count(); ++i) {
            selected.append(selectedList->item(i)->text());
        }
        return selected;
    }

private:
    /// Populates available stadiums from the "stadium_distances" SQL table.
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

    /// Moves the currently selected item from available to selected.
    void addSelected() {
        QListWidgetItem* item = availableList->currentItem();
        if (item) {
            selectedList->addItem(item->clone());
            delete availableList->takeItem(availableList->currentRow());
        }
        availableList->sortItems();
    }

    /// Moves the currently selected item from selected back to available.
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

/**
 * @class GraphMST
 * @brief Graph class to compute Minimum Spanning Tree (MST) using Kruskal's and Prim's algorithms.
 *
 * This class supports building an undirected weighted graph and computing
 * the MST using either Kruskal's or Prim's algorithm. It stores the MST edges
 * and total mileage.
 */
class GraphMST {
private:
    std::vector<std::string> vertices;             /**< List of vertex names */
    std::map<std::string, int> vertexIndex;        /**< Maps vertex names to indices */
    std::vector<std::vector<int>> adjMatrix;       /**< Adjacency matrix storing edge costs */
    std::vector<TripEntry> trip;                   /**< Stores the MST edges */
    int total_cost;

public:
    /**
     * @brief Gets the total cost of the MST.
     * @return Total mileage of the computed MST.
     */
    int totalCost() {
        return total_cost;
    }

    /**
     * @brief Gets the list of trip entries representing the MST edges.
     * @return Vector of TripEntry objects.
     */
    std::vector<TripEntry> getTrips() {
        return trip;
    }

    /**
     * @brief Constructs the graph with given vertex names.
     * @param nodes List of vertex names to initialize the graph.
     */
    GraphMST(const vector<string>& nodes) {
        vertices = nodes;
        int n = nodes.size();
        adjMatrix.resize(n, vector<int>(n, -1));
        for (int i = 0; i < n; i++) {
            vertexIndex[nodes[i]] = i;
        }
    }

    /**
     * @brief Adds an undirected edge between two vertices.
     * @param from Name of the starting vertex.
     * @param to Name of the destination vertex.
     * @param cost Weight or distance of the edge.
     */
    void addEdge(const string& from, const string& to, int cost) {
        int u = vertexIndex[from];
        int v = vertexIndex[to];
        adjMatrix[u][v] = cost;
        adjMatrix[v][u] = cost;
    }

    /**
     * @brief Computes the Minimum Spanning Tree using Kruskal's algorithm.
     *
     * Uses union-find to efficiently determine which edges to include.
     * Populates the `trip` vector with MST edges and computes the total mileage.
     */
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
                trip_detail.type = "discovery";
                trip.push_back(trip_detail);
                totalCost += cost;
            }
        }
        total_cost = totalCost;
        //cout << "Total Mileage of MST: " << totalCost << " miles\n";
    }


    /**
     * @brief Computes the Minimum Spanning Tree using Prim's algorithm.
     *
     * Starts from the first vertex and grows the MST by selecting the edge
     * with the smallest weight connecting to an unvisited vertex.
     */
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

/**
 * @struct AdjNode
 * @brief Represents an adjacency list node with a destination vertex and edge weight.
 */
// Adjacency list node
struct AdjNode {
    std::string vertex;   /**< Name of the destination vertex */
    int weight;           /**< Weight of the edge */
    AdjNode* next;        /**< Pointer to the next adjacent node */

    /**
     * @brief Constructs an AdjNode.
     * @param v Destination vertex name.
     * @param w Weight of the edge.
     */
    AdjNode(const std::string& v, int w) : vertex(v), weight(w), next(nullptr) {}
};

/**
 * @struct Vertex
 * @brief Represents a vertex in the graph with an adjacency list.
 */
// Vertex structure
struct Vertex {
    std::string name;     /**< Name of the vertex */
    AdjNode* adjHead;     /**< Head of the adjacency list */

    /**
     * @brief Constructs a Vertex with the given name.
     * @param n Name of the vertex.
     */
    Vertex(const std::string& n) : name(n), adjHead(nullptr) {}
};


/**
 * @class Graph
 * @brief Directed graph implemented with adjacency lists and supports DFS traversal.
 */
class Graph {
private:
    std::vector<Vertex*> vertices;                     /**< List of vertex pointers */
    std::unordered_map<std::string, int> vertexIndex;  /**< Maps vertex names to indices */
    std::set<std::pair<std::string, std::string>> printed; /**< Tracks printed edges */
    std::unordered_map<std::string, std::string> parent;   /**< Parent tracking for DFS */
    std::unordered_map<std::string, int> discoverTime;     /**< Discovery time per vertex */
    std::unordered_map<std::string, int> finishTime;       /**< Finish time per vertex */
    int totalDiscoveryDistance = 0;                    /**< Total distance of discovery edges */
    int time = 0;                                      /**< Global time counter for DFS */
    std::vector<TripEntry> trip;                       /**< Stores trip entries from DFS */
    int total_cost;                                    /**< Total cost of traversal */


public:
    /**
     * @brief Gets the total cost of all discovery edges.
     * @return Total discovery distance.
     */
    int totalCost() {
        return total_cost;
    }

    /**
     * @brief Retrieves the recorded trip details after traversal.
     * @return Vector of TripEntry representing the DFS result.
     */
    std::vector<TripEntry> getTrips() {
        return trip;
    }

    /**
     * @brief Constructs the graph with a list of vertex names.
     * @param names Vector of unique vertex names.
     */
    Graph(const vector<string>& names) {
        for (const auto& name : names) {
            vertices.push_back(new Vertex(name));
            vertexIndex[name] = vertices.size() - 1;
        }
    }

    /**
     * @brief Adds a directed edge to the graph.
     * @param from Name of the starting vertex.
     * @param to Name of the destination vertex.
     * @param weight Weight of the edge.
     */
    void addEdge(const string& from, const string& to, int weight) {
        insertSorted(vertices[vertexIndex[from]]->adjHead, to, weight);  // Directed only
    }

    /**
     * @brief Starts depth-first search (DFS) traversal from a given vertex.
     * @param start Name of the starting vertex.
     */
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

    /**
     * @brief Starts depth-first search (DFS) traversal from a given vertex.
     * @param start Name of the starting vertex.
     */
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
    /**
     * @brief Recursive utility function for performing DFS.
     * @param node Current vertex name.
     * @param visited Set of visited vertices.
     */
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
    /**
     * @brief Destructor to clean up dynamically allocated vertices and adjacency lists.
     */
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


/**
 * @class GraphBFS
 * @brief Represents a directed graph using an adjacency matrix and supports BFS traversal.
 *
 * This class allows for adding edges and performing a breadth-first search (BFS) traversal,
 * capturing discovery and cross edges along with the level information. It records the traversal
 * as a list of TripEntry objects.
 */
class GraphBFS {
private:
    std::vector<std::string> vertices;                         /**< List of vertex names. */
    std::map<std::string, int> vertexIndex;                    /**< Maps vertex names to indices in the adjacency matrix. */
    std::vector<std::vector<int>> adjMatrix;                   /**< Adjacency matrix representing edge weights. */
    std::set<std::pair<std::string, std::string>> printed;     /**< Tracks printed edges to avoid duplicates. */
    int totalDiscoveryDistance = 0;                            /**< Total distance of discovery edges. */
    std::vector<TripEntry> trip;                               /**< Stores trip entries from BFS traversal. */
    int total_cost;                                            /**< Total cost of the traversal. */


public:
    /**
     * @brief Returns the total discovery cost accumulated during BFS.
     * @return Total cost in miles.
     */
    int totalCost() {
        return total_cost;
    }

    /**
     * @brief Returns the recorded trip entries from the BFS traversal.
     * @return Vector of TripEntry objects.
     */
    std::vector<TripEntry> getTrips() {
        return trip;
    }

    /**
     * @brief Constructs a GraphBFS object with given vertex names.
     * @param nodes Vector of unique vertex names.
     */
    GraphBFS(const vector<string>& nodes) {
        vertices = nodes;
        int n = nodes.size();
        adjMatrix.resize(n, vector<int>(n, -1));
        for (int i = 0; i < n; i++) {
            vertexIndex[nodes[i]] = i;
        }
    }

    /**
     * @brief Adds a directed edge between two vertices with a given cost.
     * @param from Source vertex name.
     * @param to Destination vertex name.
     * @param cost Edge weight (e.g., distance in miles).
     */
    void addEdge(const string& from, const string& to, int cost) {
        int u = vertexIndex[from];
        int v = vertexIndex[to];
        adjMatrix[u][v] = cost; // directed only
    }

    /**
     * @brief Performs a breadth-first traversal starting from a specified vertex.
     * @param start Starting vertex name.
     * @param discovery_only If true, cross edges are not included in the traversal result.
     */
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

/**
 * @class GraphDijkstra
 * @brief Represents a weighted undirected graph with Dijkstra-based traversal and pathfinding capabilities.
 *
 * This class supports:
 * - Standard Dijkstra's algorithm to compute shortest paths from a single source
 * - Traversal through all vertices using Dijkstra’s algorithm to classify discovery/back/cross edges
 * - Optimized path through a subset of vertices (e.g., stadiums) using permutations + Dijkstra
 */
class GraphDijkstra {
private:
    std::vector<std::string> vertices;                    /**< List of vertex names. */
    std::map<std::string, int> vertexIndex;               /**< Maps vertex names to matrix indices. */
    std::vector<std::vector<int>> adjMatrix;              /**< Adjacency matrix to store distances. */
    std::vector<TripEntry> trip;                          /**< Stores path/trip entries for reporting. */
    int total_cost;                                       /**< Total cost accumulated from a traversal. */

public:
    /**
     * @brief Returns the total cost (e.g., miles) of the last traversal or route.
     * @return Total cost in integer miles.
     */
    int totalCost() {
        return total_cost;
    }

    /**
     * @brief Gets the recorded trip entries from the most recent traversal.
     * @return Vector of TripEntry structs.
     */
    std::vector<TripEntry> getTrips() {
        return trip;
    }

    /**
     * @brief Constructs a graph with a given set of node names.
     * @param nodes Vector of unique node labels (e.g., stadium names).
     */
    GraphDijkstra(const vector<string>& nodes) {
        vertices = nodes;
        int n = nodes.size();
        adjMatrix.resize(n, vector<int>(n, -1));
        for (int i = 0; i < n; i++) {
            vertexIndex[nodes[i]] = i;
        }
    }

    /**
     * @brief Adds an undirected edge between two nodes with a specified cost.
     * @param from Source node.
     * @param to Destination node.
     * @param cost Distance or weight of the edge.
     */
    void addEdge(const string& from, const string& to, int cost) {
        int u = vertexIndex[from];
        int v = vertexIndex[to];
        adjMatrix[u][v] = cost;
        adjMatrix[v][u] = cost; // Remove this line if making graph directed
    }

    /**
     * @brief Computes Dijkstra’s shortest paths from a single source and stores results in `trip`.
     * @param source Starting vertex name.
     */
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

    /**
     * @brief Computes Dijkstra’s path tree from a source index.
     * @param srcIdx Index of source vertex.
     * @param dist Vector to store shortest distances to all nodes.
     * @param prev Vector to store parent pointers for path reconstruction.
     */
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

    /**
     * @brief Visits all vertices starting from a city using repeated Dijkstra's to form a connected traversal.
     * @param startCity The starting vertex name.
     *
     * Classifies and prints discovery, back, and cross edges. Updates `trip` and `total_cost`.
     */
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

    /**
     * @brief Computes the optimized shortest route through a given list of stadiums.
     * @param stadiums List of stadium names to visit in optimal order.
     *
     * Uses all-pairs shortest paths + permutations to find the most efficient order of visits.
     */
    void dijkstraOptimizedRoute(const vector<string>& stadiums) {
        int k = stadiums.size();
        if (k < 2) return;

        // Step 1: Build distance and path tables
        vector<vector<int>> distMatrix(k, vector<int>(k, INT_MAX));
        vector<vector<vector<int>>> pathMatrix(k, vector<vector<int>>(k));

        for (int i = 0; i < k; ++i) {
            int srcIdx = vertexIndex[stadiums[i]];
            vector<int> dist(vertices.size(), INT_MAX);
            vector<int> prev(vertices.size(), -1);
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
            dist[srcIdx] = 0;
            pq.push({0, srcIdx});

            while (!pq.empty()) {
                auto [d, u] = pq.top(); pq.pop();
                for (int v = 0; v < vertices.size(); ++v) {
                    if (adjMatrix[u][v] != -1) {
                        int alt = dist[u] + adjMatrix[u][v];
                        if (alt < dist[v]) {
                            dist[v] = alt;
                            prev[v] = u;
                            pq.push({alt, v});
                        }
                    }
                }
            }

            for (int j = 0; j < k; ++j) {
                if (i == j) continue;
                int destIdx = vertexIndex[stadiums[j]];
                if (dist[destIdx] == INT_MAX) continue;

                distMatrix[i][j] = dist[destIdx];
                // Reconstruct path from i to j
                vector<int> path;
                for (int at = destIdx; at != -1; at = prev[at])
                    path.push_back(at);
                reverse(path.begin(), path.end());
                pathMatrix[i][j] = path;
            }
        }

        // Step 2: Try all permutations of stadium visits
        vector<int> perm(k);
        iota(perm.begin(), perm.end(), 0);
        int bestCost = INT_MAX;
        vector<int> bestPath;

        do {
            int cost = 0;
            bool valid = true;
            for (int i = 0; i < k - 1; ++i) {
                int from = perm[i], to = perm[i + 1];
                if (distMatrix[from][to] == INT_MAX) {
                    valid = false;
                    break;
                }
                cost += distMatrix[from][to];
            }
            if (valid && cost < bestCost) {
                bestCost = cost;
                bestPath = perm;
            }
        } while (next_permutation(perm.begin(), perm.end()));

        // Step 3: Reconstruct trip path
        trip.clear();
        total_cost = 0;

        for (int i = 0; i < bestPath.size() - 1; ++i) {
            int from = bestPath[i], to = bestPath[i + 1];
            auto& path = pathMatrix[from][to];
            QString travelPath;
            for (int j = 0; j < path.size(); ++j) {
                travelPath += QString::fromStdString(vertices[path[j]]);
                if (j < path.size() - 1) travelPath += " -> ";
            }

            TripEntry trip_entry;
            trip_entry.origin = QString::fromStdString(stadiums[bestPath[i]]);
            trip_entry.destination = travelPath;
            trip_entry.distance = distMatrix[from][to];
            trip_entry.type = "segment";
            trip.push_back(trip_entry);

            total_cost += distMatrix[from][to];

            cout << "Optimized Path: " << travelPath.toStdString()
                 << " (" << distMatrix[from][to] << " miles)\n";
        }

        cout << "Total Optimized Route Distance: " << total_cost << " miles\n";
    }
};

/**
 * @class PurchaseSummaryDialog
 * @brief Dialog for summarizing purchases.
 */
class PurchaseSummaryDialog : public QDialog {
public:
    /**
     * @brief Constructs a PurchaseSummaryDialog.
     * @param model The data model containing purchase information.
     * @param parent Optional parent widget.
     */
    PurchaseSummaryDialog(QStandardItemModel* model, QWidget* parent = nullptr) : QDialog(parent) {
        setWindowTitle("Purchase Summary");
        resize(650, 400); // Increase dialog size to fit data

        QVBoxLayout* mainLayout = new QVBoxLayout(this);

        tableView = new QTableView(this);
        tableView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        mainLayout->addWidget(tableView);

        summaryModel = new QStandardItemModel(this);
        summaryModel->setHorizontalHeaderLabels({"College", "Total Purchases ($)"});
        tableView->setModel(summaryModel);

        grandTotalLabel = new QLabel(this);
        grandTotalLabel->setAlignment(Qt::AlignCenter);
        grandTotalLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
        mainLayout->addWidget(grandTotalLabel);

        calculateSummary(model);

        // Set column widths
        tableView->setColumnWidth(0, 400); // School column
        tableView->setColumnWidth(1, 180); // Total Purchases column

        // Connect itemChanged signal to update summary dynamically
        connect(model, &QStandardItemModel::itemChanged, this, &PurchaseSummaryDialog::onItemChanged);
    }

private:
    /// @brief Converts a string with a dollar sign to a float.
    float stringToFloatDollar(const QString& str) {
        QString modifiedStr = str.trimmed();
        if (!modifiedStr.isEmpty() && modifiedStr[0] == '$') {
            modifiedStr.remove(0, 1); // Remove dollar sign
        }
        bool ok;
        float result = modifiedStr.toFloat(&ok);
        return ok ? result : 0.0f; // Return 0.0 if conversion fails
    }

    /// @brief Calculates the total purchases per college.
    void calculateSummary(QStandardItemModel* model) {
        if (!model) return;

        QMap<QString, float> schoolTotals;
        float grandTotal = 0.0f;

        QString currentSchool; // Keep track of the last valid college name

        for (int row = 0; row < model->rowCount(); ++row) {
            QStandardItem* schoolItem = model->item(row, 0);
            QStandardItem* souvenirItem = model->item(row, 1);
            QStandardItem* costItem = model->item(row, 2);
            QStandardItem* quantityItem = model->item(row, 3);

            if (!costItem || !quantityItem) continue; // Skip invalid rows

            // If the college name exists, update our tracking variable
            QString school = schoolItem ? schoolItem->text().trimmed() : "";
            if (!school.isEmpty()) {
                currentSchool = school; // Store the latest valid school name
            }

            // Skip invalid rows (must have a valid school & souvenir)
            if (currentSchool.isEmpty() || !souvenirItem) continue;

            float cost = stringToFloatDollar(costItem->text());

            // Get latest quantity entered
            bool ok;
            int quantity = quantityItem->text().toInt(&ok);
            if (!ok || quantity < 0) quantity = 0; // Prevent invalid/negative values

            float totalPurchase = cost * quantity;
            schoolTotals[currentSchool] += totalPurchase;
            grandTotal += totalPurchase;
        }

        // Clear and repopulate summary table
        summaryModel->clear();
        summaryModel->setHorizontalHeaderLabels({"Team", "Total Purchases ($)"});

        for (auto it = schoolTotals.constBegin(); it != schoolTotals.constEnd(); ++it) {
            QList<QStandardItem*> rowItems;
            rowItems.append(new QStandardItem(it.key())); // School name
            rowItems.append(new QStandardItem(QString("$%1").arg(QString::number(it.value(), 'f', 2)))); // Total purchase
            summaryModel->appendRow(rowItems);
        }

        // Display Grand Total
        grandTotalLabel->setText(QString("Grand Total: $%1").arg(QString::number(grandTotal, 'f', 2)));
    }


    /// @brief Updates the purchase summary when an item changes.
    void onItemChanged(QStandardItem* item) {
        if (item->column() == 3) { // Only react to quantity changes
            calculateSummary(item->model()); // Recalculate totals with updated data
        }
    }

    QTableView* tableView;
    QStandardItemModel* summaryModel;
    QLabel* grandTotalLabel;
};

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <climits>

using namespace std;

/**
 * @class GraphGreedy
 * @brief Represents an undirected weighted graph used to compute a greedy path through selected stadiums.
 *
 * This class is used to generate a greedy route starting from a specified stadium and visiting a set
 * of other stadiums by always choosing the nearest unvisited neighbor.
 */
class GraphGreedy {
private:
    std::vector<std::string> vertices;              /**< List of vertex names (e.g., stadiums). */
    std::map<std::string, int> vertexIndex;         /**< Maps stadium names to indices in the adjacency matrix. */
    std::vector<std::vector<int>> adjMatrix;        /**< Adjacency matrix storing distances between stadiums. */
    std::vector<TripEntry> trip;                    /**< List of trip entries representing the computed route. */
    int total_cost = 0;                             /**< Total mileage of the computed greedy route. */

public:
    /**
     * @brief Constructor that initializes the graph with given node names.
     * @param nodes List of stadium names to use as graph vertices.
     */
    GraphGreedy(const vector<string>& nodes) {
        vertices = nodes;
        int n = nodes.size();
        adjMatrix.resize(n, vector<int>(n, -1));
        for (int i = 0; i < n; i++) {
            vertexIndex[nodes[i]] = i;
        }
    }

    /**
     * @brief Adds an undirected edge between two stadiums with the specified distance.
     * @param from Name of the starting stadium.
     * @param to Name of the destination stadium.
     * @param cost Distance (in miles) between the two stadiums.
     */
    void addEdge(const string& from, const string& to, int cost) {
        int u = vertexIndex[from];
        int v = vertexIndex[to];
        adjMatrix[u][v] = cost;
        adjMatrix[v][u] = cost; // undirected
    }

    /**
     * @brief Computes a greedy route through the specified stadiums starting from a given stadium.
     *
     * At each step, the algorithm moves to the nearest unvisited stadium.
     * The resulting path and total cost are stored internally.
     *
     * @param startStadium The name of the stadium to start from.
     * @param stadiumsToVisit List of stadium names to include in the trip.
     */
    void greedyRouteThroughStadiums(const string& startStadium, const vector<string>& stadiumsToVisit) {
        if (stadiumsToVisit.empty()) return;

        trip.clear();
        total_cost = 0;

        // Add all stadiums to visit into a set
        set<string> remaining(stadiumsToVisit.begin(), stadiumsToVisit.end());
        remaining.insert(startStadium); // Ensure start is included
        string current = startStadium;
        remaining.erase(current);

        //cout << "Greedy Route Starting from: " << current << "\n";

        while (!remaining.empty()) {
            int u = vertexIndex[current];
            string nextStadium;
            int shortest = INT_MAX;

            for (const string& candidate : remaining) {
                int v = vertexIndex[candidate];
                int dist = adjMatrix[u][v];
                if (dist != -1 && dist < shortest) {
                    shortest = dist;
                    nextStadium = candidate;
                }
            }

            if (nextStadium.empty()) {
                cout << "No reachable unvisited stadiums from " << current << ".\n";
                break;
            }

            // Record the trip
            TripEntry trip_entry;
            trip_entry.origin = QString::fromStdString(current);
            trip_entry.destination = QString::fromStdString(nextStadium);
            trip_entry.distance = shortest;
            trip_entry.type = "forward";
            trip.push_back(trip_entry);

            //cout << current << " -> " << nextStadium << " (" << shortest << " miles)\n";

            total_cost += shortest;
            current = nextStadium;
            remaining.erase(current);
        }

        cout << "Total Greedy Distance: " << total_cost << " miles\n";
    }

    /**
     * @brief Retrieves the total cost (mileage) of the last computed route.
     * @return Total distance in miles.
     */
    int getTotalCost() const {
        return total_cost;
    }

    /**
     * @brief Retrieves the trip details (edges taken) from the last computed route.
     * @return A vector of TripEntry structures containing origin, destination, distance, and type.
     */
    vector<TripEntry> getTripDetails() const {
        return trip;
    }

};



#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

/**
 * @class GraphGreedyThrough
 * @brief Implements various greedy and optimized traversal algorithms for visiting stadiums in a weighted graph.
 *
 * This class includes algorithms such as BFS shortest path, 2-opt optimization,
 * Held-Karp TSP variant, and greedy routing to compute efficient routes
 * through a network of stadiums represented as vertices in an undirected graph.
 */
class GraphGreedyThrough {
private:
    std::vector<std::string> vertices;              /**< List of stadiums (graph vertices). */
    std::map<std::string, int> vertexIndex;         /**< Mapping from stadium names to indices. */
    std::vector<std::vector<int>> adjMatrix;        /**< Adjacency matrix storing distances. */
    std::vector<TripEntry> trip;                    /**< Stores the details of the traversal. */
    int total_cost = 0;                             /**< Total distance of the traversal. */

public:
    /**
     * @brief Constructs the graph from a list of stadium names.
     * @param nodes Vector of stadium names.
     */
    GraphGreedyThrough(const vector<string>& nodes) {
        vertices = nodes;
        int n = nodes.size();
        adjMatrix.resize(n, vector<int>(n, -1));
        for (int i = 0; i < n; i++) {
            vertexIndex[nodes[i]] = i;
        }
    }

    /**
     * @brief Adds a bidirectional edge between two stadiums.
     * @param from Source stadium.
     * @param to Destination stadium.
     * @param cost Distance between stadiums.
     */
    void addEdge(const string& from, const string& to, int cost) {
        int u = vertexIndex[from];
        int v = vertexIndex[to];
        adjMatrix[u][v] = cost;
        adjMatrix[v][u] = cost; // undirected
    }

    /**
     * @brief Finds the shortest path using BFS between two stadium indices.
     * @param start Starting index.
     * @param end Ending index.
     * @param path Output parameter to store the shortest path.
     * @return Total distance of the path or -1 if unreachable.
     */
    int bfsShortestPath(int start, int end, vector<int>& path) {
        int n = vertices.size();
        vector<bool> visited(n, false);
        vector<int> prev(n, -1);
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == end) break;

            for (int v = 0; v < n; ++v) {
                if (adjMatrix[u][v] != -1 && !visited[v]) {
                    visited[v] = true;
                    prev[v] = u;
                    q.push(v);
                }
            }
        }

        if (!visited[end]) return -1; // unreachable

        // Reconstruct path
        for (int at = end; at != -1; at = prev[at])
            path.push_back(at);
        reverse(path.begin(), path.end());

        // Calculate total distance
        int total = 0;
        for (size_t i = 0; i < path.size() - 1; ++i)
            total += adjMatrix[path[i]][path[i + 1]];

        return total;
    }

    /**
     * @brief Computes shortest path through all stadiums from Marlins Park using Held-Karp algorithm.
     */
    void visitAllFromMarlinsShortest() {
        const string startStadium = "Marlins Park";
        int startIdx = vertexIndex[startStadium];
        int n = vertices.size();

        // Step 1: Compute all-pairs shortest path distance matrix
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        vector<vector<vector<int>>> paths(n, vector<vector<int>>(n));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                vector<int> path;
                int cost = bfsShortestPath(i, j, path);
                if (cost != -1) {
                    dist[i][j] = cost;
                    paths[i][j] = path;
                }
            }
        }

        // Step 2: Held-Karp TSP (no return to start)
        int VISITED_ALL = (1 << n) - 1;
        vector<vector<int>> dp(n, vector<int>(1 << n, INT_MAX));
        vector<vector<int>> parent(n, vector<int>(1 << n, -1));
        dp[startIdx][1 << startIdx] = 0;

        for (int mask = 0; mask < (1 << n); ++mask) {
            for (int u = 0; u < n; ++u) {
                if (!(mask & (1 << u))) continue;
                for (int v = 0; v < n; ++v) {
                    if ((mask & (1 << v)) || dist[u][v] == INT_MAX) continue;
                    int nextMask = mask | (1 << v);
                    int newDist = dp[u][mask] + dist[u][v];
                    if (newDist < dp[v][nextMask]) {
                        dp[v][nextMask] = newDist;
                        parent[v][nextMask] = u;
                    }
                }
            }
        }

        // Step 3: Find best endpoint (no return to start)
        int endIdx = -1;
        int minTourCost = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (i == startIdx) continue;
            if (dp[i][VISITED_ALL] < minTourCost) {
                minTourCost = dp[i][VISITED_ALL];
                endIdx = i;
            }
        }

        // Step 4: Reconstruct the path
        trip.clear();
        total_cost = 0;
        int mask = VISITED_ALL;
        vector<int> tour;
        int curr = endIdx;
        while (curr != -1) {
            tour.push_back(curr);
            int prev = parent[curr][mask];
            mask ^= (1 << curr);
            curr = prev;
        }
        reverse(tour.begin(), tour.end());

        cout << "Optimal Route Starting at Marlins Park:\n";
        for (size_t i = 0; i < tour.size() - 1; ++i) {
            const auto& segment = paths[tour[i]][tour[i + 1]];
            for (size_t j = 0; j < segment.size() - 1; ++j) {
                int from = segment[j], to = segment[j + 1];
                TripEntry entry;
                entry.origin = QString::fromStdString(vertices[from]);
                entry.destination = QString::fromStdString(vertices[to]);
                entry.distance = adjMatrix[from][to];
                entry.type = "discovery";
                trip.push_back(entry);
                total_cost += adjMatrix[from][to];

                cout << "\"" << vertices[from] << "\"  -  \"" << vertices[to] << "\"  =   "
                     << adjMatrix[from][to] << "  :  \"forward\"\n";
            }
        }

        cout << "Total Distance (shortest path through all stadiums): " << total_cost << " miles\n";
    }

    /**
     * @brief Returns shortest path distance between two nodes using Dijkstra's algorithm.
     */
    int getDistanceBetween(int from, int to) {
        vector<int> path;
        return dijkstraShortestPath(from, to, path);
    }

    /**
     * @brief Computes a 2-opt optimized tour starting from Marlins Park.
     */
    void visitAllFromMarlins2Opt() {
        const string startStadium = "Marlins Park";
        if (vertexIndex.find(startStadium) == vertexIndex.end()) {
            cout << "Error: Marlins Park not found in graph.\n";
            return;
        }

        trip.clear();
        total_cost = 0;

        // Step 1: Build initial greedy tour
        set<int> unvisited;
        for (int i = 0; i < vertices.size(); ++i)
            if (vertices[i] != startStadium)
                unvisited.insert(i);

        vector<int> tour;
        int current = vertexIndex[startStadium];
        tour.push_back(current);

        while (!unvisited.empty()) {
            int next = -1;
            int minCost = INT_MAX;
            vector<int> tempPath;

            for (int candidate : unvisited) {
                vector<int> path;
                int cost = dijkstraShortestPath(current, candidate, path);
                if (cost != -1 && cost < minCost) {
                    minCost = cost;
                    next = candidate;
                }
            }

            if (next == -1) break;
            tour.push_back(next);
            unvisited.erase(next);
            current = next;
        }

        // Step 2: Apply 2-opt optimization to tour
        bool improved = true;
        while (improved) {
            improved = false;
            for (size_t i = 1; i < tour.size() - 2; ++i) {
                for (size_t j = i + 1; j < tour.size() - 1; ++j) {
                    int A = tour[i - 1], B = tour[i];
                    int C = tour[j], D = tour[j + 1];

                    int before = getDistanceBetween(A, B) + getDistanceBetween(C, D);
                    int after = getDistanceBetween(A, C) + getDistanceBetween(B, D);

                    if (after < before) {
                        reverse(tour.begin() + i, tour.begin() + j + 1);
                        improved = true;
                    }
                }
            }
        }

        // Step 3: Build final trip details with full Dijkstra paths
        for (size_t i = 0; i < tour.size() - 1; ++i) {
            vector<int> path;
            int cost = dijkstraShortestPath(tour[i], tour[i + 1], path);
            if (cost == -1) continue;

            for (size_t k = 0; k < path.size() - 1; ++k) {
                int from = path[k], to = path[k + 1];
                TripEntry entry;
                entry.origin = QString::fromStdString(vertices[from]);
                entry.destination = QString::fromStdString(vertices[to]);
                entry.distance = adjMatrix[from][to];
                entry.type = "discovery";
                trip.push_back(entry);
                total_cost += adjMatrix[from][to];

                cout << "\"" << vertices[from] << "\"  -  \"" << vertices[to] << "\"  =   "
                     << adjMatrix[from][to] << "  :  \"2-opt\"\n";
            }
        }

        cout << "Total 2-opt Optimized Distance from Marlins Park: " << total_cost << " miles\n";
    }


    /**
     * @brief Computes a greedy route from Marlins Park using Dijkstra-based routing.
     */
    void visitAllFromMarlinsGreedy() {
        const string startStadium = "Marlins Park";
        if (vertexIndex.find(startStadium) == vertexIndex.end()) {
            cout << "Error: Marlins Park not found in graph.\n";
            return;
        }

        trip.clear();
        total_cost = 0;

        // Initialize all stadium indices as unvisited except start
        set<int> unvisited;
        for (int i = 0; i < vertices.size(); ++i) {
            if (vertices[i] != startStadium)
                unvisited.insert(i);
        }

        int currentIdx = vertexIndex[startStadium];
        cout << "Starting at: " << vertices[currentIdx] << "\n";

        while (!unvisited.empty()) {
            int nextIdx = -1;
            vector<int> bestPath;
            int minCost = INT_MAX;

            for (int candidate : unvisited) {
                vector<int> path;
                int cost = dijkstraShortestPath(currentIdx, candidate, path);
                if (cost != -1 && cost < minCost) {
                    minCost = cost;
                    nextIdx = candidate;
                    bestPath = path;
                }
            }

            if (nextIdx == -1) {
                cout << "No more reachable unvisited stadiums from " << vertices[currentIdx] << ".\n";
                break;
            }

            // Record each step in the Dijkstra path
            for (size_t i = 0; i < bestPath.size() - 1; ++i) {
                int from = bestPath[i];
                int to = bestPath[i + 1];

                TripEntry entry;
                entry.origin = QString::fromStdString(vertices[from]);
                entry.destination = QString::fromStdString(vertices[to]);
                entry.distance = adjMatrix[from][to];
                entry.type = "discovery";
                trip.push_back(entry);

                cout << "\"" << vertices[from] << "\"  -  \"" << vertices[to] << "\"  =   "
                     << adjMatrix[from][to] << "  :  \"forward\"\n";

                total_cost += adjMatrix[from][to];
            }

            currentIdx = nextIdx;
            unvisited.erase(currentIdx);
        }

        cout << "Total Greedy Distance from Marlins Park (Dijkstra routing): " << total_cost << " miles\n";
    }

    /**
     * @brief Standard Dijkstra implementation to find the shortest path between two nodes.
     * @param start Starting index.
     * @param end Ending index.
     * @param path Output vector to store the path indices.
     * @return Distance of the shortest path or -1 if not found.
     */
    int dijkstraShortestPath(int start, int end, vector<int>& path) {
        int n = vertices.size();
        vector<int> dist(n, INT_MAX);
        vector<int> prev(n, -1);
        vector<bool> visited(n, false);

        dist[start] = 0;
        using pii = pair<int, int>;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (visited[u]) continue;
            visited[u] = true;

            for (int v = 0; v < n; ++v) {
                if (adjMatrix[u][v] != -1) {
                    int newDist = dist[u] + adjMatrix[u][v];
                    if (newDist < dist[v]) {
                        dist[v] = newDist;
                        prev[v] = u;
                        pq.push({newDist, v});
                    }
                }
            }
        }

        if (dist[end] == INT_MAX) return -1;

        for (int at = end; at != -1; at = prev[at])
            path.push_back(at);
        reverse(path.begin(), path.end());

        return dist[end];
    }

    /**
     * @brief Computes the dream vacation route by visiting a sequence of stadiums.
     * @param startStadium Starting stadium name.
     * @param orderedDestinations Sequence of stadium names to visit in order.
     */
    void dreamVacationRoute(const string& startStadium, const vector<string>& orderedDestinations) {
        trip.clear();
        total_cost = 0;

        string current = startStadium;

        cout << "Dream Vacation Route Starting from: " << current << "\n";

        for (const string& nextStadium : orderedDestinations) {
            if (vertexIndex.find(current) == vertexIndex.end() || vertexIndex.find(nextStadium) == vertexIndex.end()) {
                cout << "Invalid stadium name: " << current << " or " << nextStadium << ".\n";
                continue;
            }

            int u = vertexIndex[current];
            int v = vertexIndex[nextStadium];

            vector<int> path;
            int pathCost = dijkstraShortestPath(u, v, path);

            if (pathCost == -1) {
                cout << "No path from " << current << " to " << nextStadium << ".\n";
                continue;
            }

            for (size_t i = 0; i < path.size() - 1; ++i) {
                int from = path[i];
                int to = path[i + 1];

                TripEntry entry;
                entry.origin = QString::fromStdString(vertices[from]);
                entry.destination = QString::fromStdString(vertices[to]);
                entry.distance = adjMatrix[from][to];
                entry.type = "discovery";
                trip.push_back(entry);

                cout << "\"" << vertices[from] << "\"  -  \"" << vertices[to] << "\"  =   "
                     << adjMatrix[from][to] << "  :  \"segment\"\n";

                total_cost += adjMatrix[from][to];
            }

            current = nextStadium;
        }

        cout << "Total Dream Vacation Distance: " << total_cost << " miles\n";
    }

    /**
     * @brief Computes a greedy route through a list of stadiums using BFS shortest paths.
     * @param startStadium The starting stadium.
     * @param stadiumsToVisit List of stadiums to include in the path.
     */
    void greedyRouteThroughStadiums(const string& startStadium, const vector<string>& stadiumsToVisit) {
        if (stadiumsToVisit.empty()) return;

        trip.clear();
        total_cost = 0;

        set<string> remaining(stadiumsToVisit.begin(), stadiumsToVisit.end());
        remaining.insert(startStadium); // ensure start is valid
        string current = startStadium;
        remaining.erase(current);

        cout << "Greedy Route Starting from: " << current << "\n";

        while (!remaining.empty()) {
            int u = vertexIndex[current];
            string nextStadium;
            vector<int> bestPath;
            int shortestPathCost = INT_MAX;

            for (const string& candidate : remaining) {
                int v = vertexIndex[candidate];
                vector<int> path;
                int cost = bfsShortestPath(u, v, path);  // path may backtrack

                if (cost != -1 && cost < shortestPathCost) {
                    nextStadium = candidate;
                    shortestPathCost = cost;
                    bestPath = path;
                }
            }

            if (nextStadium.empty()) {
                cout << "No reachable unvisited stadiums from " << current << ". Remaining: ";
                for (const string& s : remaining) cout << s << ", ";
                cout << endl;
                break;
            }

            for (size_t i = 0; i < bestPath.size() - 1; ++i) {
                int from = bestPath[i];
                int to = bestPath[i + 1];

                TripEntry entry;
                entry.origin = QString::fromStdString(vertices[from]);
                entry.destination = QString::fromStdString(vertices[to]);
                entry.distance = adjMatrix[from][to];
                entry.type = "discovery";
                trip.push_back(entry);

                cout << "\"" << vertices[from] << "\"  -  \"" << vertices[to] << "\"  =   "
                     << adjMatrix[from][to] << "  :  \"forward\"\n";
                total_cost += adjMatrix[from][to];
            }

            current = nextStadium;
            remaining.erase(current);
        }

        cout << "Total Greedy Distance: " << total_cost << " miles\n";
    }

    /**
     * @brief Returns the total distance of the last computed route.
     */
    int getTotalCost() const {
        return total_cost;
    }

    /**
     * @brief Returns the trip details from the last traversal.
     */
    vector<TripEntry> getTripDetails() const {
        return trip;
    }
};





#endif // UTILITY_H
