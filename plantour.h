#ifndef PLANTOUR_H
#define PLANTOUR_H

#include <QWidget>

namespace Ui {
class plantour;
}

class plantour : public QWidget
{
    Q_OBJECT

public:
    explicit plantour(QWidget *parent = nullptr);
    ~plantour();

private slots:
    void on_pb_exit_clicked();

    void on_pb_team_details_clicked();

    void on_pb_team_report_clicked();

private:
    Ui::plantour *ui;
};

#endif // PLANTOUR_H
