#include "db.h"

/**
 * @brief Inserts distance data between stadiums into the 'stadium_distances' table.
 * @param db The active QSqlDatabase connection.
 * @return true if data was inserted successfully, false on error.
 */
bool insertStadiumDistances(QSqlDatabase& db) {
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery insertQuery(db);
    QSqlQuery checkQuery(db);

    insertQuery.prepare(R"(
        INSERT INTO stadium_distances (origin, destination, distance)
        VALUES (?, ?, ?)
    )");

    checkQuery.prepare("SELECT COUNT(*) FROM stadium_distances "
                       "WHERE origin = ? AND destination = ? AND distance = ?");


    QList<DistanceEntry> entries = {
        {"Angel Stadium", "Petco Park", 110},
        {"Angel Stadium", "Dodger Stadium", 50},
        {"Busch Stadium", "Minute Maid Park", 680},
        {"Busch Stadium", "Great American Ball Park", 310},
        {"Busch Stadium", "Target Field", 465},
        {"Busch Stadium", "Kauffman Stadium", 235},
        {"Chase Field", "Coors Field", 580},
        {"Chase Field", "Globe Life Park in Arlington", 870},
        {"Chase Field", "Minute Maid Park", 1115},
        {"Chase Field", "Oakland-Alameda County Coliseum", 650},
        {"Chase Field", "Petco Park", 300},
        {"Citi Field", "Fenway Park", 195},
        {"Citi Field", "Yankee Stadium", 50},
        {"Citizens Bank Park", "Yankee Stadium", 80},
        {"Citizens Bank Park", "Oriole Park at Camden Yards", 90},
        {"Comerica Park", "Guaranteed Rate Field", 240},
        {"Comerica Park", "Rogers Centre", 210},
        {"Comerica Park", "Progressive Field", 90},
        {"Coors Field", "Kauffman Stadium", 560},
        {"Coors Field", "Globe Life Park in Arlington", 650},
        {"Coors Field", "Chase Field", 580},
        {"Coors Field", "Petco Park", 830},
        {"Dodger Stadium", "Angel Stadium", 50},
        {"Dodger Stadium", "Target Field", 1500},
        {"Dodger Stadium", "Oakland-Alameda County Coliseum", 340},
        {"Fenway Park", "Citi Field", 195},
        {"Fenway Park", "Marlins Park", 1255},
        {"Fenway Park", "Rogers Centre", 430},
        {"Globe Life Park in Arlington", "Chase Field", 870},
        {"Globe Life Park in Arlington", "Kauffman Stadium", 460},
        {"Globe Life Park in Arlington", "SunTrust Park", 740},
        {"Globe Life Park in Arlington", "Minute Maid Park", 230},
        {"Globe Life Park in Arlington", "Coors Field", 650},
        {"Great American Ball Park", "PNC Park", 260},
        {"Great American Ball Park", "Progressive Field", 225},
        {"Great American Ball Park", "Guaranteed Rate Field", 250},
        {"Great American Ball Park", "Tropicana Field", 790},
        {"Great American Ball Park", "SunTrust Park", 375},
        {"Great American Ball Park", "Busch Stadium", 310},
        {"Guaranteed Rate Field", "Comerica Park", 240},
        {"Guaranteed Rate Field", "Great American Ball Park", 250},
        {"Guaranteed Rate Field", "Wrigley Field", 50},
        {"Kauffman Stadium", "Busch Stadium", 235},
        {"Kauffman Stadium", "Globe Life Park in Arlington", 460},
        {"Kauffman Stadium", "Wrigley Field", 415},
        {"Kauffman Stadium", "Coors Field", 560},
        {"Marlins Park", "SunTrust Park", 600},
        {"Marlins Park", "Tropicana Field", 210},
        {"Marlins Park", "Nationals Park", 930},
        {"Marlins Park", "Fenway Park", 1255},
        {"Marlins Park", "Minute Maid Park", 965},
        {"Miller Park", "Rogers Centre", 430},
        {"Miller Park", "Wrigley Field", 80},
        {"Miller Park", "Target Field", 300},
        {"Minute Maid Park", "Globe Life Park in Arlington", 230},
        {"Minute Maid Park", "Tropicana Field", 790},
        {"Minute Maid Park", "Marlins Park", 965},
        {"Minute Maid Park", "Busch Stadium", 680},
        {"Minute Maid Park", "Chase Field", 1115},
        {"Nationals Park", "Oriole Park at Camden Yards", 50},
        {"Nationals Park", "PNC Park", 195},
        {"Nationals Park", "SunTrust Park", 560},
        {"Nationals Park", "Marlins Park", 930},
        {"Oakland-Alameda County Coliseum", "Oracle Park", 50},
        {"Oakland-Alameda County Coliseum", "Dodger Stadium", 340},
        {"Oakland-Alameda County Coliseum", "Chase Field", 650},
        {"Oracle Park", "Safeco Field", 680},
        {"Oracle Park", "Oakland-Alameda County Coliseum", 50},
        {"Oriole Park at Camden Yards", "Nationals Park", 50},
        {"Oriole Park at Camden Yards", "Citizens Bank Park", 90},
        {"Petco Park", "Coors Field", 830},
        {"Petco Park", "Chase Field", 300},
        {"Petco Park", "Angel Stadium", 110},
        {"PNC Park", "Nationals Park", 195},
        {"PNC Park", "Rogers Centre", 225},
        {"PNC Park", "Progressive Field", 115},
        {"PNC Park", "Great American Ball Park", 260},
        {"PNC Park", "Yankee Stadium", 315},
        {"Progressive Field", "PNC Park", 115},
        {"Progressive Field", "Comerica Park", 90},
        {"Progressive Field", "Great American Ball Park", 225},
        {"Rogers Centre", "PNC Park", 225},
        {"Rogers Centre", "Miller Park", 430},
        {"Rogers Centre", "Comerica Park", 210},
        {"Rogers Centre", "Fenway Park", 430},
        {"Rogers Centre", "Safeco Field", 2070},
        {"Safeco Field", "Rogers Centre", 2070},
        {"Safeco Field", "Target Field", 1390},
        {"Safeco Field", "Oracle Park", 680},
        {"SunTrust Park", "Great American Ball Park", 375},
        {"SunTrust Park", "Nationals Park", 560},
        {"SunTrust Park", "Marlins Park", 600},
        {"SunTrust Park", "Globe Life Park in Arlington", 740},
        {"Target Field", "Dodger Stadium", 1500},
        {"Target Field", "Busch Stadium", 465},
        {"Target Field", "Miller Park", 300},
        {"Target Field", "Safeco Field", 1390},
        {"Tropicana Field", "Great American Ball Park", 790},
        {"Tropicana Field", "Marlins Park", 210},
        {"Tropicana Field", "Minute Maid Park", 790},
        {"Wrigley Field", "Guaranteed Rate Field", 50},
        {"Wrigley Field", "Miller Park", 80},
        {"Wrigley Field", "Kauffman Stadium", 415},
        {"Yankee Stadium", "PNC Park", 315},
        {"Yankee Stadium", "Citizens Bank Park", 80},
        {"Yankee Stadium", "Citi Field", 50}
    };

    db.transaction(); // faster batch insert

    for (const DistanceEntry& entry : entries) {
        // Check if this entry already exists
        checkQuery.bindValue(0, entry.origin);
        checkQuery.bindValue(1, entry.destination);
        checkQuery.bindValue(2, entry.distance);

        if (!checkQuery.exec()) {
            qWarning() << "Check failed for" << entry.origin << "->" << entry.destination << ":" << checkQuery.lastError().text();
            db.rollback();
            return false;
        }

        if (checkQuery.next() && checkQuery.value(0).toInt() == 0) {
            // Doesn't exist, insert
            insertQuery.bindValue(0, entry.origin);
            insertQuery.bindValue(1, entry.destination);
            insertQuery.bindValue(2, entry.distance);

            if (!insertQuery.exec()) {
                qWarning() << "Insert failed for" << entry.origin << "->" << entry.destination << ":" << insertQuery.lastError().text();
                db.rollback();
                return false;
            }
        } else {
            qDebug() << "Distance already exists:" << entry.origin << "->" << entry.destination;
        }

    }

    return db.commit();
}


