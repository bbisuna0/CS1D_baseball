#include "teamdisplay.h"
#include "ui_teamdisplay.h"

teamdisplay::teamdisplay(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::teamdisplay)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: white;");
    // Apply color scheme
    // QPalette palette;
    // palette.setColor(QPalette::Window, QColor(251, 252, 254)); // background
    // palette.setColor(QPalette::WindowText, QColor(12, 13, 23)); // text
    // palette.setColor(QPalette::Button, QColor(60, 81, 201)); // primary
    // palette.setColor(QPalette::ButtonText, QColor(12, 13, 23));
    // palette.setColor(QPalette::Highlight, QColor(132, 147, 232)); // secondary
    // palette.setColor(QPalette::Base, QColor(89, 111, 237)); // accent
    // this->setPalette(palette);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout;
    QVBoxLayout *groupBoxLayout = new QVBoxLayout(ui->teamBox);

    // Fields for MLB team information
    teamName = new QLineEdit(this);
    stadiumName = new QLineEdit(this);
    seatingCapacity = new QSpinBox(this);
    seatingCapacity->setMaximum(100000);
    seatingCapacity->setMinimum(1);
    location = new QLineEdit(this);
    playingSurface = new QLineEdit(this);
    league = new QComboBox(this);
    league->addItems({"American", "National"});
    dateOpened = new QSpinBox(this);
    dateOpened->setMaximum(2100);
    dateOpened->setMinimum(1800);
    distanceToCenterField = new QLineEdit(this);
    ballparkTypology = new QLineEdit(this);
    roofType = new QLineEdit(this);

    // Add fields to form layout
    formLayout->addRow("Team Name:", teamName);
    formLayout->addRow("Stadium Name:", stadiumName);
    formLayout->addRow("Seating Capacity:", seatingCapacity);
    formLayout->addRow("Location:", location);
    formLayout->addRow("Playing Surface:", playingSurface);
    formLayout->addRow("League:", league);
    formLayout->addRow("Date Opened:", dateOpened);
    formLayout->addRow("Distance to Center Field:", distanceToCenterField);
    formLayout->addRow("Ballpark Typology:", ballparkTypology);
    formLayout->addRow("Roof Type:", roofType);

    groupBoxLayout->addLayout(formLayout);
    ui->teamBox->setLayout(groupBoxLayout);
    // mainLayout->addLayout(formLayout);
    // ui->teamBox->layout(mainLayout);

    // Buttons
    // QPushButton *submitButton = new QPushButton("Submit", this);
    // QPushButton *cancelButton = new QPushButton("Cancel", this);

    // connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    // connect(submitButton, &QPushButton::clicked, this, &teamdisplay::validateAndSubmit);

    //QHBoxLayout *buttonLayout = new QHBoxLayout;
    //buttonLayout->addWidget(submitButton);
    //buttonLayout->addWidget(cancelButton);
    //mainLayout->addLayout(buttonLayout);
}

teamdisplay::~teamdisplay()
{
    delete ui;
}
