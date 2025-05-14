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


/**
 * @class TeamSelectionDialog
 * @brief Dialog for selecting MLB teams to visit.
 *
 * Provides a dual-list interface for users to select teams from an available list,
 * manage their selections, and retrieve either selected team names or mapped stadium names.
 */
class TeamSelectionDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructor for TeamSelectionDialog.
     * @param parent Optional parent widget.
     */
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

    /**
     * @brief Gets the list of selected stadiums mapped from selected team names.
     * @return QStringList of stadium names.
     */
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

    /**
     * @brief Gets the list of selected team names.
     * @return QStringList of team names.
     */
    // Returns team names in the selected list
    QStringList getSelectedTeams() const {
        QStringList selectedTeams;
        for (int i = 0; i < selectedList->count(); ++i) {
            QListWidgetItem* item = selectedList->item(i);
            selectedTeams.append(item->text());  // The text is the team name
        }
        return selectedTeams;
    }

    /**
     * @brief Removes a team from the available list.
     * @param teamName Name of the team to exclude.
     */
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
    /**
     * @brief Populates the available team list from the database model.
     */
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

    /**
     * @brief Moves selected team from available to selected list.
     */
    void addSelected() {
        QListWidgetItem* item = availableList->currentItem();
        if (item) {
            selectedList->addItem(item->clone());
            delete availableList->takeItem(availableList->currentRow());
        }
        availableList->sortItems();
    }

    /**
     * @brief Moves selected team from selected list back to available list.
     */
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
