#ifndef TEAMDISPLAY_H
#define TEAMDISPLAY_H

#include <QDialog>
#include <QApplication>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QSqlRelationalTableModel>

#include "main.h"

/// Global instance representing the logged-in user.
extern User myUser;

namespace Ui {
class teamdisplay;
}


/**
 * @class teamdisplay
 * @brief Dialog class for displaying and editing team and stadium information.
 *
 * Provides UI for administrators to view, edit, and delete team data as well as manage associated souvenirs.
 */
class teamdisplay : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the teamdisplay dialog.
     * @param parent Optional parent widget.
     */
    explicit teamdisplay(QWidget *parent = nullptr);

    /// @brief Destructor for teamdisplay.
    ~teamdisplay();

private slots:
    /**
     * @brief Validates form fields before accepting input.
     */
    void validateAndSubmit() {
        if (teamName->text().isEmpty() || stadiumName->text().isEmpty() || location->text().isEmpty() ||
            playingSurface->text().isEmpty() || distanceToCenterField->text().isEmpty() ||
            ballparkTypology->text().isEmpty() || roofType->text().isEmpty()) {
            QMessageBox::warning(this, "Validation Error", "All fields must be filled.");
            return;
        }

        // bool isNumeric;
        // distanceToCenterField->text().toInt(&isNumeric);
        // if (!isNumeric) {
        //     QMessageBox::warning(this, "Validation Error", "Distance to center field must be numeric.");
        //     return;
        // }
        accept();
    }

    /**
     * @brief Updates UI when the current record changes.
     * @param index Index of the current record.
     */
    void onRecordChanged(int index);

    /**
     * @brief Slot called when OK/Accept button is clicked.
     */
    void on_buttonBox_accepted();

    /**
     * @brief Slot called when Cancel/Reject button is clicked.
     */
    void on_buttonBox_rejected();

    /**
     * @brief Marks or reverts deletion of the current team.
     */
    void on_pb_delete_clicked();

    /**
     * @brief Opens map display to edit stadium location.
     */
    void on_pb_location_clicked();

    /**
     * @brief Removes the selected souvenir entry.
     */
    void on_pb_souvenir_delete_clicked();

    /**
     * @brief Adds a new souvenir entry associated with the current team.
     */
    void on_pb_souvenir_add_clicked();

private:
    Ui::teamdisplay *ui;                ///< Pointer to UI components.
    QLineEdit *teamName;                ///< Input for team name.
    QLineEdit *stadiumName;             ///< Input for stadium name.
    QSpinBox *seatingCapacity;          ///< Input for stadium seating capacity.
    QLineEdit *location;                ///< Input for stadium location.
    QLineEdit *playingSurface;          ///< Input for playing surface type.
    QComboBox *league;                  ///< Selector for league type (American/National).
    QSpinBox *dateOpened;              ///< Input for stadium opening year.
    QLineEdit *distanceToCenterField;   ///< Input for distance to center field.
    QLineEdit *ballparkTypology;        ///< Input for ballpark typology.
    QLineEdit *roofType;                ///< Input for roof type.
    QSqlTableModel *teamModel;          ///< SQL model for team data.
    QDataWidgetMapper *mapper;          ///< Maps widgets to SQL data fields.
    QSqlTableModel *souvenirModel;      ///< SQL model for souvenir data.
};

#include <QStyledItemDelegate>
#include <QLocale>

/**
 * @class CurrencyDelegate
 * @brief Custom delegate to format price values as currency in table views.
 */
class CurrencyDelegate : public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    /**
     * @brief Formats display text for a cell as US currency.
     * @param value The data to format.
     * @param locale The locale to use for formatting.
     * @return Formatted currency string.
     */
    QString displayText(const QVariant &value, const QLocale &locale) const override {
        // Format as USD currency with 2 decimal places
        double amount = value.toDouble();
        return locale.toCurrencyString(amount, "$", 2);
    }
};

#endif // TEAMDISPLAY_H
