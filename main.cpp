#include "loginwindow.h"
#include "main.h"
#include "mainmenu.h"
#include "utility.h"

#include <QApplication>

User myUser;
QSqlDatabase db;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
