#include "reguser.h"
#include "ui_reguser.h"
#include "utility.h"

/**
 * @brief Constructs a new reguser dialog for registering a new user.
 * @param parent The parent widget, if any.
 */
reguser::reguser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reguser)
{
    ui->setupUi(this);
}

/**
 * @brief Destructor for the reguser dialog.
 */
reguser::~reguser()
{
    delete ui;
}

/**
 * @brief Slot triggered when the Cancel button is clicked.
 * Closes the registration dialog without saving.
 */
void reguser::on_buttonBox_rejected()
{
    this->close();
}

/**
 * @brief Slot triggered when the OK button is clicked.
 * Retrieves input from the form and calls addUser to store the new user credentials.
 * Closes the dialog afterward.
 */
void reguser::on_buttonBox_accepted()
{
    QString uname;
    QString pass;
    bool admin;

    uname = ui->lineEdit->text();
    pass = ui->lineEdit_2->text();
    admin = ui->checkBox->checkState();

    addUser(0, uname, pass, admin);
    this->close();
}
