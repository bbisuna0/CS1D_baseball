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



//utility::utility() {}
