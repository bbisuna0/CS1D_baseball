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
#include <qcombobox.h>
#include "stadium.h"
#include "display_souvenirs.h"

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

        bool isNumeric;
        distanceToCenterField->text().toInt(&isNumeric);
        if (!isNumeric) {
            QMessageBox::warning(this, "Validation Error", "Distance to center field must be numeric.");
            return;
        }
        accept();
    }

    //void on_pushButton_3_clicked(const QComboBox* obj); //for displaying souvenirs

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
    //display_souvenirs *display_items;
};

#endif // TEAMDISPLAY_H
