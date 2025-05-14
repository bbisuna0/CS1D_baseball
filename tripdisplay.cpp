#include "tripdisplay.h"
#include "ui_tripdisplay.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QSortFilterProxyModel>
#include "purchasesouvenirs.h"
#include "utility.h"
#include <QDebug>
#include "mapdisp.h"
#include "ui_mapdisp.h"

tripdisplay::tripdisplay(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::tripdisplay)
{
    ui->setupUi(this);

}

tripdisplay::tripdisplay(const std::vector<TripEntry>& data, float totalDistance, bool souvenirDisp, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::tripdisplay)
{
    ui->setupUi(this);
    if (!souvenirDisp) {
        ui->saddlebackPB->hide();
    }


    model = new QStandardItemModel(this);
    //ui->tableView->setModel(model);


    model->setHorizontalHeaderLabels({"Origin", "Destination", "Distance", "Type"});

    // Populate Table
    for (const auto& entry : data) {
        QList<QStandardItem*> rowItems;
        rowItems.append(new QStandardItem(entry.origin));
        rowItems.append(new QStandardItem(entry.destination));
        rowItems.append(new QStandardItem(QString::number(entry.distance, 'f', 2)));
        rowItems.append(new QStandardItem(entry.type));
        model->appendRow(rowItems);
        qDebug() << entry.origin;
    }

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->tableView->setModel(proxyModel);

    ui->tableView->setColumnWidth(0, 400);
    ui->tableView->setColumnWidth(1, 400);
    ui->tableView->setColumnWidth(2, 100);
    ui->label_2->setText(QString::fromStdString("Total Distance Travelled: ") + QString::number(totalDistance, 'f', 2));
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //souvenirList = souvenirListParm;



}




tripdisplay::~tripdisplay()
{
    delete ui;
}

void tripdisplay::on_buttonBox_accepted()
{
    this->close();
}


void tripdisplay::on_saddlebackPB_clicked()
{
    //std::vector<SouvenirData> data;
    //data = loadSouvenirCSV("souvenirs1.csv");
    std::vector<SouvenirPurchase> editData;
    SouvenirPurchase editRow;

    QSqlTableModel *souvenir_data;
    souvenir_data = new QSqlTableModel(this);
    souvenir_data->setTable("souvenirs");
    if (teams.empty())
        souvenir_data->setFilter("0=1");
    else {
        // Convert std::vector<std::string> → QStringList
        QStringList quotedTeams;
        for (const std::string& name : teams) {
            quotedTeams << "'" + QString::fromStdString(name).replace("'", "''") + "'";
        }
        QString filter = QString("team_name IN (%1)").arg(quotedTeams.join(", "));
        souvenir_data->setFilter(filter);
    }
    souvenir_data->select();

    for (int row = 0; row < souvenir_data->rowCount(); ++row) {
        QModelIndex index = souvenir_data->index(row, 1); //team name
        QVariant value = souvenir_data->data(index);
        editRow.team = value.toString();
        index = souvenir_data->index(row, 2); //item name
        value = souvenir_data->data(index);
        editRow.souvenir = value.toString();
        index = souvenir_data->index(row, 3); //price
        value = souvenir_data->data(index);
        editRow.price = value.toString();
        editRow.quantity = 0;
        qDebug() << editRow.team;
        qDebug() << editRow.souvenir;
        qDebug() << editRow.price;
        editData.push_back(editRow);
    }

    purchasesouvenirs c(editData, this);
    c.exec();
}


void tripdisplay::on_pbMap_clicked()
{
    mapdisp *mapWin = new mapdisp();
    mapWin->show();
}

