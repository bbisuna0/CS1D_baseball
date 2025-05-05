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

class teamdisplay : public QDialog
{
    Q_OBJECT

public:
    explicit teamdisplay(QWidget *parent = nullptr);
    ~teamdisplay();

private slots:
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

    void onRecordChanged(int index);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_pb_delete_clicked();

    void on_pb_location_clicked();

    void on_pb_souvenir_delete_clicked();

    void on_pb_souvenir_add_clicked();

private:
    Ui::teamdisplay *ui;
    QLineEdit *teamName;
    QLineEdit *stadiumName;
    QSpinBox *seatingCapacity;
    QLineEdit *location;
    QLineEdit *playingSurface;
    QComboBox *league;
    QSpinBox *dateOpened;
    QLineEdit *distanceToCenterField;
    QLineEdit *ballparkTypology;
    QLineEdit *roofType;
    QSqlTableModel *teamModel;
    QDataWidgetMapper *mapper;
    // QSqlRelationalTableModel *souvenirModel;
    QSqlTableModel *souvenirModel;
};

#include <QStyledItemDelegate>
#include <QLocale>

class CurrencyDelegate : public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    QString displayText(const QVariant &value, const QLocale &locale) const override {
        // Format as USD currency with 2 decimal places
        double amount = value.toDouble();
        return locale.toCurrencyString(amount, "$", 2);
    }
};

#endif // TEAMDISPLAY_H
