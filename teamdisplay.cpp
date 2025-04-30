#include "teamdisplay.h"
#include "ui_teamdisplay.h"
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QSqlRelationalDelegate>

void teamdisplay::onRecordChanged(int index)
{
    // You can access the current record like this:
    QSqlRecord record = teamModel->record(index);
    QString team = record.value("team_name").toString();
    QString logoPath = QString(":/logos/%1.png").arg(team.toLower().replace(' ', '-'));
    QPixmap pixmap(logoPath);
    if (!pixmap.isNull()) {
        ui->teamlogo->setPixmap(pixmap);
    }
    else
    {
        logoPath = QString(":/logos/generic-team.png");
        QPixmap pixmap(logoPath);
        ui->teamlogo->setPixmap(pixmap);
    }

    int row = mapper->currentIndex();
    QModelIndex rindex = teamModel->index(row,0);
    bool markedDeletion = teamModel->isDirty(rindex);
    if (markedDeletion)
        qDebug() << "Marked Row";

    // int teamId = teamModel->record(index).value("id").toInt();

    // souvenirModel->setFilter(QString("team_id = %1").arg(teamId));

    souvenirModel->setFilter(QString("team_name = '%1'").arg(team));
    souvenirModel->select();
}


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

    // Set label alignment to left
    formLayout->setLabelAlignment(Qt::AlignLeft);

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

    formLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    formLayout->setLabelAlignment(Qt::AlignLeft);

    groupBoxLayout->addLayout(formLayout, /*stretch=*/0);
    groupBoxLayout->setAlignment(formLayout, Qt::AlignLeft);

    ui->teamBox->setLayout(groupBoxLayout);
    ui->teamBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    teamModel = new QSqlTableModel(this);
    teamModel->setTable("teams"); // your actual table name
    teamModel->select();
    teamModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(teamModel);
    //mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit); // Save on widget change
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit); // Save on save button

    mapper->addMapping(teamName, teamModel->fieldIndex("team_name"));
    mapper->addMapping(stadiumName, teamModel->fieldIndex("stadium_name"));
    mapper->addMapping(seatingCapacity, teamModel->fieldIndex("seating_capacity"));
    mapper->addMapping(location, teamModel->fieldIndex("location"));
    mapper->addMapping(playingSurface, teamModel->fieldIndex("playing_surface"));
    mapper->addMapping(league, teamModel->fieldIndex("league"));
    mapper->addMapping(dateOpened, teamModel->fieldIndex("date_opened"));
    mapper->addMapping(distanceToCenterField, teamModel->fieldIndex("distance_to_center_field"));
    mapper->addMapping(ballparkTypology, teamModel->fieldIndex("ballpark_typology"));
    mapper->addMapping(roofType, teamModel->fieldIndex("roof_type"));

    mapper->toFirst(); // Or to a specific row: mapper->setCurrentIndex(rowIndex);

    connect(ui->pb_right, &QPushButton::clicked, mapper, &QDataWidgetMapper::toNext);
    connect(ui->pb_left, &QPushButton::clicked, mapper, &QDataWidgetMapper::toPrevious);

    bool editable = true;
    if (!myUser.admin)
        editable = false;

    teamName->setReadOnly(!editable);
    stadiumName->setReadOnly(!editable);
    seatingCapacity->setEnabled(editable);
    location->setReadOnly(!editable);
    playingSurface->setReadOnly(!editable);
    league->setEnabled(editable);
    dateOpened->setEnabled(editable);
    distanceToCenterField->setReadOnly(!editable);
    ballparkTypology->setReadOnly(!editable);
    roofType->setReadOnly(!editable);

    //souvenirModel = new QSqlRelationalTableModel(this);
    souvenirModel = new QSqlTableModel(this);
    souvenirModel->setTable("souvenirs");
    souvenirModel->setHeaderData(0, Qt::Horizontal, "ID");
    souvenirModel->setHeaderData(1, Qt::Horizontal, "Team Name");
    souvenirModel->setHeaderData(2, Qt::Horizontal, "Souvenir");
    souvenirModel->setHeaderData(3, Qt::Horizontal, "Price");
    souvenirModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    // souvenirModel->setRelation(
    //     souvenirModel->fieldIndex("team_id"),
    //     QSqlRelation("teams", "id", "team_name")
    //     );

    souvenirModel->select();

    ui->tv_souvenirs->setModel(souvenirModel);

    ui->tv_souvenirs->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tv_souvenirs->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tv_souvenirs->setColumnHidden(souvenirModel->fieldIndex("id"), true);
    ui->tv_souvenirs->setColumnHidden(souvenirModel->fieldIndex("team_name"), true);
    ui->tv_souvenirs->setColumnHidden(souvenirModel->fieldIndex("item_name"), false);
    ui->tv_souvenirs->setColumnHidden(souvenirModel->fieldIndex("price"), false);
    ui->tv_souvenirs->resizeColumnsToContents();

    ui->tv_souvenirs->setColumnWidth(souvenirModel->fieldIndex("item_name"), 180);

    int priceColumn = souvenirModel->fieldIndex("price");
    ui->tv_souvenirs->setItemDelegateForColumn(priceColumn, new CurrencyDelegate(ui->tv_souvenirs));

    if (myUser.admin) {
        ui->tv_souvenirs->setEditTriggers(QAbstractItemView::DoubleClicked |
                                          QAbstractItemView::SelectedClicked |
                                          QAbstractItemView::EditKeyPressed);
    } else {
        ui->tv_souvenirs->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }

    //ui->tv_souvenirs->setItemDelegate(new QSqlRelationalDelegate(ui->tv_souvenirs));


    connect(mapper, &QDataWidgetMapper::currentIndexChanged,
            this, &teamdisplay::onRecordChanged);
    onRecordChanged(0);

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

void teamdisplay::on_buttonBox_accepted()
{
    if (!mapper->submit()) {
        qDebug() << "Submit failed:" << teamModel->lastError().text();
    }
    teamModel->submitAll(); // Persist to DB
    if (!souvenirModel->submitAll()) {
        qDebug() << "Failed to submit changes:" << souvenirModel->lastError().text();
        // Optional: Show user a message box
    }
}


void teamdisplay::on_buttonBox_rejected()
{
    mapper->revert();          // Reverts changes in widgets
    teamModel->revertAll();    // Reverts unsubmitted model changes
    souvenirModel->revertAll();  // Discard unsaved changes
    reject();                  // Closes the dialog
}


void teamdisplay::on_pushButton_clicked()
{
    int row = mapper->currentIndex();
    teamModel->removeRow(row);  // Marks the row for deletion only
    QModelIndex index = teamModel->index(row,0);
    bool markedDeletion = teamModel->isDirty(index);
    if (markedDeletion)
        qDebug() << "Marked Row";
    //teamModel->revertRow(row);

}

