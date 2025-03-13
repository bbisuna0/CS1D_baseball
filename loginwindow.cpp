#include "loginwindow.h"
#include "./ui_loginwindow.h"
#include "mainmenu.h"

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
    mainmenu *mainWin = new mainmenu();
    mainWin->show();
    close();
}

