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

/**
 * @class LoginWindow
 * @brief Provides a user interface for login and registration functionality.
 *
 * This class manages user authentication, including username/password validation,
 * login attempt tracking, and access to the registration dialog.
 */
class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the LoginWindow and initializes the UI.
     * @param parent Pointer to the parent widget.
     */
    explicit LoginWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for LoginWindow. Cleans up resources.
     */
    ~LoginWindow();

private slots:
    /**
     * @brief Closes the login window when the Exit button is clicked.
     */
    void on_pushButton_exit_clicked();

    /**
     * @brief Handles login logic when the Login button is clicked.
     */
    void on_pushButton_login_clicked();

    /**
     * @brief Triggers login when Enter is pressed in the password field.
     */
    void on_lineEdit_password_returnPressed();

    /**
     * @brief Opens the registration dialog when the Register button is clicked.
     */
    void on_pushButton_register_clicked();

private:
    Ui::LoginWindow *ui;  /**< Pointer to the auto-generated UI class. */
};

#endif // LOGINWINDOW_H
