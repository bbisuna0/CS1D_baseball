#include "loginwindow.h"
#include "./ui_loginwindow.h"
#include "utility.h"
#include "reguser.h"

extern User myUser;

int login_count = 0;

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_exit_clicked()
{
    close();
}


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


void LoginWindow::on_lineEdit_password_returnPressed()
{
    ui->pushButton_login->click();
}


void LoginWindow::on_pushButton_register_clicked()
{
    reguser r;
    r.setModal(true);
    r.setWindowFlags(r.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    r.exec();
}

