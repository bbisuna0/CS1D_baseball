#include "plantour.h"
#include "ui_plantour.h"
#include "teamdisplay.h"
#include "utility.h"
#include <vector>
#include <set>
#include "ui_tripdisplay.h"
#include "tripdisplay.h"
#include "teamselectdialog.h"

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
    // Plan a trip from Dodgers Stadium
    TeamSelectionDialog *teamDialog = new TeamSelectionDialog();
    teamDialog->excludeTeam("Los Angeles Dodgers");
    if (teamDialog->exec() == QDialog::Accepted) {
        QStringList selectedTeams = teamDialog->getSelectedStadiums();
        std::vector<std::string> stadiumstovisit;
        stadiumstovisit.push_back("Dodger Stadium");
        for (const QString& team : selectedTeams) {
            //qDebug() << "Selected team:" << team;
            stadiumstovisit.push_back(team.toStdString());
        }
        // teamdisplay *teamWin = new teamdisplay();
        // teamWin->show();
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

        GraphDijkstra graph(cities);

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

        //graph.traverseAllFrom("Dodger Stadium");
        //graph.dijkstra("Dodger Stadium");
        graph.dijkstraOptimizedRoute(stadiumstovisit);

        //cout << "-----------------------------\n";
        //graph.computePrimMST();
        //     explicit tripdisplay(const std::vector<TripEntry>& data, float totalDistance,
        std::vector<TripEntry> trip = graph.getTrips();
        for (auto t : trip){
            qDebug() << t.origin << " - " << t.destination << " =  " << t.distance << " : " << t.type;
        }
        int total_distance = graph.totalCost();

        // Setup teams selected for souvenir purchase
        QStringList souvenirTeams = teamDialog->getSelectedTeams();
        souvenirTeams.append("Los Angeles Dodgers");
        souvenirTeams.sort();

        std::vector<std::string> teamSouvenirs;

        for(auto t : souvenirTeams)
            teamSouvenirs.push_back(t.toStdString());

        tripdisplay *tripWin = new tripdisplay(trip, total_distance, true);
        tripWin->setTeams(teamSouvenirs);
        tripWin->show();
    }
}


void plantour::on_pb_team_report_clicked()
{
    // Plan shortest custom trip

    // StadiumSelectionDialog *stadiumDialog = new StadiumSelectionDialog();
    // stadiumDialog->show();
    TeamSelectionDialog *teamDialog = new TeamSelectionDialog();
    if (teamDialog->exec() == QDialog::Accepted) {
        QStringList selectedTeams = teamDialog->getSelectedStadiums();

        // for (const QString& team : selectedTeams) {
        //     qDebug() << "Selected team:" << team;
        // }

        // dreamVacationRoute(const string& startStadium, const vector<string>& orderedDestinations)


        std::vector<std::string> stadiumstovisit;
        std::string startstadium = "";
        //stadiumstovisit.push_back("Marlins Stadium");
        for (const QString& team : selectedTeams) {
            //qDebug() << "Selected team:" << team;
            if (startstadium == "")
                startstadium = team.toStdString();
            else
                stadiumstovisit.push_back(team.toStdString());
        }
        // teamdisplay *teamWin = new teamdisplay();
        // teamWin->show();
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

        GraphGreedyThrough graph(cities);

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

        //graph.traverseAllFrom("Dodger Stadium");
        //graph.dijkstra("Dodger Stadium");
        graph.dreamVacationRoute(startstadium, stadiumstovisit);

        //cout << "-----------------------------\n";
        //graph.computePrimMST();
        //     explicit tripdisplay(const std::vector<TripEntry>& data, float totalDistance,
        std::vector<TripEntry> trip = graph.getTripDetails();
        for (auto t : trip){
            qDebug() << t.origin << " - " << t.destination << " =  " << t.distance << " : " << t.type;
        }
        int total_distance = graph.getTotalCost();

        // Setup teams selected for souvenir purchase
        QStringList souvenirTeams = teamDialog->getSelectedTeams();
        souvenirTeams.sort();

        std::vector<std::string> teamSouvenirs;

        for(auto t : souvenirTeams)
            teamSouvenirs.push_back(t.toStdString());

        tripdisplay *tripWin = new tripdisplay(trip, total_distance, true);
        tripWin->setTeams(teamSouvenirs);
        tripWin->show();
    }
}