/**
 * @brief Creates the 'stadium_distances' table if it does not exist.
 * @param db The active QSqlDatabase connection.
 * @return true if the table was created or already exists, false on error.
 */
bool createStadiumDistancesTable(QSqlDatabase& db) {
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);

    // Check if table exists
    if (db.tables().contains("stadium_distances")) {
        qDebug() << "Table 'stadium_distances' already exists.";
        return false;
    }

    QString createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS stadium_distances (
            origin TEXT,
            destination TEXT,
            distance INTEGER
        );
    )";

    if (!query.exec(createTableSQL)) {
        qWarning() << "Failed to create table:" << query.lastError().text();
        return false;
    }

    qDebug() << "stadium_distances table created successfully!";
    return true;
}


/**
 * @brief Creates the 'teams' table if it does not already exist in the database.
 * @param db The database connection.
 * @return true on successful creation; false if an error occurred.
 */
bool createTeamsTable(QSqlDatabase& db) {
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);

    // Check if table exists
    if (db.tables().contains("teams")) {
        qDebug() << "Table 'teams' already exists.";
        return false;
    }

    // Create the teams table
    QString createTableSQL = R"(
        CREATE TABLE teams (
            team_name TEXT,
            stadium_name TEXT,
            seating_capacity INTEGER,
            location TEXT,
            playing_surface TEXT,
            league TEXT,
            date_opened INTEGER,
            distance_to_center_field TEXT,
            ballpark_typology TEXT,
            roof_type TEXT
        );
    )";

    if (!query.exec(createTableSQL)) {
        qWarning() << "Failed to create 'teams' table:" << query.lastError().text();
        return false;
    }

    qDebug() << "'teams' table created successfully!";
    return true;
}


