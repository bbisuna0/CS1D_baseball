#include "displaystadiums.h"
#include "ui_displaystadiums.h"
#include <QSqlRecord>
#include "utility.h"

DisplayStadiums::DisplayStadiums(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DisplayStadiums)
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

    ui->pb_stadium->click();
}

DisplayStadiums::~DisplayStadiums()
{
    delete ui;
}

void DisplayStadiums::on_pb_exit_clicked()
{
    this->close();
}


void DisplayStadiums::on_pb_stadium_clicked()
{
    // QVariant header = team_data->headerData(1,Qt::Horizontal, Qt::DisplayRole);
    // qDebug() << header.toString();
    // qDebug() << team_data->fieldIndex("Stadium");
    // qDebug() << team_data->fieldIndex(0);
    // qDebug() << team_data->fieldIndex("stadiumName");
    // for (int i = 0; i < team_data->columnCount(); ++i) {
    //     QString fieldName = team_data->record().fieldName(i);
    //     qDebug() << "Column" << i << ":" << fieldName;
    // }
    team_data->setSort(team_data->fieldIndex("stadium_name"), Qt::AscendingOrder);
    team_data->setFilter("");
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


void DisplayStadiums::on_pb_typology_clicked()
{
    team_data->setSort(team_data->fieldIndex("ballpark_typology"), Qt::AscendingOrder);
    team_data->setFilter("");
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


void DisplayStadiums::on_pb_openroof_clicked()
{
    team_data->setSort(team_data->fieldIndex("team_name"), Qt::AscendingOrder);
    team_data->setFilter("roof_type='Open'");
    team_data->select();
    int row = team_data->rowCount();
    team_data->insertRow(row);
    team_data->setData(team_data->index(row,0),"");
    team_data->setData(team_data->index(row,1),"");
    team_data->setData(team_data->index(row,2),"");
    team_data->setData(team_data->index(row,3),"");
    team_data->setData(team_data->index(row,4),"");
    team_data->setData(team_data->index(row,5),"");
    team_data->setData(team_data->index(row,6),"");
    team_data->setData(team_data->index(row,7),"");
    team_data->setData(team_data->index(row,8),"Count:");
    team_data->setData(team_data->index(row,9),row);

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

    //team_data->revertAll();
}


void DisplayStadiums::on_pb_chronological_clicked()
{
    team_data->setSort(team_data->fieldIndex("date_opened"), Qt::AscendingOrder);
    team_data->setFilter("");
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


void DisplayStadiums::on_pb_seating_clicked()
{
    team_data->setSort(team_data->fieldIndex("seating_capacity"), Qt::AscendingOrder);
    team_data->setFilter("");
    team_data->select();

    int total = 0;
    int col = team_data->fieldIndex("seating_capacity");

    for (int row = 0; row < team_data->rowCount(); ++row) {
        QVariant value = team_data->data(team_data->index(row, col));
        total += value.toInt();  // or .toDouble() for decimals
    }

    int row = team_data->rowCount();
    team_data->insertRow(row);
    team_data->setData(team_data->index(row,0),"");
    team_data->setData(team_data->index(row,1),"");
    team_data->setData(team_data->index(row,2),"");
    team_data->setData(team_data->index(row,3),"");
    team_data->setData(team_data->index(row,4),"");
    team_data->setData(team_data->index(row,5),"");
    team_data->setData(team_data->index(row,6),"");
    team_data->setData(team_data->index(row,7),"");
    team_data->setData(team_data->index(row,8),"Total Capacity:");
    team_data->setData(team_data->index(row,9),total);


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


void DisplayStadiums::on_pb_largedistance_clicked()
{
    team_data->setSort(team_data->fieldIndex("distance_to_center_field"), Qt::DescendingOrder);
    team_data->setFilter("distance_to_center_field = (SELECT MAX(distance_to_center_field) FROM teams)");
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

    for (int row = 10; row < team_data->rowCount(); ++row) {
        ui->tableView->setRowHidden(row, true);
    }
}


void DisplayStadiums::on_pb_smalldistance_clicked()
{
    team_data->setSort(team_data->fieldIndex("distance_to_center_field"), Qt::AscendingOrder);
    team_data->setFilter("distance_to_center_field = (SELECT MIN(distance_to_center_field) FROM teams)");
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

    for (int row = 10; row < team_data->rowCount(); ++row) {
        ui->tableView->setRowHidden(row, true);
    }
}

