#ifndef DISPLAYTEAMS_H
#define DISPLAYTEAMS_H

#include <QWidget>
#include <QSqlTableModel>
#include "db.h"

namespace Ui {
class DisplayTeams;
}

class DisplayTeams : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayTeams(QWidget *parent = nullptr);
    ~DisplayTeams();

private slots:
    void on_pb_mlbteam_clicked();

    void on_pb_exit_clicked();

    void on_pb_american_clicked();

    void on_pb_national_clicked();

private:
    Ui::DisplayTeams *ui;
    QSqlTableModel *team_data;
};

#endif // DISPLAYTEAMS_H
