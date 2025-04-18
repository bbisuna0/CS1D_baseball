#include "display_souvenirs.h"
#include "ui_display_souvenirs.h"

display_souvenirs::display_souvenirs(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::display_souvenirs)
{
    ui->setupUi(this);
}

display_souvenirs::~display_souvenirs()
{
    delete ui;
}

void display_souvenirs::appendSouvenirText(const QString& text) {
    ui->textEdit->append(text);
}
