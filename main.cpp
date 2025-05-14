/**
 * @file main.cpp
 * @brief Entry point for the Baseball Stadium Management application.
 *
 * Initializes the Qt application, database connection, required tables, and launches
 * the login window. If login is successful, the main menu is shown.
 */

#include "loginwindow.h"
#include "main.h"
#include "mainmenu.h"
#include "utility.h"
#include <QApplication>

/**
 * @var themeStyle
 * @brief Global stylesheet used to style the entire application UI.
 */
QString themeStyle = R"(
    QWidget {
        //background-color: #f0f0f0;
        //color: #333333;
        font-family: Segoe UI, sans-serif;
        font-size: 10pt;
    }

    // QMainWindow {
    //     background-color: #e8e8e8;
    // }

    // QPushButton {
    //     background-color: #4a90e2;
    //     color: white;
    //     border: 1px solid #357ab7;
    //     border-radius: 4px;
    //     padding: 4px 8px;
    // }

    // QPushButton:hover {
    //     background-color: #357ab7;
    // }

    // QPushButton:disabled {
    //     background-color: #cccccc;
    //     color: #666666;
    //     border: 1px solid #aaaaaa;
    // }

    QLineEdit, QComboBox, QSpinBox {
        background-color: white;
        border: 1px solid #cccccc;
        border-radius: 3px;
        padding: 2px;
    }

    // QLineEdit:read-only,
    // QComboBox[readonlyMode="true"],
    // QSpinBox[readonlyMode="true"] {
    //     // background-color: #f0f0f0;
    //     // color: #777;
    // background-color: #f5f5f5;
    // color: #666;
    // border: 1px solid #ccc;
    // padding-left: 20px; /* room for icon */
    // background-image: url(:/logos/delete.png);  /* must be in your resources */
    // background-repeat: no-repeat;
    // background-position: left center;
    // }

    QTableView {
        background-color: white;
        alternate-background-color: #f9f9f9;
        gridline-color: #dddddd;
    }

    QHeaderView::section {
        background-color: #d0d0d0;
        padding: 4px;
        border: 1px solid #bbbbbb;
    }
)";


/**
 * @var myUser
 * @brief Global instance of User that tracks login status and credentials.
 */
User myUser;


/**
 * @var db
 * @brief Global QSqlDatabase connection used throughout the application.
 */
QSqlDatabase db;


/**
 * @brief Main entry point for the Baseball Stadium Management application.
 *
 * - Loads the application stylesheet.
 * - Opens or creates the SQLite database and essential tables.
 * - Launches the login window.
 * - If login is successful, launches the main menu window.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return Exit code of the application.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyleSheet(themeStyle);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DBNAME);

    if(!db.open())
    {
        qDebug() << "Error opening user database";
    }

    bool existingDB = QFile::exists(DBNAME);

    if (!existingDB)
    {
        qDebug() << "Error: The Database Does not Exist!";
    }

    if (!(checkUserTable()))
    {
        qDebug() << "User table not found!\nCreating user table.\n";
        createUserTable();
    }

    bool create = false;
    create = createStadiumDistancesTable(db);
    if (create)
        insertStadiumDistances(db);

    create = false;
    create = createTeamsTable(db);
    if (create)
        insertTeamsData(db);

    create = false;
    create = createSouvenirsTable(db);
    if (create)
        addDefaultSouvenirs(db);

    if (!(checkStadiumLocationTable()))
    {
        qDebug() << "Stadium Location table not found!\nCreating Stadium Location table.\n";
        create = createStadiumLocationTable(db);
    }
    if (create)
        insertStadiumLocationData(db);

    a.setWindowIcon(QIcon(":/logos/baseball.ico")); // From qrc
    LoginWindow w;
    w.setWindowModality(Qt::ApplicationModal);
    w.show();
    int result = a.exec();
    if (!myUser.login_ok)
    {
        a.quit();
        QString connectionName = db.connectionName();
        db.close();
        //QSqlDatabase::removeDatabase(connectionName);
        return 0;
    }

    mainmenu *mainWin = new mainmenu();
    mainWin->show();
    mainWin->setWindowModality(Qt::ApplicationModal);
    result = a.exec();
    QString connectionName = db.connectionName();
    db.close();
    //QSqlDatabase::removeDatabase(connectionName);
    exit(result);
    return 0;
}
