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


struct TripEntry {
    QString origin;
    QString destination;
    int distance;
    QString type;
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


struct Souvenir {
    QString name;
    double price;
};


/**
 * @struct SouvenirData
 * @brief Represents a souvenir available at a college.
 */
struct SouvenirData {
    QString team; /**< The name of the college. */
    QString souvenir; /**< The name of the souvenir. */
    double price; /**< The cost of the souvenir. */
};


/**
 * @struct SouvenirPurchase
 * @brief Represents a purchased souvenir with quantity.
 */
struct SouvenirPurchase {
    QString team; /**< The name of the college. */
    QString souvenir; /**< The name of the souvenir. */
    QString price; /**< The cost of the souvenir. */
    int quantity; /**< The quantity of the souvenir purchased. */
};


// Function headers
bool insertStadiumDistances(QSqlDatabase& db);
bool createStadiumDistancesTable(QSqlDatabase& db);
bool createTeamsTable(QSqlDatabase& db);
bool createSouvenirsTable(QSqlDatabase& db);
bool insertTeamsData(QSqlDatabase& db);
bool addDefaultSouvenirs(QSqlDatabase& db);
bool resetContent(QSqlDatabase& db);
bool resetAllContent(QSqlDatabase& db);
bool addTeamsData(QSqlDatabase& db);
bool addStadiumDistances(QSqlDatabase& db);
bool addBulkData(QSqlDatabase& db);


#endif // DB_H
