#include "utility.h"
#include <QMessageBox>

bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("personnel.dat");
    if (!db.open()) {
        QMessageBox::warning(0, QObject::tr("Database Error"),
                             db.lastError().text());
        return false;
    }
    return true;
}

void createUserTable() // QSqlDatabase &db
{
    /*
    QString create = "CREATE TABLE if not exists users ("
                     "ID integer,"
                     "username VARCHAR(20),"
                     "password VARCHAR(20));";
    */

    QString create = "CREATE TABLE user ("
                     "uid	INTEGER UNIQUE,"
                     "uname	TEXT,"
                     "pass	TEXT,"
                     "admin	INTEGER DEFAULT 0 CHECK(admin >= 0 AND admin <= 1),"
                     "PRIMARY KEY(uid AUTOINCREMENT))";

    QSqlQuery query;
    if(!query.exec(create))
    {
        qDebug() << "Error creating table";
    }
    return;
}

bool checkUserTable() // check if user table exists
{
    QString checkUser;
    checkUser = "SELECT name FROM sqlite_master where type='table' AND name='user';";
    QSqlQuery query;
    query.prepare(checkUser);
    if (query.exec()) // found
    {
        return query.next(); // return true if user table found, false if not
    }
    else // error check for table
    {
        qDebug() << query.lastError().text() << Qt::endl;
        return false;
    }
}

void addUser(int ID, QString username, QString password, bool admin) // add user data into database
{
    QString addUser = "INSERT INTO user ("
                      "uid, uname, pass, admin)"
                      "VALUES (NULL, :uname , :pass, :admin);";
    QSqlQuery query;
    query.prepare(addUser);
    qDebug() << "created " << ID;
    //query.bindValue(":id", ID);  // auto-increment
    query.bindValue(":uname", username);
    query.bindValue(":pass", password);
    if (admin)
        query.bindValue(":admin", 1);
    else
        query.bindValue(":admin", 0);
    //qDebug() << query.boundValue(":pass");
    if(!query.exec())
    {
        qDebug() << query.lastError().text() << Qt::endl;
        qDebug() << "Error adding " << username << " to users";
    }
    return;
}

//bool checkPassword(QString uname, QString pass, bool &admin, QString &uid) // check if user table exists
bool checkPassword(QString uname, QString pass, bool &admin) // check if user table exists
{
    QString checkPassword;
    checkPassword = "SELECT * FROM user where uname=:uname AND pass=:pass;";
    QSqlQuery query;
    query.prepare(checkPassword);
    query.bindValue(":uname", uname);
    query.bindValue(":pass", pass);
    admin = true;
    if (query.exec()) // found
    {
        if (query.next()) {
            //uid = query.value(0).toString();
            int i = query.value(3).toInt();
            if (i==1)
                admin = true;
            else
                admin = false;
            return true;
        }
        else
            return false;
    }
    else // error check for table
    {
        qDebug() << query.lastError().text() << Qt::endl;
        return false;
    }
}

bool tableExists(QSqlDatabase& db, const QString& tableName) {
    return db.tables().contains(tableName);
}

// /**
//  * @brief Trims leading and trailing spaces from a string while preserving spaces inside quotes.
//  * @param str The input string.
//  * @return The trimmed string.
//  */
// // Function to trim leading and trailing spaces from a string, preserving spaces inside quotes
// std::string trim(const std::string& str) {
//     size_t first = str.find_first_not_of(' ');
//     if (std::string::npos == first) {
//         return "";
//     }
//     size_t last = str.find_last_not_of(' ');
//     return str.substr(first, (last - first + 1));
// }

// /**
//  * @brief Finds the closest college to a given college that has not been visited.
//  * @param currentCollege The name of the current college.
//  * @param data The list of college data.
//  * @param visitedCampuses The set of already visited campuses.
//  * @param nextIndex Reference to store the index of the next closest college.
//  * @return The distance to the next closest college.
//  */
// float findClosestCollege(const std::string& currentCollege, std::vector<CollegeData>& data, std::unordered_set<std::string>& visitedCampuses, int& nextIndex) {
//     float minDistance = std::numeric_limits<float>::max();
//     nextIndex = -1;

//     for (size_t i = 0; i < data.size(); ++i) {
//         if (visitedCampuses.find(data[i].collegeEnd) == visitedCampuses.end() &&
//             data[i].collegeStart == currentCollege && data[i].distance < minDistance) {
//             minDistance = data[i].distance;
//             nextIndex = i;
//         }
//     }
//     return minDistance;
// }


// /**
//  * @brief Plans the most efficient route visiting a specific number of colleges.
//  * @param startCollege The starting college.
//  * @param data The list of college data.
//  * @param stops The number of stops to make.
//  * @param totalDistance Reference to store the total distance traveled.
//  * @return A vector containing the planned route.
//  */
// std::vector<CollegeData> planEfficientRoute(const std::string startCollege, std::vector<CollegeData> data, int stops, float& totalDistance) {
//     std::vector<CollegeData> route;
//     std::unordered_set<std::string> visitedCampuses;
//     std::string currentCollege = startCollege;
//     totalDistance = 0.0;

//     for (int i = 0; i < stops; ++i) {
//         int nextIndex;
//         float distance = findClosestCollege(currentCollege, data, visitedCampuses, nextIndex);

