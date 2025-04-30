#ifndef REGUSER_H
#define REGUSER_H

#include <QDialog>

namespace Ui {
class reguser;
}

/**
 * @class reguser
 * @brief Dialog for registering a new user.
 *
 * This class provides a user interface for user registration, allowing new users
 * to input their credentials and register within the system.
 */
class reguser : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the reguser dialog.
     * @param parent Optional parent widget.
     */
    explicit reguser(QWidget *parent = nullptr);

    /// @brief Destructor for reguser.
    ~reguser();

private slots:
    /// @brief Handles the event when the cancel button is clicked.
    void on_buttonBox_rejected();

    /// @brief Handles the event when the register button is clicked.
    void on_buttonBox_accepted();

private:
    Ui::reguser *ui; /**< Pointer to the UI instance of the reguser dialog. */
};

#endif // REGUSER_H
