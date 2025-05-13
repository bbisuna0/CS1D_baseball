#ifndef MAPDISP_H
#define MAPDISP_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>

class ConnectionLine : public QWidget {
    Q_OBJECT
public:
    enum LineMode { Solid, Dashed, Blink, Remove };

    QPoint getDiamondCenter(QWidget *w) {
        // Match the diamond center logic in DiamondWidget (fixed size: 40x40, offset upward by 8px)
        QRect geom = w->geometry();
        return QPoint(geom.left() + w->width() / 2, geom.top() + w->height() / 2 - 8);
    }

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
    void toggleVisibility() {
        setVisible(!isVisible());
    }

private:
    QWidget *source;
    QWidget *target;
    LineMode lineMode;
    QTimer *flashTimer = nullptr;
};



class DiamondWidget : public QWidget {
    Q_OBJECT
public:
    explicit DiamondWidget(const QString& text, QWidget *parent = nullptr)
        : QWidget(parent), label(text)
    {
        setFixedSize(40, 40);  // Size for diamond + text
        setMouseTracking(true);
    }

protected:
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

        // Draw label below diamond
        QFont font = painter.font();
        font.setPointSize(9);
        painter.setFont(font);
        painter.setPen(Qt::black);
        painter.drawText(QRect(0, center.y() + half + 2, width(), 20), Qt::AlignHCenter | Qt::AlignTop, label);
    }

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            dragStart = event->pos();
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (event->buttons() & Qt::LeftButton) {
            QPoint delta = event->pos() - dragStart;
            move(pos() + delta);
            emit positionChanged();  // Notify if used with connecting lines
        }
    }

signals:
    void positionChanged();  // Useful if you want to update lines dynamically

private:
    QString label;
    QPoint dragStart;
};




namespace Ui {
class mapdisp;
}

class mapdisp : public QWidget
{
    Q_OBJECT

public:
    explicit mapdisp(bool disp = true, const int &x = 570, const int &y = 270 , QWidget *parent = nullptr);
    ~mapdisp();

private slots:
    void on_pb_exit_clicked();

    void on_pb_route_clicked();

    void on_pb_animate_clicked();

    void on_pb_cancel_clicked();

    void on_pb_save_clicked();

    void on_pb_all_clicked();

private:
    Ui::mapdisp *ui;
    QVector<DiamondWidget*> diamonds;
    QVector<ConnectionLine*> lines;
};

#endif // MAPDISP_H
