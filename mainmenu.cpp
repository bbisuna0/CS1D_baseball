/**
 * @file mainmenu.cpp
 * @brief Implements the main menu for the Baseball Stadium Management System.
 *
 * Provides access to various features including team details, reports,
 * trip planning, and maintenance (admin-only).
 */

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


/**
 * @class mainmenu
 * @brief The main menu window that provides navigation to different parts of the application.
 *
 * This class creates buttons for team details, vacation planning, reports, and maintenance.
 * The maintenance option is enabled only for admin users.
 */

/**
 * @brief Constructs the mainmenu window and initializes the UI.
 * @param parent Pointer to the parent widget.
 */
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


/**
 * @brief Destructor for mainmenu. Cleans up UI resources.
 */
mainmenu::~mainmenu()
{
    delete ui;
}


/**
 * @brief Closes the main menu when the Exit button is clicked.
 */
void mainmenu::on_pb_exit_clicked()
{
    close();
}


/**
 * @brief Opens the Team Details window.
 */
void mainmenu::on_pb_team_details_clicked()
{
    teamdisplay *teamWin = new teamdisplay();
    teamWin->show();
}


/**
 * @brief Opens the Vacation Planning window.
 */
void mainmenu::on_pb_plan_vacation_clicked()
{
    plantour *tourWin = new plantour();
    tourWin->show();
}


/**
 * @brief Opens the Team Report window.
 */
void mainmenu::on_pb_team_report_clicked()
{
    DisplayTeams *teamWin = new DisplayTeams();
    teamWin->show();
}


/**
 * @brief Opens the Stadium Report window.
 */
void mainmenu::on_pb_stadium_report_clicked()
{
    DisplayStadiums *stadiumWin = new DisplayStadiums();
    stadiumWin->show();
}


/**
 * @brief Opens the Maintenance window (admin only).
 */
void mainmenu::on_pb_maintenance_clicked()
{
    maintenance *maintWin = new maintenance();
    maintWin->show();
}

