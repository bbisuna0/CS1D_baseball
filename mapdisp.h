#ifndef MAPDISP_H
#define MAPDISP_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>


/**
 * @struct routeType
 * @brief Represents a route edge between two stadiums with a specified line type.
 */
struct routeType {
    QString origin;         /**< Starting stadium name. */
    QString destination;    /**< Ending stadium name. */
    QString type;           /**< Type of line: "solid", "dashed", or "blink". */
};


/**
 * @class ConnectionLine
 * @brief A visual line between two DiamondWidgets with optional animation or styling.
 */
class ConnectionLine : public QWidget {
    Q_OBJECT
public:
    /**
     * @enum LineMode
     * @brief Available line display modes.
     */
    enum LineMode { Solid, Dashed, Blink, Remove };


    /**
     * @brief Computes the visual center of a diamond widget.
     * @param w The widget to compute the center for.
     * @return Center point as QPoint.
     */
    QPoint getDiamondCenter(QWidget *w) {
        // Match the diamond center logic in DiamondWidget (fixed size: 40x40, offset upward by 8px)
        QRect geom = w->geometry();
        return QPoint(geom.left() + w->width() / 2, geom.top() + w->height() / 2 - 8);
    }


    /**
     * @brief Constructs a ConnectionLine between two widgets.
     * @param parent The parent container widget.
     * @param from Source widget.
     * @param to Target widget.
     * @param mode Line display mode.
     */
    ConnectionLine(QWidget *parent, QWidget *from, QWidget *to, LineMode mode = Solid)
        : QWidget(parent), source(from), target(to), lineMode(mode)
    {
        setAttribute(Qt::WA_TransparentForMouseEvents);
        setAttribute(Qt::WA_NoSystemBackground);
        setGeometry(parent->rect());
        raise();
        show();

        if (lineMode == Blink) {
            flashTimer = new QTimer(this);
            flashTimer->setInterval(200);  // Toggle every 200 ms
            connect(flashTimer, &QTimer::timeout, this, &ConnectionLine::toggleVisibility);
            flashTimer->start();

            // Stop blinking after 0.8 seconds
            QTimer::singleShot(800, this, [this]() {
                flashTimer->stop();
                this->setVisible(true);
                this->lineMode = Solid;  // revert to solid line after blink
                update();
            });
        }

        if (lineMode == Remove)
            this->setVisible(false);
    }

protected:
    /**
     * @brief Handles painting of the connection line.
     */
    void paintEvent(QPaintEvent *) override {
        if (!source || !target || !isVisible()) return;

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPen pen(Qt::red, 2);
        if (lineMode == Dashed) {
            //QPen pen(Qt::blue, 2);
            //pen.setStyle(Qt::CustomDashLine);
            pen.setStyle(Qt::DashLine);
            pen.setDashPattern({3, 4});  // 10 pixels on, 10 pixels off
        }


        painter.setPen(pen);

        // Use adjusted diamond centers
        QPoint srcCenter = getDiamondCenter(source);
        QPoint dstCenter = getDiamondCenter(target);

        painter.drawLine(srcCenter, dstCenter);
    }


private slots:
    /**
     * @brief Toggles visibility for blinking effect.
     */
    void toggleVisibility() {
        setVisible(!isVisible());
    }


private:
    QWidget *source;          /**< Start widget of the connection. */
    QWidget *target;          /**< End widget of the connection. */
    LineMode lineMode;        /**< Current line mode. */
    QTimer *flashTimer = nullptr; /**< Timer used for blinking effect. */
};


/**
 * @class DiamondWidget
 * @brief A draggable diamond-shaped widget that displays a wrapped stadium name.
 */
class DiamondWidget : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Constructs a DiamondWidget with the given label.
     * @param text The stadium name.
     * @param parent Parent QWidget.
     */
    explicit DiamondWidget(const QString& text, QWidget *parent = nullptr)
        : QWidget(parent), label(text)
    {
        setFixedSize(70, 55);  // Size for diamond + wrapped text
        setMouseTracking(true);
    }


    /**
     * @brief Returns the stadium label.
     * @return Stadium name.
     */
    QString getLabel() const {
        return label;
    }

