#ifndef DB_H
#define DB_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
#include <QSqlTableModel>

/**
 * @struct DistanceEntry
 * @brief Represents a travel distance between two stadiums.
 */
struct DistanceEntry {
    QString origin;       /**< Name of the origin stadium. */
    QString destination;  /**< Name of the destination stadium. */
    int distance;         /**< Distance in miles between the stadiums. */
};

/**
 * @struct TripEntry
 * @brief Represents a trip leg with a distance and edge type.
 */
struct TripEntry {
    QString origin;       /**< Name of the origin stadium. */
    QString destination;  /**< Name of the destination stadium. */
    int distance;         /**< Distance in miles. */
    QString type;         /**< Type of trip edge (e.g., "Discovery", "Back"). */

    bool operator==(const TripEntry& other) const {
        return origin == other.origin &&
               destination == other.destination &&
               distance == other.distance &&
               type == other.type;
    }
};

/**
 * @struct TeamEntry
 * @brief Represents team and stadium information.
 */
struct TeamEntry {
    QString teamName;                /**< Name of the team. */
    QString stadiumName;             /**< Name of the stadium. */
    int seatingCapacity;            /**< Stadium seating capacity. */
    QString location;                /**< City and state. */
    QString playingSurface;          /**< Type of field surface. */
    QString league;                  /**< League the team belongs to. */
    int dateOpened;                  /**< Year the stadium opened. */
    QString distanceToCenterField;   /**< Distance to center field. */
    QString ballparkTypology;        /**< Typology of the ballpark. */
    QString roofType;                /**< Type of roof. */
};

/**
 * @struct Souvenir
 * @brief Represents a souvenir item and its price.
 */
struct Souvenir {
    QString name;    /**< Name of the souvenir. */
    double price;    /**< Price of the souvenir. */
};

/**
 * @struct SouvenirData
 * @brief Represents a souvenir available at a team stadium.
 */
struct SouvenirData {
    QString team;      /**< The name of the team. */
    QString souvenir;  /**< The name of the souvenir. */
    double price;      /**< The cost of the souvenir. */
};

/**
 * @struct SouvenirPurchase
 * @brief Represents a purchased souvenir with quantity.
 */
struct SouvenirPurchase {
    QString team;      /**< The name of the team. */
    QString souvenir;  /**< The name of the souvenir. */
    QString price;     /**< The cost of the souvenir (formatted). */
    int quantity;      /**< The quantity purchased. */
};

// =========================
// Function Prototypes
// =========================

/**
 * @brief Inserts predefined stadium distances into the database.
 * @param db Reference to the active database connection.
 * @return true on success, false otherwise.
 */
bool insertStadiumDistances(QSqlDatabase& db);

/**
 * @brief Creates the stadium_distances table if it doesn't exist.
 * @param db Reference to the active database connection.
 * @return true on success, false otherwise.
 */
bool createStadiumDistancesTable(QSqlDatabase& db);

/**
 * @brief Creates the teams table if it doesn't exist.
 * @param db Reference to the active database connection.
 * @return true on success, false otherwise.
 */
bool createTeamsTable(QSqlDatabase& db);

/**
 * @brief Creates the souvenirs table if it doesn't exist.
 * @param db Reference to the active database connection.
 * @return true on success, false otherwise.
 */
bool createSouvenirsTable(QSqlDatabase& db);

/**
 * @brief Inserts default MLB team and stadium data into the teams table.
 * @param db Reference to the active database connection.
 * @return true if all inserts succeed, false otherwise.
 */
bool insertTeamsData(QSqlDatabase& db);

/**
 * @brief Inserts default souvenirs for all teams into the souvenirs table.
 * @param db Reference to the active database connection.
 * @return true if all inserts succeed, false otherwise.
 */
bool addDefaultSouvenirs(QSqlDatabase& db);

/**
 * @brief Drops and recreates all data tables (teams, distances, souvenirs), and populates them.
 * @param db Reference to the active database connection.
 * @return true on success, false otherwise.
 */
bool resetContent(QSqlDatabase& db);

/**
 * @brief Resets all content, including the user table and related data.
 * @param db Reference to the active database connection.
 * @return true on success, false otherwise.
 */
bool resetAllContent(QSqlDatabase& db);

/**
 * @brief Adds a new team entry such as the Las Vegas Gamblers to the teams table.
 * @param db Reference to the active database connection.
 * @return true on success, false otherwise.
 */
bool addTeamsData(QSqlDatabase& db);

/**
 * @brief Adds distances between Las Vegas Stadium and select other stadiums.
 * @param db Reference to the active database connection.
 * @return true on success, false otherwise.
 */
bool addStadiumDistances(QSqlDatabase& db);

/**
 * @brief Performs a batch insert of new team, stadium location, and distance data.
 * @param db Reference to the active database connection.
 * @return true on success, false otherwise.
 */
bool addBulkData(QSqlDatabase& db);

/**
 * @brief Creates the stadium_location table for storing widget coordinates.
 * @param db Reference to the active database connection.
 * @return true on success, false otherwise.
 */
bool createStadiumLocationTable(QSqlDatabase& db);

/**
 * @brief Inserts default locations (x, y) for stadiums into stadium_location.
 * @param db Reference to the active database connection.
 * @return true on success, false otherwise.
 */
bool insertStadiumLocationData(QSqlDatabase& db);

/**
 * @brief Adds location data for new stadiums such as Las Vegas Stadium.
 * @param db Reference to the active database connection.
 * @return true on success, false otherwise.
 */
bool addStadiumLocationData(QSqlDatabase& db);



#endif // DB_H