/**
 * @brief Creates the 'stadium_location' table for tracking stadium widget coordinates.
 * @param db The database connection.
 * @return true if table creation succeeded; false otherwise.
 */
bool createStadiumLocationTable(QSqlDatabase& db) {
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);

    // Check if table exists
    if (db.tables().contains("stadium_location")) {
        qDebug() << "Table 'stadium_location' already exists.";
        return false;
    }

    // Create the stadium_location table
    QString createTableSQL = R"(
        CREATE TABLE stadium_location (
            stadium_name TEXT,
            x_loc INTEGER,
            y_loc INTEGER
        );
    )";

    if (!query.exec(createTableSQL)) {
        qWarning() << "Failed to create 'stadium_location' table:" << query.lastError().text();
        return false;
    }

    qDebug() << "'stadium_location' table created successfully!";
    return true;
}


/**
 * @brief Creates the 'souvenirs' table for storing souvenir items per team.
 * @param db The database connection.
 * @return true if the table was created successfully; false on error.
 */
bool createSouvenirsTable(QSqlDatabase& db) {
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);

    // Check if table exists
    if (db.tables().contains("souvenirs")) {
        qDebug() << "Table 'souvenirs' already exists.";
        return false;
    }

    // Create the souvenirs table
    // Step 1: Create the souvenirs table if it doesn't exist
    const QString createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS souvenirs (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            team_name TEXT NOT NULL,
            item_name TEXT NOT NULL,
            price REAL NOT NULL,
            FOREIGN KEY(team_name) REFERENCES teams(team_name),
            UNIQUE(team_name, item_name)
        )
    )";

    if (!query.exec(createTableSQL)) {
        qWarning() << "Failed to create 'souvenirs' table:" << query.lastError().text();
        return false;
    }

    qDebug() << "'souvenirs' table created successfully!";
    return true;
}



/**
 * @brief Inserts a predefined list of MLB teams and stadium data into the 'teams' table, checking for duplicates.
 * @param db The database connection.
 * @return true if all entries were inserted or already existed; false if a query failed.
 */
