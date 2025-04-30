#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include "main.h"

/// Global instance representing the logged-in user.
extern User myUser;

namespace Ui {
class mainmenu;
}

class mainmenu : public QWidget
{
    Q_OBJECT

public:
    explicit mainmenu(QWidget *parent = nullptr);
    ~mainmenu();

private slots:
    void on_pb_exit_clicked();

    void on_pb_team_details_clicked();

    void on_pb_plan_vacation_clicked();

    void on_pb_team_report_clicked();

    void on_pb_stadium_report_clicked();

    void on_pb_maintenance_clicked();

private:
    Ui::mainmenu *ui;
};

#endif // MAINMENU_H
