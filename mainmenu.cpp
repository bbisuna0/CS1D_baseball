#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "teamdisplay.h"

mainmenu::mainmenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainmenu)
{
    ui->setupUi(this);
}

mainmenu::~mainmenu()
{
    delete ui;
}

void mainmenu::on_pb_exit_clicked()
{
    close();
}


void mainmenu::on_pb_team_details_clicked()
{
    teamdisplay *teamWin = new teamdisplay();
    teamWin->show();
}

