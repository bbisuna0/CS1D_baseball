#ifndef PLANTOUR_H
#define PLANTOUR_H

#include <QWidget>
#include "display_dfs_bfs.h"

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

    // void DFS_Oracle_Park();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::plantour *ui;
    display_dfs *print_ptr;
};

#endif // PLANTOUR_H
