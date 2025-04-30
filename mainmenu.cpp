#include "mainmenu.h"
#include "plantour.h"
#include "displaystadiums.h"
#include "displayteams.h"
#include "ui_mainmenu.h"
#include "ui_plantour.h"
#include "ui_displayteams.h"
#include "ui_displaystadiums.h"
#include "teamdisplay.h"
#include "maintenance.h"
#include "ui_maintenance.h"

mainmenu::mainmenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainmenu)
{
    ui->setupUi(this);
    if (!myUser.admin)
    {
        ui->pb_maintenance->setEnabled(false);
    }
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


void mainmenu::on_pb_plan_vacation_clicked()
{
    plantour *tourWin = new plantour();
    tourWin->show();
}


void mainmenu::on_pb_team_report_clicked()
{
    DisplayTeams *teamWin = new DisplayTeams();
    teamWin->show();
}


void mainmenu::on_pb_stadium_report_clicked()
{
    DisplayStadiums *stadiumWin = new DisplayStadiums();
    stadiumWin->show();
}


void mainmenu::on_pb_maintenance_clicked()
{
    maintenance *maintWin = new maintenance();
    maintWin->show();
}

