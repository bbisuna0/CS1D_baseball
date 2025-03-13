#include "teamdisplay.h"
#include "ui_teamdisplay.h"

teamdisplay::teamdisplay(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::teamdisplay)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: darkblue;");
}

teamdisplay::~teamdisplay()
{
    delete ui;
}
