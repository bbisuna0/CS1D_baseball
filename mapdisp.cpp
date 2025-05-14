/**
 * @file mapdisp.cpp
 * @brief Implements stadium map visualization and interaction for planning or displaying routes.
 *
 * Provides a draggable diamond widget interface to represent stadiums,
 * allowing routes to be visualized and positions to be saved to the database.
 */

#include "mapdisp.h"
#include "ui_mapdisp.h"
#include <QTimer>
#include <QSqlTableModel>


/**
 * @brief Draws a line between two DiamondWidgets with a specified mode.
 * @param container The widget on which the line will be drawn.
 * @param from Source diamond widget.
 * @param to Destination diamond widget.
 * @param modeStr A string indicating the line mode ("solid", "dashed", "blink", or "remove").
 * @return A pointer to the newly created ConnectionLine.
 */
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


/**
 * @class mapdisp
 * @brief Visual interface for displaying and editing stadium map and route overlays.
 */

/**
 * @brief Constructs the mapdisp widget and populates it with stadium diamond widgets.
 * @param disp If true, display-only mode; if false, enables editing/saving.
 * @param x Optional initial X offset.
 * @param y Optional initial Y offset.
 * @param parent Optional parent widget.
 */
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


/**
 * @brief Destructor for mapdisp.
 */
mapdisp::~mapdisp()
{
    delete ui;
}


/**
 * @brief Closes the map display window.
 */
void mapdisp::on_pb_exit_clicked()
{
    close();
}


/**
 * @brief Draws all "blink" type route edges as solid lines.
 */
void mapdisp::on_pb_route_clicked()
{
    // Display Route
    if (!lines.empty()) {
        for (ConnectionLine* conn : lines) {
            if (conn) {
                conn->deleteLater();  // schedule deletion
            }
        }
        lines.clear();
    }

    QVector<QPair<QWidget*, QWidget*>> pendingLines;
    for (auto a : route) {
        if(a.type == "blink") {
            pendingLines.push_back({diamonds[findDiamondIndexByLabel(a.origin)],diamonds[findDiamondIndexByLabel(a.destination)]});
        }
    }
    for (auto pair : pendingLines)
        lines.push_back(new ConnectionLine(ui->label, pair.first, pair.second, ConnectionLine::Solid));
}


/**
 * @brief Draws all "dashed" type route edges as dashed lines.
 */
void mapdisp::on_pb_animate_clicked()
{
    // Display Cross/Back Edges

    if (!lines.empty()) {
        for (ConnectionLine* conn : lines) {
            if (conn) {
                conn->deleteLater();  // schedule deletion
            }
        }
        lines.clear();
    }

    QVector<QPair<QWidget*, QWidget*>> pendingLines;
    for (auto a : route) {
        if(a.type == "dashed") {
            pendingLines.push_back({diamonds[findDiamondIndexByLabel(a.origin)],diamonds[findDiamondIndexByLabel(a.destination)]});
        }
    }
    for (auto pair : pendingLines)
        lines.push_back(new ConnectionLine(ui->label, pair.first, pair.second, ConnectionLine::Dashed));
}


/**
 * @brief Cancels and closes the map editing window without saving.
 */
void mapdisp::on_pb_cancel_clicked()
{
    close();
}


/**
 * @brief Saves the current diamond widget positions to the stadium_location table.
 */
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


/**
 * @brief Animates the route by drawing blink lines one at a time with a timer.
 */
void mapdisp::on_pb_all_clicked()
{
    // Animate Route
    if (!lines.empty()) {
        for (ConnectionLine* conn : lines) {
            if (conn) {
                conn->deleteLater();  // schedule deletion
            }
        }
        lines.clear();
    }

    QVector<QPair<QWidget*, QWidget*>> pendingLines;
    for (auto a : route) {
        if(a.type == "blink") {
            pendingLines.push_back({diamonds[findDiamondIndexByLabel(a.origin)],diamonds[findDiamondIndexByLabel(a.destination)]});
        }
    }


    int currentIndex = 0;

    QTimer *lineTimer = new QTimer(this);
    lineTimer->setInterval(500);  // Draw one line every 500 ms

    connect(lineTimer, &QTimer::timeout, this, [=]() mutable {
        if (currentIndex < pendingLines.size()) {
            auto pair = pendingLines[currentIndex++];
            lines.push_back(new ConnectionLine(ui->label, pair.first, pair.second, ConnectionLine::Blink));
        } else {
            lineTimer->stop();
            lineTimer->deleteLater();
        }
    });

    lineTimer->start();
}


/**
 * @brief Draws all edges in the route: "blink" edges as solid, others as dashed.
 */
void mapdisp::on_pb_backedges_clicked()
{
    // Display all
    if (!lines.empty()) {
        for (ConnectionLine* conn : lines) {
            if (conn) {
                conn->deleteLater();  // schedule deletion
            }
        }
        lines.clear();
    }

    for (auto a : route) {
        if(a.type == "blink")
            lines.push_back(new ConnectionLine(ui->label, diamonds[findDiamondIndexByLabel(a.origin)], diamonds[findDiamondIndexByLabel(a.destination)], ConnectionLine::Solid));
        else
            lines.push_back(new ConnectionLine(ui->label, diamonds[findDiamondIndexByLabel(a.origin)], diamonds[findDiamondIndexByLabel(a.destination)], ConnectionLine::Dashed));
    }
}

