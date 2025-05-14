#include "loginwindow.h"
#include "./ui_loginwindow.h"
#include "utility.h"
#include "reguser.h"

extern User myUser;

int login_count = 0;


/**
 * @class LoginWindow
 * @brief Main login window that handles user authentication and access control.
 */
LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}


/**
 * @brief Destructor for LoginWindow. Cleans up the UI.
 */
LoginWindow::~LoginWindow()
{
    delete ui;
}


/**
 * @brief Closes the login window when the exit button is clicked.
 */
void LoginWindow::on_pushButton_exit_clicked()
{
    close();
}


/**
 * @brief Handles user login logic when the login button is clicked.
 *
 * Validates the entered username and password. If valid, sets login status in the
 * global `myUser` object and closes the window. If failed more than three times,
 * shows a warning and exits.
 */
void LoginWindow::on_pushButton_login_clicked()
{
    QString uname = ui->lineEdit_username->text();
    QString pass = ui->lineEdit_password->text();
    //extern QString curr_uname;
    //extern bool curr_admin;
    bool login_ok = checkPassword(uname, pass, myUser.admin);
    login_count++;
    if (login_ok)
    {
        myUser.uname = uname;
        myUser.login_ok = true;
        this->close();
    }
    else
    {
        myUser.login_ok = false;
        myUser.admin = false;
        if (login_count > 2)
        {
            QMessageBox::warning(0, QObject::tr("Too many invalid login attempt"),
                                 "Too many invalid login attempts.");
            this->close();
        }
    }
}


/**
 * @brief Simulates login button click when the Return key is pressed in the password field.
 */
void LoginWindow::on_lineEdit_password_returnPressed()
{
    ui->pushButton_login->click();
}


/**
 * @brief Opens the registration dialog when the Register button is clicked.
 */
void LoginWindow::on_pushButton_register_clicked()
{
    reguser r;
    r.setModal(true);
    r.setWindowFlags(r.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    r.exec();
}

