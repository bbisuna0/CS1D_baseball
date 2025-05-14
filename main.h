#ifndef MAIN_H
#define MAIN_H

#include <QString>
#include <QSqlDatabase>
#include <QDebug>
#include <QFile>
#include "utility.h"
#include "db.h"

/**
 * @class User
 * @brief Represents a user in the system.
 *
 * This class encapsulates login credentials and session metadata such as
 * administrative privileges and login status.
 */
class User {
public:
    QString uname;  /**< Username associated with the account. */
    bool admin;     /**< Whether the user has administrative privileges. */
    bool login_ok;  /**< Whether the user has successfully logged in. */
    QString uid;    /**< Unique identifier for the user (optional). */
};

/**
 * @var myUser
 * @brief Global instance representing the current logged-in user.
 */
extern User myUser;

/**
 * @var db
 * @brief Global QSqlDatabase connection used by the application.
 */
extern QSqlDatabase db;

/**
 * @var DBNAME
 * @brief Name of the SQLite database file used in the application.
 */
const QString DBNAME = "baseball.db";

#endif // MAIN_H
