#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include "stadium.h"
#include "display_souvenirs.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWindow;
}
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_login_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::LoginWindow *ui;
    display_souvenirs *display_items;
};
#endif // LOGINWINDOW_H
