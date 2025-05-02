#include "map.h"
#include "ui_map.h"
#include <QTimer>

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



map::map(bool disp, const int& x, const int& y, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::map)
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
}

map::~map()
{
    delete ui;
}

void map::on_pb_exit_clicked()
{
    close();
}


void map::on_pb_route_clicked()
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


void map::on_pb_animate_clicked()
{
    ConnectionLine *lineA = drawLine(ui->label, diamonds[0], diamonds[1], "blink");
    QTimer::singleShot(500, this, SLOT(on_pb_animate_clicked()));
    this->update();
    ConnectionLine *lineB = drawLine(ui->label, diamonds[1], diamonds[2], "blink");
    QTimer::singleShot(500, this, SLOT(on_pb_animate_clicked()));
    this->update();
    ConnectionLine *lineC = drawLine(ui->label, diamonds[2], diamonds[3], "blink");
    QTimer::singleShot(500, this, SLOT(on_pb_animate_clicked()));
    this->update();
    ConnectionLine *lineD = drawLine(ui->label, diamonds[3], diamonds[4], "blink");
    QTimer::singleShot(500, this, SLOT(on_pb_animate_clicked()));
    this->update();
    ConnectionLine *lineE = drawLine(ui->label, diamonds[4], diamonds[5], "blink");
    QTimer::singleShot(500, this, SLOT(on_pb_animate_clicked()));
    this->update();
}


void map::on_pb_cancel_clicked()
{
    close();
}


void map::on_pb_save_clicked()
{
    close();
}


void map::on_pb_all_clicked()
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