bool insertTeamsData(QSqlDatabase& db) {
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    QSqlQuery checkQuery(db);  // Separate query for checking existence

    query.prepare(R"(
        INSERT INTO teams (team_name, stadium_name, seating_capacity, location, playing_surface,
                           league, date_opened, distance_to_center_field, ballpark_typology, roof_type)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);
    )");

    QList<TeamEntry> entries = {
        {"Arizona Diamondbacks", "Chase Field", 48686, "Phoenix, Arizona", "Grass", "National", 1998, "407 feet (124 m)", "Retro Modern", "Retractable"},
        {"Atlanta Braves", "SunTrust Park", 41149, "Cumberland, Georgia", "Grass", "National", 2017, "400 feet (122 m)", "Retro Modern", "Open"},
        {"Baltimore Orioles", "Oriole Park at Camden Yards", 45971, "Baltimore, Maryland", "Grass", "American", 1992, "410 feet (125 m)", "Retro Classic", "Open"},
        {"Boston Red Sox", "Fenway Park", 37731, "Boston, Massachusetts", "Grass", "American", 1912, "420 feet (128 m)", "Jewel Box", "Open"},
        {"Chicago Cubs", "Wrigley Field", 41268, "Chicago, Illinois", "Grass", "National", 1914, "400 feet (122 m)", "Jewel Box", "Open"},
        {"Chicago White Sox", "Guaranteed Rate Field", 40615, "Chicago, Illinois", "Grass", "American", 1991, "400 feet (122 m)", "Retro Classic", "Open"},
        {"Cincinnati Reds", "Great American Ball Park", 42319, "Cincinnati, Ohio", "Grass", "National", 2003, "404 feet (123 m)", "Retro Modern", "Open"},
        {"Cleveland Indians", "Progressive Field", 35051, "Cleveland, Ohio", "Grass", "American", 1994, "410 feet (125 m)", "Retro Modern", "Open"},
        {"Colorado Rockies", "Coors Field", 50398, "Denver, Colorado", "Grass", "National", 1995, "415 feet (126 m)", "Retro Classic", "Open"},
        {"Detroit Tigers", "Comerica Park", 41299, "Detroit, Michigan", "Grass", "American", 2000, "420 feet (128 m)", "Retro Classic", "Open"},
        {"Houston Astros", "Minute Maid Park", 41168, "Houston, Texas", "Grass", "American", 2000, "409 feet (125 m)", "Retro Modern", "Retractable"},
        {"Kansas City Royals", "Kauffman Stadium", 37903, "Kansas City, Missouri", "Grass", "American", 1973, "410 feet (125 m)", "Retro Modern", "Open"},
        {"Los Angeles Angels", "Angel Stadium", 45477, "Anaheim, California", "Grass", "American", 1966, "396 feet (121 m)", "Retro Modern", "Open"},
        {"Los Angeles Dodgers", "Dodger Stadium", 56000, "Los Angeles, California", "Grass", "National", 1962, "400 feet (122 m)", "Modern", "Open"},
        {"Miami Marlins", "Marlins Park", 36742, "Miami, Florida", "Grass", "National", 2012, "407 feet (124 m)", "Contemporary", "Retractable"},
        {"Milwaukee Brewers", "Miller Park", 41900, "Milwaukee, Wisconsin", "Grass", "National", 2001, "400 feet (122 m)", "Retro Modern", "Retractable"},
        {"Minnesota Twins", "Target Field", 38885, "Minneapolis, Minnesota", "Grass", "American", 2010, "404 feet (123 m)", "Retro Modern", "Open"},
        {"New York Mets", "Citi Field", 41922, "Queens, New York", "Grass", "National", 2009, "408 feet (124 m)", "Retro Classic", "Open"},
        {"New York Yankees", "Yankee Stadium", 47422, "Bronx, New York", "Grass", "American", 2009, "408 feet (124 m)", "Retro Classic", "Open"},
        {"Oakland Athletics", "Oakland-Alameda County Coliseum", 47170, "Oakland, California", "Grass", "American", 1966, "400 feet (122 m)", "Multipurpose", "Open"},
        {"Philadelphia Phillies", "Citizens Bank Park", 43651, "Philadelphia, Pennsylvania", "Grass", "National", 2004, "401 feet (122 m)", "Retro Classic", "Open"},
        {"Pittsburgh Pirates", "PNC Park", 38362, "Pittsburgh, Pennsylvania", "Grass", "National", 2001, "399 feet (122 m)", "Retro Classic", "Open"},
        {"San Diego Padres", "Petco Park", 40209, "San Diego, California", "Grass", "National", 2004, "396 feet (121 m)", "Retro Modern", "Open"},
        {"San Francisco Giants", "Oracle Park", 41915, "San Francisco, California", "Grass", "National", 2000, "399 feet (122 m)", "Retro Classic", "Open"},
        {"Seattle Mariners", "Safeco Field", 47943, "Seattle, Washington", "Grass", "American", 1999, "401 feet (122 m)", "Retro Modern", "Retractable"},
        {"St. Louis Cardinals", "Busch Stadium", 45529, "St. Louis, Missouri", "Grass", "National", 2006, "400 feet (122 m)", "Retro Classic", "Open"},
        {"Tampa Bay Rays", "Tropicana Field", 31042, "St. Petersburg, Florida", "AstroTurf GameDay Grass", "American", 1990, "404 feet (123 m)", "Multipurpose", "Fixed"},
        {"Texas Rangers", "Globe Life Park in Arlington", 48114, "Arlington, Texas", "Grass", "American", 1994, "400 feet (122 m)", "Retro Classic", "Open"},
        {"Toronto Blue Jays", "Rogers Centre", 49282, "Toronto, Ontario", "AstroTurf GameDay Grass 3D", "American", 1989, "400 feet (122 m)", "Multipurpose", "Retractable"},
        {"Washington Nationals", "Nationals Park", 41339, "Washington, D.C.", "Grass", "National", 2008, "402 feet (123 m)", "Retro Modern", "Open"}
    };

    db.transaction(); // optional: faster

    for (const TeamEntry& entry : entries) {
        checkQuery.prepare(R"(
            SELECT COUNT(*) FROM teams WHERE team_name = ?
        )");
        checkQuery.addBindValue(entry.teamName);

        if (!checkQuery.exec()) {
            qWarning() << "Check query failed for" << entry.teamName << ":" << checkQuery.lastError().text();
            db.rollback();
            return false;
        }

        if (checkQuery.next() && checkQuery.value(0).toInt() == 0) {
            // Team does not exist, safe to insert
            query.addBindValue(entry.teamName);
            query.addBindValue(entry.stadiumName);
            query.addBindValue(entry.seatingCapacity);
            query.addBindValue(entry.location);
            query.addBindValue(entry.playingSurface);
            query.addBindValue(entry.league);
            query.addBindValue(entry.dateOpened);
            query.addBindValue(entry.distanceToCenterField);
            query.addBindValue(entry.ballparkTypology);
            query.addBindValue(entry.roofType);

            if (!query.exec()) {
                qWarning() << "Insert failed for" << entry.teamName << ":" << query.lastError().text();
                db.rollback();
                return false;
            }
        } else {
            qDebug() << "Team already exists:" << entry.teamName;
        }
    }

    return db.commit();
}


