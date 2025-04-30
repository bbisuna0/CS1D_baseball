#include "displayteams.h"
#include "ui_displayteams.h"
#include "utility.h"

DisplayTeams::DisplayTeams(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DisplayTeams)
{
    /*
    Column 0 : "team_name"
    Column 1 : "stadium_name"
    Column 2 : "seating_capacity"
    Column 3 : "location"
    Column 4 : "playing_surface"
    Column 5 : "league"
    Column 6 : "date_opened"
    Column 7 : "distance_to_center_field"
    Column 8 : "ballpark_typology"
    Column 9 : "roof_type"
     */
    ui->setupUi(this);

    team_data = new QSqlTableModel(this);
    team_data->setTable("teams");

    team_data->setHeaderData(0, Qt::Horizontal, "Team Name");
    team_data->setHeaderData(1, Qt::Horizontal, "Stadium");
    team_data->setHeaderData(2, Qt::Horizontal, "Seating Capacity");
    team_data->setHeaderData(3, Qt::Horizontal, "Location");
    team_data->setHeaderData(4, Qt::Horizontal, "Playing Surface");
    team_data->setHeaderData(5, Qt::Horizontal, "League");
    team_data->setHeaderData(6, Qt::Horizontal, "Date Opened");
    team_data->setHeaderData(7, Qt::Horizontal, "Center Field Distance");
    team_data->setHeaderData(8, Qt::Horizontal, "Typology");
    team_data->setHeaderData(9, Qt::Horizontal, "Roof Type");

    ui->pb_mlbteam->click();
}

DisplayTeams::~DisplayTeams()
{
    delete ui;
    delete team_data;
}

void DisplayTeams::on_pb_mlbteam_clicked()
{
    team_data->setSort(team_data->fieldIndex("team_name"), Qt::AscendingOrder);
    team_data->setFilter("");
    team_data->select();

    // This works
    // QSqlDatabase db = QSqlDatabase::database();
    // TeamLogoModel *logoModel = new TeamLogoModel(this);
    // logoModel->setTable("teams");
    // ui->tableView->setModel(logoModel);

    TeamLogoDelegate *logoDelegate = new TeamLogoDelegate(ui->tableView);
    ui->tableView->setItemDelegateForColumn(team_data->fieldIndex("team_name"), logoDelegate);

    ui->tableView->verticalHeader()->setDefaultSectionSize(42);

    ui->tableView->setModel(team_data);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setColumnHidden(team_data->fieldIndex("team_name"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("stadium_name"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("seating_capacity"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("location"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("playing_surface"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("league"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("date_opened"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("distance_to_center_field"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("ballpark_typology"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("roof_type"), false);
    ui->tableView->resizeColumnsToContents();

    ui->tableView->setColumnWidth(0, 170); // Logo column
}


void DisplayTeams::on_pb_exit_clicked()
{
    this->close();
}


void DisplayTeams::on_pb_american_clicked()
{
    team_data->setSort(team_data->fieldIndex("team_name"), Qt::AscendingOrder);
    team_data->setFilter("league='American'");
    team_data->select();

    TeamLogoDelegate *logoDelegate = new TeamLogoDelegate(ui->tableView);
    ui->tableView->setItemDelegateForColumn(team_data->fieldIndex("team_name"), logoDelegate);
    ui->tableView->verticalHeader()->setDefaultSectionSize(42);

    ui->tableView->setModel(team_data);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setColumnHidden(team_data->fieldIndex("team_name"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("stadium_name"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("seating_capacity"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("location"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("playing_surface"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("league"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("date_opened"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("distance_to_center_field"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("ballpark_typology"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("roof_type"), false);
    ui->tableView->resizeColumnsToContents();

    ui->tableView->setColumnWidth(0, 170); // Logo column
}


void DisplayTeams::on_pb_national_clicked()
{
    team_data->setSort(team_data->fieldIndex("stadium_name"), Qt::AscendingOrder);
    team_data->setFilter("league='National'");
    team_data->select();

    TeamLogoDelegate *logoDelegate = new TeamLogoDelegate(ui->tableView);
    ui->tableView->setItemDelegateForColumn(team_data->fieldIndex("team_name"), logoDelegate);
    ui->tableView->verticalHeader()->setDefaultSectionSize(42);

    ui->tableView->setModel(team_data);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setColumnHidden(team_data->fieldIndex("team_name"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("stadium_name"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("seating_capacity"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("location"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("playing_surface"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("league"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("date_opened"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("distance_to_center_field"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("ballpark_typology"), false);
    ui->tableView->setColumnHidden(team_data->fieldIndex("roof_type"), false);
    ui->tableView->resizeColumnsToContents();

    ui->tableView->setColumnWidth(0, 170); // Logo column
}

