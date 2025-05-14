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


/**
 * @brief Default constructor for tripdisplay dialog.
 * @param parent Parent widget.
 */
tripdisplay::tripdisplay(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::tripdisplay)
{
    ui->setupUi(this);

}

/**
 * @brief Overloaded constructor to initialize trip data and optionally show souvenir button.
 * @param data Vector of TripEntry representing trip route.
 * @param totalDistance Total distance of the trip.
 * @param souvenirDisp Boolean flag to enable souvenir purchasing button.
 * @param parent Parent widget.
 */
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


/**
 * @brief Destructor for tripdisplay.
 */
tripdisplay::~tripdisplay()
{
    delete ui;
}


/**
 * @brief Closes the dialog when OK is clicked.
 */
void tripdisplay::on_buttonBox_accepted()
{
    this->close();
}


/**
 * @brief Opens the souvenir purchasing dialog filtered by visited teams.
 */
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

bool containsArrow(const QString& input) {
    return input.contains("->");
}

/**
 * @brief Displays a graphical map of the trip route.
 *
 * Routes with type "discovery" are animated with blinking lines,
 * while "cross" edges are shown as dashed lines.
 */
void tripdisplay::on_pbMap_clicked()
{
    mapdisp *mapWin = new mapdisp();

    int rowCount = model->rowCount();
    int columnCount = model->columnCount();

    for (int row = 0; row < rowCount; ++row) {
        QString start;
        QString end;
        QString type;
        // if true, means the path is a dijkstra path
        if (containsArrow(model->item(row,1)->text()))
        {
            QString path = model->item(row,1)->text();
            QStringList stadiums = path.split("->", Qt::SkipEmptyParts);

            for (QString& stadium : stadiums) {
                stadium = stadium.trimmed();  // Remove leading/trailing spaces
            }

            for (int i = 0; i < stadiums.size() - 1; ++i) {
                qDebug() << "(" << stadiums[i] << "," << stadiums[i + 1] << ")";
                start = stadiums[i];
                end = stadiums[i+1];
                type = "blink";
                mapWin->routeAdd(start, end, type);
            }
        }
        else
            if (model->item(row,3)->text() == "discovery" || model->item(row,3)->text() == "cross") {
                start = model->item(row,0)->text();
                end = model->item(row,1)->text();
                if(model->item(row,3)->text() == "discovery")
                    type = "blink";
                else
                    type = "dashed";
                mapWin->routeAdd(start, end, type);
            }
    }

    mapWin->show();
}