protected:
    /**
     * @brief Paints the diamond and its wrapped label.
     */
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        // Yellow diamond
        painter.setBrush(QColor("#FFD700"));
        painter.setPen(Qt::black);

        QPoint center(width() / 2, height() / 2 - 8);
        int half = 5;

        QPolygon diamond;
        diamond << QPoint(center.x(), center.y() - half)
                << QPoint(center.x() + half, center.y())
                << QPoint(center.x(), center.y() + half)
                << QPoint(center.x() - half, center.y());

        painter.drawPolygon(diamond);

        // Draw smart-wrapped label below the diamond
        QFont font = painter.font();
        font.setPointSize(7);
        painter.setFont(font);
        painter.setPen(Qt::black);

        QString wrappedLabel = wrapLabel(label, width(), font);
        painter.drawText(QRect(0, center.y() + half + 2, width(), 20),
                         Qt::AlignHCenter | Qt::AlignTop,
                         wrappedLabel);
    }

    /**
     * @brief Captures the start point for dragging.
     */
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            dragStart = event->pos();
        }
    }

    /**
     * @brief Moves the widget during a drag operation.
     */
    void mouseMoveEvent(QMouseEvent *event) override {
        if (event->buttons() & Qt::LeftButton) {
            QPoint delta = event->pos() - dragStart;
            move(pos() + delta);
            emit positionChanged();  // Notify if used with connecting lines
        }
    }

signals:
    /**
     * @brief Emitted when the widget is moved.
     */
    void positionChanged();  // Useful if you want to update lines dynamically

private:
    QString label;           /**< The stadium name label. */
    QPoint dragStart;        /**< The drag start position. */


    /**
     * @brief Wraps text over multiple lines at space boundaries to fit within width.
     * @param input Input string.
     * @param maxWidth Maximum width for wrapping.
     * @param font Font used to calculate string width.
     * @return Wrapped string with newlines.
     */
    QString wrapLabel(const QString& input, int maxWidth, const QFont& font) const {
        QFontMetrics fm(font);
        QStringList words = input.split(' ');
        QString result, line;

        for (const QString& word : words) {
            QString testLine = line.isEmpty() ? word : line + " " + word;
            if (fm.horizontalAdvance(testLine) > maxWidth) {
                if (!line.isEmpty()) result += line + '\n';
                line = word;
            } else {
                line = testLine;
            }
        }
        result += line;
        return result;
    }
};


/**
 * @class mapdisp
 * @brief A QWidget that displays stadiums as diamond widgets and routes as lines between them.
 */
namespace Ui {
class mapdisp;
}

class mapdisp : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the map display window and optionally loads stadiums from the database.
     * @param disp If true, opens in display-only mode.
     * @param x Optional x-offset.
     * @param y Optional y-offset.
     * @param parent Optional parent QWidget.
     */
    explicit mapdisp(bool disp = true, const int &x = 570, const int &y = 270 , QWidget *parent = nullptr);


    /**
     * @brief Destructor for mapdisp.
     */
    ~mapdisp();


    /**
     * @brief Adds a route entry to the route vector.
     * @param start Starting stadium.
     * @param end Destination stadium.
     * @param type Type of connection ("solid", "blink", "dashed").
     */
    void routeAdd(QString start, QString end, QString type) {
        routeType routeEntry;
        routeEntry.origin = start;
        routeEntry.destination = end;
        routeEntry.type = type;
        route.push_back(routeEntry);
    }


    /**
     * @brief Finds the index of a DiamondWidget by label.
     * @param targetLabel Label to search for.
     * @return Index in the diamonds vector, or -1 if not found.
     */
    int findDiamondIndexByLabel(const QString& targetLabel) {
        for (int i = 0; i < diamonds.size(); ++i) {
            if (diamonds[i]->getLabel() == targetLabel) {
                return i;
            }
        }
        return -1;  // Not found
    }

private slots:
    /**
     * @brief Closes the map window.
     */
    void on_pb_exit_clicked();

    /**
     * @brief Displays "blink"-type routes as solid lines.
     */
    void on_pb_route_clicked();

    /**
     * @brief Displays "dashed"-type routes as dashed lines.
     */
    void on_pb_animate_clicked();

    /**
     * @brief Cancels changes and closes the map window.
     */
    void on_pb_cancel_clicked();

    /**
     * @brief Saves all diamond positions to the stadium_location table.
     */
    void on_pb_save_clicked();

    /**
     * @brief Animates "blink"-type routes one-by-one using a timer.
     */
    void on_pb_all_clicked();

    /**
     * @brief Displays all routes: blink as solid, others as dashed.
     */
    void on_pb_backedges_clicked();

private:
    Ui::mapdisp *ui;                            /**< UI object. */
    QVector<DiamondWidget*> diamonds;          /**< List of all stadium widgets. */
    QVector<ConnectionLine*> lines;            /**< List of all drawn connections. */
    QVector<routeType> route;                  /**< List of logical route edges. */
};



#endif // MAPDISP_H
