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


void LoginWindow::on_pushButton_3_clicked()
{
    display_items = new display_souvenirs(this);
    display_items->show();

    // Get the text of the currently selected item in the combo box
    QString selectedTeam = ui->comboBox->currentText();
    std::string teamStr = selectedTeam.toStdString();

    for (Stadium* stadium : Stadium::object_list) {
        if (stadium->getTeamName() == teamStr) {
            const std::map<std::string, double>& souvenirs = stadium->getSouvenirs();

            for (const auto& [name, price] : souvenirs) {
                display_items->appendSouvenirText(
                    QString::fromStdString(name + ": $" + std::to_string(price))
                    );
            }

            break;
        }
    }
}


