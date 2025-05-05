#include "tripdisplay.h"
#include "ui_tripdisplay.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QSortFilterProxyModel>
#include "purchasesouvenirs.h"
#include "utility.h"

tripdisplay::tripdisplay(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::tripdisplay)
{
    ui->setupUi(this);

}

tripdisplay::tripdisplay(const std::vector<CollegeData>& data, float totalDistance, std::vector<SouvenirData>& souvenirListParm, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::tripdisplay)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    //ui->tableView->setModel(model);


    model->setHorizontalHeaderLabels({"College Start", "College End", "Distance"});

    // Populate Table
    for (const auto& entry : data) {
        QList<QStandardItem*> rowItems;
        rowItems.append(new QStandardItem(QString::fromStdString(entry.collegeStart)));
        rowItems.append(new QStandardItem(QString::fromStdString(entry.collegeEnd)));
        rowItems.append(new QStandardItem(QString::number(entry.distance, 'f', 2)));
        model->appendRow(rowItems);
    }

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->tableView->setModel(proxyModel);

    ui->tableView->setColumnWidth(0, 400);
    ui->tableView->setColumnWidth(1, 400);
    ui->tableView->setColumnWidth(2, 100);
    ui->label_2->setText(QString::fromStdString("Total Distance Travelled: ") + QString::number(totalDistance, 'f', 2));
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    souvenirList = souvenirListParm;



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
    for (auto row : souvenirList) {
        editRow.college = row.college;
        editRow.souvenir =  row.souvenir;
        editRow.cost =row.cost;
        editRow.quantity = 0;
        if (isCollegeMatch(model, QString::fromStdString(row.college))){
            editData.push_back(editRow);
            qDebug() << QString::fromStdString(row.college);
        }
    }
    purchasesouvenirs c(editData, this);
    c.exec();
}

