#ifndef DISPLAY_DFS_BFS_H
#define DISPLAY_DFS_BFS_H

#include <QDialog>

namespace Ui {
class display_dfs;
}

class display_dfs : public QDialog
{
    Q_OBJECT

public:
    explicit display_dfs(QWidget *parent = nullptr);
    ~display_dfs();

    void setOutput(const QString& text);

private:
    Ui::display_dfs *ui;
};

#endif // DISPLAY_DFS_BFS_H
