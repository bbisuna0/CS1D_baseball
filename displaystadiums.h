#ifndef DISPLAYSTADIUMS_H
#define DISPLAYSTADIUMS_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class DisplayStadiums;
}

class DisplayStadiums : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayStadiums(QWidget *parent = nullptr);
    ~DisplayStadiums();

private slots:
    void on_pb_exit_clicked();

    void on_pb_stadium_clicked();

    void on_pb_typology_clicked();

    void on_pb_openroof_clicked();

    void on_pb_chronological_clicked();

    void on_pb_seating_clicked();

    void on_pb_largedistance_clicked();

    void on_pb_smalldistance_clicked();

private:
    Ui::DisplayStadiums *ui;
    QSqlTableModel *team_data;
};

#endif // DISPLAYSTADIUMS_H
