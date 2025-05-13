#ifndef TEAMSELECTDIALOG_H
#define TEAMSELECTDIALOG_H

#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSet>
#include <QStringList>

class TeamSelectionDialog : public QDialog {
    Q_OBJECT

public:
    TeamSelectionDialog(QWidget* parent = nullptr) : QDialog(parent) {
        setWindowTitle("Select Teams to Visit");

        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        QHBoxLayout* listLayout = new QHBoxLayout();

        availableList = new QListWidget();
        selectedList = new QListWidget();

        listLayout->addWidget(availableList);
        listLayout->addWidget(selectedList);
        mainLayout->addLayout(listLayout);

        QHBoxLayout* buttonLayout = new QHBoxLayout();
        addButton = new QPushButton("Add");
        removeButton = new QPushButton("Remove");
        okButton = new QPushButton("OK");
        cancelButton = new QPushButton("Cancel");

        buttonLayout->addWidget(addButton);
        buttonLayout->addWidget(removeButton);
        buttonLayout->addStretch();
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);
        mainLayout->addLayout(buttonLayout);

        connect(addButton, &QPushButton::clicked, this, &TeamSelectionDialog::addSelected);
        connect(removeButton, &QPushButton::clicked, this, &TeamSelectionDialog::removeSelected);
        connect(okButton, &QPushButton::clicked, this, &TeamSelectionDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &TeamSelectionDialog::reject);

        populateAvailableListFromModel();
    }

    // Returns stadium names (mapped from selected team names)
    QStringList getSelectedStadiums() const {
        QStringList selectedStadiums;
        for (int i = 0; i < selectedList->count(); ++i) {
            QListWidgetItem* item = selectedList->item(i);
            QString stadiumName = item->data(Qt::UserRole).toString(); // Retrieve stored stadium
            selectedStadiums.append(stadiumName);
        }
        return selectedStadiums;
    }

    // Removes a team from the available list based on team name
    void excludeTeam(const QString& teamName) {
        for (int i = 0; i < availableList->count(); ++i) {
            QListWidgetItem* item = availableList->item(i);
            if (item->text() == teamName) {
                delete availableList->takeItem(i);
                break;  // Stop after removing one match
            }
        }
    }

private:
    void populateAvailableListFromModel() {
        QSqlTableModel model;
        model.setTable("teams");
        model.select();

        QSet<QString> seenTeams;
        for (int i = 0; i < model.rowCount(); ++i) {
            QSqlRecord record = model.record(i);
            QString teamName = record.value("team_name").toString();
            QString stadiumName = record.value("stadium_name").toString();

            if (!seenTeams.contains(teamName)) {
                seenTeams.insert(teamName);
                QListWidgetItem* item = new QListWidgetItem(teamName);
                item->setData(Qt::UserRole, stadiumName);  // Store stadium name
                availableList->addItem(item);
            }
        }

        availableList->sortItems();
    }

    void addSelected() {
        QListWidgetItem* item = availableList->currentItem();
        if (item) {
            selectedList->addItem(item->clone());
            delete availableList->takeItem(availableList->currentRow());
        }
        availableList->sortItems();
    }

    void removeSelected() {
        QListWidgetItem* item = selectedList->currentItem();
        if (item) {
            availableList->addItem(item->clone());
            delete selectedList->takeItem(selectedList->currentRow());
        }
        availableList->sortItems();
    }


    QListWidget* availableList;
    QListWidget* selectedList;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* okButton;
    QPushButton* cancelButton;
};


#endif // TEAMSELECTDIALOG_H
