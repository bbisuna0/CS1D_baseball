#include "mapdisp.h"
#include "ui_mapdisp.h"
#include <QTimer>
#include <QSqlTableModel>

ConnectionLine* drawLine(QWidget *container, DiamondWidget *from, DiamondWidget *to, const QString &modeStr) {
    ConnectionLine::LineMode mode;

    if (modeStr == "dashed") {
        mode = ConnectionLine::Dashed;
    } else if (modeStr == "blink") {
        mode = ConnectionLine::Blink;
    } else if (modeStr == "solid"){
        mode = ConnectionLine::Solid;
    } else {
        mode = ConnectionLine::Remove;
    }

    auto *line = new ConnectionLine(container, from, to, mode);
    return line;  // Return pointer for later removal
}



mapdisp::mapdisp(bool disp, const int& x, const int& y, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mapdisp)
{
    ui->setupUi(this);
    if (disp) {
        ui->pb_save->hide();
        ui->pb_cancel->hide();
    } else {
        ui->pb_save->show();
        ui->pb_cancel->show();
        ui->pb_exit->hide();
        ui->pb_animate->hide();
        ui->pb_all->hide();
        ui->pb_backedges->hide();
        ui->pb_route->hide();
    }
    QSqlTableModel *stadium_loc;
    stadium_loc = new QSqlTableModel(this);
    stadium_loc->setTable("stadium_location");
    stadium_loc->select();

    for (int row = 0; row < stadium_loc->rowCount(); ++row) {
        QModelIndex index = stadium_loc->index(row, 0); //stadium name
        QVariant value = stadium_loc->data(index);
        std::string stadium_name = value.toString().toStdString();
        index = stadium_loc->index(row, 1); //x_loc
        value = stadium_loc->data(index);
        int xloc = value.toInt();
        index = stadium_loc->index(row, 2); //y_loc
        value = stadium_loc->data(index);
        int yloc = value.toInt();
        auto *diamond = new DiamondWidget(QString::fromStdString(stadium_name), ui->label);
        qDebug() << stadium_name << " x:" << xloc << " y:" << yloc;
        diamond->move(xloc,yloc);
        diamond->show();
        diamonds.append(diamond);
    }
}

mapdisp::~mapdisp()
{
    delete ui;
}

void mapdisp::on_pb_exit_clicked()
{
    close();
}


void mapdisp::on_pb_route_clicked()
{
    for (int i = 0; i < 10; ++i) {
        auto *diamond = new DiamondWidget(QString("Team %1").arg(i + 1), ui->label);
        diamond->move(50 + i * 60, 50);  // Stagger horizontally
        diamond->show();
        diamonds.append(diamond);
    }

    // DiamondWidget *a = new DiamondWidget("Team A", ui->label); // parent = QFrame*
    // a->move(50, 30);  // Position it inside the frame
    // a->show();

    // DiamondWidget *b = new DiamondWidget("Team B", ui->label); // parent = QFrame*
    // b->move(490, 190);  // Position it inside the frame
    // b->show();
}


void mapdisp::on_pb_animate_clicked()
{

}


void mapdisp::on_pb_cancel_clicked()
{
    close();
}


void mapdisp::on_pb_save_clicked()
{
    QSqlTableModel *stadium_loc;
    stadium_loc = new QSqlTableModel(this);
    stadium_loc->setTable("stadium_location");
    stadium_loc->select();

    for (auto stadium : diamonds) {
        QString stadiumName = stadium->getLabel();  // You’ll need a getter for `label`
        int x = stadium->x();
        int y = stadium->y();

        for (int row = 0; row < stadium_loc->rowCount(); ++row) {
            QModelIndex index = stadium_loc->index(row, stadium_loc->fieldIndex("stadium_name"));
            if (stadium_loc->data(index).toString() == stadiumName) {
                // Update x_loc and y_loc
                stadium_loc->setData(stadium_loc->index(row, stadium_loc->fieldIndex("x_loc")), x);
                stadium_loc->setData(stadium_loc->index(row, stadium_loc->fieldIndex("y_loc")), y);

                if (!stadium_loc->submitAll()) {
                    qWarning() << "Submit failed: " << stadiumName;
                } else {
                    qDebug() << "Updated " << stadiumName << "to x=" << x << ", y=" << y;
                }
            }
        }
    }
    close();
}


void mapdisp::on_pb_all_clicked()
{
    QVector<QPair<QWidget*, QWidget*>> pendingLines = {
        {diamonds[0], diamonds[1]},
        {diamonds[1], diamonds[2]},
        {diamonds[2], diamonds[3]},
        {diamonds[3], diamonds[4]},
        {diamonds[4], diamonds[5]}
    };

    int currentIndex = 0;

    QTimer *lineTimer = new QTimer(this);
    lineTimer->setInterval(1500);  // Draw one line every 500 ms

    connect(lineTimer, &QTimer::timeout, this, [=]() mutable {
        if (currentIndex < pendingLines.size()) {
            auto pair = pendingLines[currentIndex++];
            new ConnectionLine(ui->label, pair.first, pair.second, ConnectionLine::Dashed);
        } else {
            lineTimer->stop();
            lineTimer->deleteLater();
        }
    });

    lineTimer->start();

}