void plantour::on_pb_maintenance_clicked()
{
    // MST

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

    // DFS

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
    // BFS

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


void plantour::on_pb_plan_vacation_clicked()
{
    // Plan a custom trip, recursive selection

    // StadiumSelectionDialog *stadiumDialog = new StadiumSelectionDialog();
    // stadiumDialog->show();
    TeamSelectionDialog *teamDialog = new TeamSelectionDialog();
    if (teamDialog->exec() == QDialog::Accepted) {
        QStringList selectedTeams = teamDialog->getSelectedStadiums();

        std::vector<std::string> stadiumstovisit;
        std::string startstadium = "";
        //stadiumstovisit.push_back("Marlins Stadium");
        for (const QString& team : selectedTeams) {
            //qDebug() << "Selected team:" << team;
            if (startstadium == "")
                startstadium = team.toStdString();
            else
                stadiumstovisit.push_back(team.toStdString());
        }
        // teamdisplay *teamWin = new teamdisplay();
        // teamWin->show();
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

        GraphGreedyThrough graph(cities);

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

        //graph.traverseAllFrom("Dodger Stadium");
        //graph.dijkstra("Dodger Stadium");
        graph.greedyRouteThroughStadiums(startstadium, stadiumstovisit);

        //cout << "-----------------------------\n";
        //graph.computePrimMST();
        //     explicit tripdisplay(const std::vector<TripEntry>& data, float totalDistance,
        std::vector<TripEntry> trip = graph.getTripDetails();
        for (auto t : trip){
            qDebug() << t.origin << " - " << t.destination << " =  " << t.distance << " : " << t.type;
        }
        int total_distance = graph.getTotalCost();

        // Setup teams selected for souvenir purchase
        QStringList souvenirTeams = teamDialog->getSelectedTeams();
        souvenirTeams.sort();

        std::vector<std::string> teamSouvenirs;

        for(auto t : souvenirTeams)
            teamSouvenirs.push_back(t.toStdString());

        tripdisplay *tripWin = new tripdisplay(trip, total_distance, true);
        tripWin->setTeams(teamSouvenirs);

        tripWin->show();
    }
}


void plantour::on_pb_stadium_report_clicked()
{
    // Plan to visit all stadiums starting at Marlins Park

    QSqlTableModel model;
    model.setTable("teams");
    model.select();

    QStringList souvenirTeams;

    QSet<QString> seenTeams;
    for (int i = 0; i < model.rowCount(); ++i) {
        QSqlRecord record = model.record(i);
        QString teamName = record.value("stadium_name").toString();
        souvenirTeams.append(record.value("team_name").toString());
        if (!seenTeams.contains(teamName)) {
            //if (teamName != "Marlins Park")
                seenTeams.insert(teamName);
            qDebug() << teamName << " = " << record.value("team_name").toString();
        }
    }

    std::vector<std::string> stadiumstovisit;
    //stadiumstovisit.push_back("Marlins Stadium");
    for (const QString& team : seenTeams) {
        qDebug() << "Selected team:" << team;
        //if (team != "Marlins Park")
            stadiumstovisit.push_back(team.toStdString());
    }
    // teamdisplay *teamWin = new teamdisplay();
    // teamWin->show();
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

    for (auto c : stadiums){
        cities.push_back(c);
        //qDebug() << c << "!";
    }

    GraphGreedyThrough graph(cities);

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

    //graph.traverseAllFrom("Dodger Stadium");
    //graph.dijkstra("Dodger Stadium");
    //graph.greedyRouteThroughStadiums("Marlins Park", stadiumstovisit);

    graph.visitAllFromMarlinsGreedy();
    //graph.visitAllFromMarlins2Opt();

    //cout << "-----------------------------\n";
    //graph.computePrimMST();
    //     explicit tripdisplay(const std::vector<TripEntry>& data, float totalDistance,
    std::vector<TripEntry> trip = graph.getTripDetails();
    for (auto t : trip){
        qDebug() << t.origin << " - " << t.destination << " =  " << t.distance << " : " << t.type;
    }
    int total_distance = graph.getTotalCost();

    // Setup teams selected for souvenir purchase

    souvenirTeams.sort();
    std::vector<std::string> teamSouvenirs;

    for(auto t : souvenirTeams)
        teamSouvenirs.push_back(t.toStdString());

    tripdisplay *tripWin = new tripdisplay(trip, total_distance, true);
    tripWin->setTeams(teamSouvenirs);
    tripWin->show();
}

