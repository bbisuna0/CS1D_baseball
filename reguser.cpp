#include "reguser.h"
#include "ui_reguser.h"
#include "utility.h"

reguser::reguser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reguser)
{
    ui->setupUi(this);
}

reguser::~reguser()
{
    delete ui;
}

void reguser::on_buttonBox_rejected()
{
    this->close();
}

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
