#include "plantour.h"
#include "ui_plantour.h"
#include "teamdisplay.h"
#include "utility.h"
#include <vector>
#include <set>
#include "ui_tripdisplay.h"
#include "tripdisplay.h"

plantour::plantour(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::plantour)
{
    ui->setupUi(this);
}

plantour::~plantour()
{
    delete ui;
}

void plantour::on_pb_exit_clicked()
{
    close();
}


void plantour::on_pb_team_details_clicked()
{
    teamdisplay *teamWin = new teamdisplay();
    teamWin->show();
}


void plantour::on_pb_team_report_clicked()
{
    StadiumSelectionDialog *stadiumDialog = new StadiumSelectionDialog();
    stadiumDialog->show();
}


void plantour::on_pb_maintenance_clicked()
{


    QSqlTableModel *stadium_data;
    stadium_data = new QSqlTableModel(this);
    stadium_data->setTable("stadium_distances");
    stadium_data->select();

    std::set<std::string> stadiums;

    for (int row = 0; row < stadium_data->rowCount(); ++row) {
        QModelIndex index = stadium_data->index(row, 0); //origin
        QVariant value = stadium_data->data(index);
        std::string origin = value.toString().toStdString();
        index = stadium_data->index(row, 1); //destination
        value = stadium_data->data(index);
        std::string destination = value.toString().toStdString();
        stadiums.insert(origin);
        stadiums.insert(destination);
    }

    std::vector<std::string> cities;

    for (auto c : stadiums)
        cities.push_back(c);

    GraphMST graph(cities);

    for (int row = 0; row < stadium_data->rowCount(); ++row) {
        QModelIndex index = stadium_data->index(row, 0); //origin
        QVariant value = stadium_data->data(index);
        std::string origin = value.toString().toStdString();
        index = stadium_data->index(row, 1); //destination
        value = stadium_data->data(index);
        std::string destination = value.toString().toStdString();
        index = stadium_data->index(row, 2); //distance
        value = stadium_data->data(index);
        int distance = value.toInt();
        graph.addEdge(origin, destination, distance);
    }

    graph.computeKruskalMST();
    //cout << "-----------------------------\n";
    //graph.computePrimMST();
    //     explicit tripdisplay(const std::vector<TripEntry>& data, float totalDistance,
    std::vector<TripEntry> trip = graph.getTrips();
    for (auto t : trip){
        qDebug() << t.origin << " - " << t.destination << " =  " << t.distance << " : " << t.type;
    }
    int total_distance = graph.totalCost();

    tripdisplay *tripWin = new tripdisplay(trip, total_distance, false);
    tripWin->show();
}


void plantour::on_pushButton_clicked()
{
    QSqlTableModel *stadium_data;
    stadium_data = new QSqlTableModel(this);
    stadium_data->setTable("stadium_distances");
    stadium_data->select();

    std::set<std::string> stadiums;

    for (int row = 0; row < stadium_data->rowCount(); ++row) {
        QModelIndex index = stadium_data->index(row, 0); //origin
        QVariant value = stadium_data->data(index);
        std::string origin = value.toString().toStdString();
        index = stadium_data->index(row, 1); //destination
        value = stadium_data->data(index);
        std::string destination = value.toString().toStdString();
        stadiums.insert(origin);
        stadiums.insert(destination);
    }

    std::vector<std::string> cities;

    for (auto c : stadiums)
        cities.push_back(c);

    Graph graph(cities);

    for (int row = 0; row < stadium_data->rowCount(); ++row) {
        QModelIndex index = stadium_data->index(row, 0); //origin
        QVariant value = stadium_data->data(index);
        std::string origin = value.toString().toStdString();
        index = stadium_data->index(row, 1); //destination
        value = stadium_data->data(index);
        std::string destination = value.toString().toStdString();
        index = stadium_data->index(row, 2); //distance
        value = stadium_data->data(index);
        int distance = value.toInt();
        graph.addEdge(origin, destination, distance);
    }

    graph.dfs("Oracle Park");
    //cout << "-----------------------------\n";
    //graph.computePrimMST();
    //     explicit tripdisplay(const std::vector<TripEntry>& data, float totalDistance,
    std::vector<TripEntry> trip = graph.getTrips();
    for (auto t : trip){
        qDebug() << t.origin << " - " << t.destination << " =  " << t.distance << " : " << t.type;
    }
    int total_distance = graph.totalCost();

    tripdisplay *tripWin = new tripdisplay(trip, total_distance, false);
    tripWin->show();
}


void plantour::on_pushButton_2_clicked()
{
    QSqlTableModel *stadium_data;
    stadium_data = new QSqlTableModel(this);
    stadium_data->setTable("stadium_distances");
    stadium_data->select();

    std::set<std::string> stadiums;

    for (int row = 0; row < stadium_data->rowCount(); ++row) {
        QModelIndex index = stadium_data->index(row, 0); //origin
        QVariant value = stadium_data->data(index);
        std::string origin = value.toString().toStdString();
        index = stadium_data->index(row, 1); //destination
        value = stadium_data->data(index);
        std::string destination = value.toString().toStdString();
        stadiums.insert(origin);
        stadiums.insert(destination);
    }

    std::vector<std::string> cities;

    for (auto c : stadiums)
        cities.push_back(c);

    GraphBFS graph(cities);

    for (int row = 0; row < stadium_data->rowCount(); ++row) {
        QModelIndex index = stadium_data->index(row, 0); //origin
        QVariant value = stadium_data->data(index);
        std::string origin = value.toString().toStdString();
        index = stadium_data->index(row, 1); //destination
        value = stadium_data->data(index);
        std::string destination = value.toString().toStdString();
        index = stadium_data->index(row, 2); //distance
        value = stadium_data->data(index);
        int distance = value.toInt();
        graph.addEdge(origin, destination, distance);
    }

    graph.bfs("Target Field");
    //cout << "-----------------------------\n";
    //graph.computePrimMST();
    //     explicit tripdisplay(const std::vector<TripEntry>& data, float totalDistance,
    std::vector<TripEntry> trip = graph.getTrips();
    for (auto t : trip){
        qDebug() << t.origin << " - " << t.destination << " =  " << t.distance << " : " << t.type;
    }
    int total_distance = graph.totalCost();

    tripdisplay *tripWin = new tripdisplay(trip, total_distance, false);
    tripWin->show();
}

