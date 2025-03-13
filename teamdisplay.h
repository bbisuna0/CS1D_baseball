#ifndef TEAMDISPLAY_H
#define TEAMDISPLAY_H

#include <QDialog>

namespace Ui {
class teamdisplay;
}

class teamdisplay : public QDialog
{
    Q_OBJECT

public:
    explicit teamdisplay(QWidget *parent = nullptr);
    ~teamdisplay();

private:
    Ui::teamdisplay *ui;
};

#endif // TEAMDISPLAY_H