/**
 * @brief Inserts default souvenir items for each team in the 'teams' table.
 * @param db The database connection.
 * @return true if inserts succeed; false if any fail.
 */
bool addDefaultSouvenirs(QSqlDatabase& db) {
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);

    QList<Souvenir> defaultItems = {
        {"Baseball cap", 19.99},
        {"Baseball bat", 89.39},
        {"Team pennant", 17.99},
        {"Autographed baseball", 29.99},
        {"Team jersey", 199.99}
    };

    // Step 1: Query all teams from the teams table
    if (!query.exec("SELECT team_name FROM teams")) {
        qWarning() << "Failed to query teams:" << query.lastError().text();
        return false;
    }

    // Step 2: Insert default souvenirs for each team
    QSqlQuery insertQuery(db);
    insertQuery.prepare("INSERT INTO souvenirs (team_name, item_name, price) VALUES (?, ?, ?)");

    db.transaction(); // Begin transaction for speed and atomicity

    while (query.next()) {
        QString teamName = query.value(0).toString();

        for (const Souvenir& item : defaultItems) {
            insertQuery.bindValue(0, teamName);
            insertQuery.bindValue(1, item.name);
            insertQuery.bindValue(2, item.price);

            if (!insertQuery.exec()) {
                qWarning() << "Insert failed for" << teamName << "/" << item.name << ":" << insertQuery.lastError().text();
                db.rollback();
            //    return false;
            }
        }
    }

    return db.commit(); // Commit if all inserts succeed
}


/**
 * @brief Resets content for key tables (teams, distances, souvenirs), recreating them and repopulating with default data.
 * @param db The database connection.
 * @return true on successful reset; false if any drop/create/insert operation fails.
 */
bool resetContent(QSqlDatabase& db) {
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);

    // Check if table exists
    if (db.tables().contains("teams")) {
        if (!query.exec("DROP TABLE IF EXISTS teams")) {
            qWarning() << "Failed to drop table:" << query.lastError().text();
        } else {
            qDebug() << "Table teams dropped successfully.";
            createTeamsTable(db);
            insertTeamsData(db);
        }
    }

    // Check if table exists
    if (db.tables().contains("stadium_distances")) {
        if (!query.exec("DROP TABLE IF EXISTS stadium_distances")) {
            qWarning() << "Failed to drop table:" << query.lastError().text();
        } else {
            qDebug() << "Table stadium_distances dropped successfully.";
            createStadiumDistancesTable(db);
            insertStadiumDistances(db);
        }
    }

    // Check if table exists
    if (db.tables().contains("souvenirs")) {
        if (!query.exec("DROP TABLE IF EXISTS souvenirs")) {
            qWarning() << "Failed to drop table:" << query.lastError().text();
        } else {
            qDebug() << "Table souvenirs dropped successfully.";
            createSouvenirsTable(db);
            addDefaultSouvenirs(db);
        }
    }

    query.prepare(R"(
    DELETE FROM stadium_location
    WHERE stadium_name = ?;)");
    query.addBindValue("Las Vegas Stadium");

    if (!query.exec()) {
        qWarning() << "Failed to delete stadium:" << query.lastError().text();
    } else {
        qDebug() << "Las Vegas Stadium deleted from stadium_location.";
    }

    return true;
}


