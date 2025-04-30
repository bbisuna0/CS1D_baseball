#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "main.h"

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

    void on_lineEdit_password_returnPressed();

    void on_pushButton_register_clicked();

private:
    Ui::LoginWindow *ui;
};
#endif // LOGINWINDOW_H
