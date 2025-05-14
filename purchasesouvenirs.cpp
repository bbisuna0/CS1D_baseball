#include "purchasesouvenirs.h"
#include "mergedtableview.h"
#include "ui_purchasesouvenirs.h"
#include "mergedtableview.h"
#include <QStandardItemModel>
#include "utility.h"
#include "db.h"

purchasesouvenirs::purchasesouvenirs(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::purchasesouvenirs)
{
    ui->setupUi(this);
}


purchasesouvenirs::purchasesouvenirs(const std::vector<SouvenirPurchase>& data, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::purchasesouvenirs)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);

    model->setHorizontalHeaderLabels({"Team", "Souvenir", "Cost", "Quantity"});

    // Populate Table
    for (const auto& entry : data) {
        QList<QStandardItem*> rowItems;

        // College
        rowItems.append(new QStandardItem(entry.team));

        // Souvenir
        rowItems.append(new QStandardItem(entry.souvenir));

        // Cost (converted to float)
        rowItems.append(new QStandardItem(entry.price));

        // Quantity
        QStandardItem* quantityItem = new QStandardItem(entry.quantity);
        quantityItem->setData(entry.quantity, Qt::UserRole); // Store the int value for data integrity
        rowItems.append(quantityItem);

/*        qDebug() << QString::fromStdString(entry.college);
        qDebug() << QString::fromStdString(entry.souvenir)*/;

        model->appendRow(rowItems);
    }

    ui->tableView->setModel(model);

    ui->tableView->setColumnWidth(0, 400);
    ui->tableView->setColumnWidth(1, 400);
    ui->tableView->setColumnWidth(2, 100);
    ui->tableView->setColumnWidth(3, 100); // Set width for quantity column

    // Make only the quantity column editable
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed); // Enable editing on double click or key press
    for (int col = 0; col < model->columnCount(); ++col) {
        if (col != 3) { // If it's not the quantity column
            for (int row = 0; row < model->rowCount(); ++row) {
                model->item(row, col)->setFlags(model->item(row, col)->flags() & ~Qt::ItemIsEditable); // Remove the editable flag
            }
        }
    }
}




purchasesouvenirs::~purchasesouvenirs()
{
    delete ui;
}

void purchasesouvenirs::on_purchaseButton_clicked()
{
    PurchaseSummaryDialog c(model, this);
    c.exec();
}

