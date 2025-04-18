#ifndef DISPLAY_SOUVENIRS_H
#define DISPLAY_SOUVENIRS_H

#include <QDialog>

namespace Ui {
class display_souvenirs;
}

class display_souvenirs : public QDialog
{
    Q_OBJECT

public:
    explicit display_souvenirs(QWidget *parent = nullptr);
    ~display_souvenirs();
    void appendSouvenirText(const QString& text);


private:
    Ui::display_souvenirs *ui;
};

#endif // DISPLAY_SOUVENIRS_H
