#ifndef DB_H
#define DB_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
#include <QSqlTableModel>

// class db
// {
// public:
//     db();
// };

struct DistanceEntry {
    QString origin;
    QString destination;
    int distance;
};


struct TeamEntry {
    QString teamName;
    QString stadiumName;
    int seatingCapacity;
    QString location;
    QString playingSurface;
    QString league;
    int dateOpened;
    QString distanceToCenterField;
    QString ballparkTypology;
    QString roofType;
};

// Function headers
bool insertStadiumDistances(QSqlDatabase& db);
bool createStadiumDistancesTable(QSqlDatabase& db);
bool createTeamsTable(QSqlDatabase& db);
bool insertTeamsData(QSqlDatabase& db);

#endif // DB_H