//         if (nextIndex == -1) break; // No more valid colleges to visit

//         visitedCampuses.insert(currentCollege); // Mark the current college as visited
//         route.push_back(data[nextIndex]);
//         totalDistance += distance;
//         currentCollege = data[nextIndex].collegeEnd;
//     }

//     return route;
// }


// /**
//  * @brief Plans the shortest trip visiting a specific number of colleges.
//  * @param startCollege The starting college.
//  * @param data The list of college data.
//  * @param numStops The number of stops to make.
//  * @param totalDistance Reference to store the total distance traveled.
//  * @return A vector containing the planned route.
//  */
// std::vector<CollegeData> planShortestTrip(const std::string& startCollege, std::vector<CollegeData> data, int numStops, float& totalDistance) {
//     std::vector<CollegeData> route;
//     std::unordered_set<std::string> visitedCampuses;
//     std::string currentCollege = startCollege;
//     totalDistance = 0.0;

//     for (int i = 0; i < numStops; ++i) {
//         int nextIndex;
//         float distance = findClosestCollege(currentCollege, data, visitedCampuses, nextIndex);

//         if (nextIndex == -1) break; // No more valid colleges to visit

//         visitedCampuses.insert(currentCollege); // Mark the current college as visited
//         route.push_back(data[nextIndex]);
//         totalDistance += distance;
//         currentCollege = data[nextIndex].collegeEnd;
//     }

//     return route;
// }

// /**
//  * @brief Plans an efficient trip visiting a specified list of colleges.
//  * @param collegesToVisit The list of colleges to visit.
//  * @param data The list of college data.
//  * @param totalDistance Reference to store the total distance traveled.
//  * @return A vector containing the planned route.
//  */
// std::vector<CollegeData> planEfficientTrip(const QStringList& collegesToVisit, std::vector<CollegeData> data, float& totalDistance) {
//     std::vector<CollegeData> route;
//     std::unordered_set<std::string> visitedCampuses;
//     totalDistance = 0.0;

//     if (collegesToVisit.isEmpty()) {
//         return route; // Return empty route if no colleges are provided
//     }

//     std::string currentCollege = collegesToVisit.first().toStdString();
//     visitedCampuses.insert(currentCollege);

//     std::unordered_set<std::string> remainingColleges;
//     for (int i = 1; i < collegesToVisit.size(); ++i) {
//         remainingColleges.insert(collegesToVisit[i].toStdString());
//     }

//     while (!remainingColleges.empty()) {
//         int nextIndex;
//         float distance = findClosestCollege2(currentCollege, data, visitedCampuses, nextIndex, remainingColleges);

//         if (nextIndex == -1) {
//             // No valid next college found from the current college
//             // Find the closest remaining college from all visited colleges
//             int bestNextIndex = -1;
//             float bestDistance = std::numeric_limits<float>::max();
//             std::string bestStartCollege;

//             for (const auto& visited : visitedCampuses) {
//                 int tempNextIndex;
//                 float tempDistance = findClosestCollege2(visited, data, visitedCampuses, tempNextIndex, remainingColleges);
//                 if (tempNextIndex != -1 && tempDistance < bestDistance) {
//                     bestDistance = tempDistance;
//                     bestNextIndex = tempNextIndex;
//                     bestStartCollege = visited;
//                 }
//             }

//             if (bestNextIndex == -1) {
//                 break; // No path to remaining colleges
//             }
//             nextIndex = bestNextIndex;
//             distance = bestDistance;
//             currentCollege = bestStartCollege;

//         }

//         route.push_back(data[nextIndex]);
//         totalDistance += distance;
//         currentCollege = data[nextIndex].collegeEnd;
//         visitedCampuses.insert(currentCollege);
//         remainingColleges.erase(currentCollege);
//     }

//     return route;
// }


// /**
//  * @brief Checks if a given college name is present in the model.
//  * @param model The QStandardItemModel containing the college data.
//  * @param searchValue The college name to search for.
//  * @return True if the college is found, otherwise false.
//  */
// bool isCollegeMatch(QStandardItemModel* model, const QString& searchValue) {
//     if (!model) return false;

//     for (int row = 0; row < model->rowCount(); ++row) {
//         QStandardItem* startItem = model->item(row, 0); // Column 0: collegeStart
//         QStandardItem* endItem = model->item(row, 1);   // Column 1: collegeEnd

//         if (startItem && startItem->text() == searchValue) {
//             return true; // Match found
//         } else if (endItem && endItem->text() == searchValue) {
//             return true; // Match found
//         }
//     }
//     return false; // No match found
// }


// /**
//  * @brief Displays a message box indicating a file was successfully loaded.
//  * @param parent The parent QWidget.
//  * @param filename The name of the loaded file.
//  */
// void showFileLoadedMessage(QWidget* parent, const QString filename) {
//     QString message = QString("File '%1' successfully loaded.").arg(filename);
//     QMessageBox::information(parent, "File Loaded", message);
// }


// /**
//  * @brief Displays a message box indicating a file was successfully saved.
//  * @param parent The parent QWidget.
//  * @param filename The name of the saved file.
//  */
// void showFileSavedMessage(QWidget* parent, const QString filename) {
//     QString message = QString("File '%1' successfully Saved.").arg(filename);
//     QMessageBox::information(parent, "File Saved", message);
// }



//utility::utility() {}
