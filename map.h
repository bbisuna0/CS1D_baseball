#ifndef MAP_H
#define MAP_H

#include <QWidget>

namespace Ui {
class map;
}

class map : public QWidget
{
    Q_OBJECT

public:
    explicit map(QWidget *parent = nullptr);
    ~map();

private slots:
    void on_pb_exit_clicked();

private:
    Ui::map *ui;
};

#endif // MAP_H