/**
 * @brief Resets all content, including the user table, by dropping and recreating database tables.
 * @param db The database connection.
 * @return true if all operations succeed; false otherwise.
 */
bool resetAllContent(QSqlDatabase& db) {
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);

    // Check if table exists
    if (db.tables().contains("user")) {
        if (!query.exec("DROP TABLE IF EXISTS user")) {
            qWarning() << "Failed to drop table:" << query.lastError().text();
        } else {
            qDebug() << "Table user dropped successfully.";
        }
    }

    resetContent(db);

    return true;
}


/**
 * @brief Adds distances from Las Vegas Stadium to a few other stadiums in the 'stadium_distances' table.
 * @param db The database connection.
 * @return true on success; false if a query fails.
 */
bool addStadiumDistances(QSqlDatabase& db) {
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery insertQuery(db);
    QSqlQuery checkQuery(db);

    insertQuery.prepare(R"(
        INSERT INTO stadium_distances (origin, destination, distance)
        VALUES (?, ?, ?)
    )");

    checkQuery.prepare("SELECT COUNT(*) FROM stadium_distances "
                       "WHERE origin = ? AND destination = ? AND distance = ?");


    QList<DistanceEntry> entries = {
        {"Las Vegas Stadium", "Oakland-Alameda County Coliseum", 325},
        {"Las Vegas Stadium", "Dodger Stadium", 300},
        {"Las Vegas Stadium", "Chase Field", 250}
    };

    db.transaction(); // faster batch insert

    for (const DistanceEntry& entry : entries) {
        // Check if this entry already exists
        checkQuery.bindValue(0, entry.origin);
        checkQuery.bindValue(1, entry.destination);
        checkQuery.bindValue(2, entry.distance);

        if (!checkQuery.exec()) {
            qWarning() << "Check failed for" << entry.origin << "->" << entry.destination << ":" << checkQuery.lastError().text();
            db.rollback();
            return false;
        }

        if (checkQuery.next() && checkQuery.value(0).toInt() == 0) {
            // Doesn't exist, insert
            insertQuery.bindValue(0, entry.origin);
            insertQuery.bindValue(1, entry.destination);
            insertQuery.bindValue(2, entry.distance);

            if (!insertQuery.exec()) {
                qWarning() << "Insert failed for" << entry.origin << "->" << entry.destination << ":" << insertQuery.lastError().text();
                db.rollback();
                return false;
            }
        } else {
            qDebug() << "Distance already exists:" << entry.origin << "->" << entry.destination;
        }

    }

    return db.commit();
}


/**
 * @brief Inserts default (x, y) coordinates for each known stadium into 'stadium_location'.
 * @param db The database connection.
 * @return true on successful insert; false if a query fails.
 */
