#include "plantour.h"
#include "ui_plantour.h"
#include "teamdisplay.h"
#include "utility.h"

plantour::plantour(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::plantour)
{
    ui->setupUi(this);
}

plantour::~plantour()
{
    delete ui;
}

void plantour::on_pb_exit_clicked()
{
    close();
}


void plantour::on_pb_team_details_clicked()
{
    teamdisplay *teamWin = new teamdisplay();
    teamWin->show();
}


void plantour::on_pb_team_report_clicked()
{
    StadiumSelectionDialog *stadiumDialog = new StadiumSelectionDialog();
    stadiumDialog->show();
}

