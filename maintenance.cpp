/**
 * @file maintenance.cpp
 * @brief Implements the maintenance window for administrative database operations.
 *
 * Provides UI access to reset content, perform bulk inserts, and launch map visualization.
 */
#include "maintenance.h"
#include "ui_maintenance.h"
#include "db.h"
#include "mapdisp.h"
#include "ui_mapdisp.h"


/**
 * @class maintenance
 * @brief UI widget for performing administrative functions such as resetting and populating data.
 *
 * Accessible only to admin users, this window supports resetting database tables,
 * performing bulk data updates, and visualizing stadium maps.
 */

/**
 * @brief Constructs the maintenance window and sets up the UI.
 * @param parent Optional parent widget.
 */
maintenance::maintenance(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::maintenance)
{
    ui->setupUi(this);
}


/**
 * @brief Destructor for maintenance. Cleans up UI resources.
 */
maintenance::~maintenance()
{
    delete ui;
}


/**
 * @brief Closes the maintenance window.
 */
void maintenance::on_pb_exit_clicked()
{
    close();
}


/**
 * @brief Resets content for core tables (teams, distances, souvenirs) to default state.
 */
void maintenance::on_pb_content_default_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    resetContent(db);
}


/**
 * @brief Displays stadium distance data.
 * @note This function is currently a placeholder and not implemented.
 */
void maintenance::on_pb_display_distances_clicked()
{

}


/**
 * @brief Performs a bulk insert of team, stadium, souvenir, and distance data.
 */
void maintenance::on_pb_bulk_update_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    addBulkData(db);
}


/**
 * @brief Opens a dialog to upload team or stadium images.
 * @note This function is currently a placeholder and not implemented.
 */
void maintenance::on_pb_upload_image_clicked()
{

}


/**
 * @brief Fully resets all database content including user data.
 */
void maintenance::on_pb_full_reset_clicked()
{
    QSqlDatabase db = QSqlDatabase::database();
    resetAllContent(db);
}


/**
 * @brief Opens a map display window for stadium visualization.
 */
void maintenance::on_pb_res1_clicked()
{
    mapdisp *mapWin = new mapdisp();
    mapWin->show();
}