bool insertStadiumLocationData(QSqlDatabase& db) {
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);

    query.prepare(R"(
        INSERT INTO stadium_location (stadium_name, x_loc, y_loc)
        VALUES (?, ?, ?);
    )");

    const QList<std::tuple<QString, int, int>> stadiumCoordinates = {
        {"Chase Field", 222, 368},
        {"SunTrust Park", 841, 369},
        {"Oriole Park at Camden Yards", 971, 232},
        {"Fenway Park", 1078, 146},
        {"Wrigley Field", 701, 207},
        {"Guaranteed Rate Field", 745, 230},
        {"Great American Ball Park", 836, 255},
        {"Progressive Field", 847, 207},
        {"Coors Field", 398, 241},
        {"Comerica Park", 794, 187},
        {"Minute Maid Park", 607, 452},
        {"Kauffman Stadium", 610, 268},
        {"Angel Stadium", 69, 318},
        {"Dodger Stadium", 31, 288},
        {"Marlins Park", 961, 520},
        {"Miller Park", 722, 164},
        {"Target Field", 605, 125},
        {"Citi Field", 1047, 183},
        {"Yankee Stadium", 1007, 161},
        {"Oakland-Alameda County Coliseum", 19, 237},
        {"Citizens Bank Park", 992, 200},
        {"PNC Park", 908, 204},
        {"Petco Park", 96, 354},
        {"Oracle Park", 1, 206},
        {"Safeco Field", 70, 49},
        {"Busch Stadium", 693, 277},
        {"Tropicana Field", 910, 490},
        {"Globe Life Park in Arlington", 547, 394},
        {"Rogers Centre", 888, 103},
        {"Nationals Park", 954, 272}
    };

    for (const auto& [name, x, y] : stadiumCoordinates) {
        query.addBindValue(name);
        query.addBindValue(x);
        query.addBindValue(y);

        if (!query.exec()) {
            qWarning() << "Failed to insert into 'stadium_location':" << query.lastError().text();
            return false;
        }
    }

    qDebug() << "'stadium_location' data inserted successfully!";
    return true;
}


/**
 * @brief Adds the Las Vegas Stadium to the 'stadium_location' table with specific coordinates.
 * @param db The database connection.
 * @return true if insert succeeds; false on error.
 */
bool addStadiumLocationData(QSqlDatabase& db) {
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);

    query.prepare(R"(
        INSERT INTO stadium_location (stadium_name, x_loc, y_loc)
        VALUES (?, ?, ?);
    )");

    QStringList stadiums = {
        "Las Vegas Stadium"
    };

    for (const QString& stadium : stadiums) {
        query.addBindValue(stadium);
        query.addBindValue(138);  // default x_loc
        query.addBindValue(232);  // default y_loc

        if (!query.exec()) {
            qWarning() << "Failed to insert into 'stadium_location':" << query.lastError().text();
            return false;
        }
    }

    qDebug() << "'stadium_location' data inserted successfully!";
    return true;
}


/**
 * @brief Adds the Las Vegas Gamblers team entry to the 'teams' table.
 * @param db The database connection.
 * @return true if insert is successful; false on error or duplicate.
 */
bool addTeamsData(QSqlDatabase& db) {
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    QSqlQuery checkQuery(db);  // Separate query for checking existence

    query.prepare(R"(
        INSERT INTO teams (team_name, stadium_name, seating_capacity, location, playing_surface,
                           league, date_opened, distance_to_center_field, ballpark_typology, roof_type)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);
    )");

    QList<TeamEntry> entries = {
        {"Las Vegas Gamblers", "Las Vegas Stadium", 44444, "Las Vegas, Nevada", "Grass", "National", 2022, "400 feet (122 m)", "Retro Modern", "Open"}
    };

    db.transaction(); // optional: faster

    for (const TeamEntry& entry : entries) {
        checkQuery.prepare(R"(
            SELECT COUNT(*) FROM teams WHERE team_name = ?
        )");
        checkQuery.addBindValue(entry.teamName);

        if (!checkQuery.exec()) {
            qWarning() << "Check query failed for" << entry.teamName << ":" << checkQuery.lastError().text();
            db.rollback();
            return false;
        }

        if (checkQuery.next() && checkQuery.value(0).toInt() == 0) {
            // Team does not exist, safe to insert
            query.addBindValue(entry.teamName);
            query.addBindValue(entry.stadiumName);
            query.addBindValue(entry.seatingCapacity);
            query.addBindValue(entry.location);
            query.addBindValue(entry.playingSurface);
            query.addBindValue(entry.league);
            query.addBindValue(entry.dateOpened);
            query.addBindValue(entry.distanceToCenterField);
            query.addBindValue(entry.ballparkTypology);
            query.addBindValue(entry.roofType);

            if (!query.exec()) {
                qWarning() << "Insert failed for" << entry.teamName << ":" << query.lastError().text();
                db.rollback();
                return false;
            }
        } else {
            qDebug() << "Team already exists:" << entry.teamName;
        }
    }

    return db.commit();
}


/**
 * @brief Bulk inserts the Las Vegas team, distances, souvenir data, and location.
 * @param db The database connection.
 * @return true if all operations succeed; false otherwise.
 */
bool addBulkData(QSqlDatabase& db) {
    addTeamsData(db);
    addStadiumDistances(db);
    addDefaultSouvenirs(db);
    addStadiumLocationData(db);
    return true;
}

// db::db() {}
