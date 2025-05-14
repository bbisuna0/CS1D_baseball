#ifndef TRIPDISPLAY_H
#define TRIPDISPLAY_H

#include <QDialog>
#include "utility.h"
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "db.h"
#include <QRegularExpression>

namespace Ui {
class tripdisplay;
}

/**
 * @class tripdisplay
 * @brief Dialog for displaying trip details, including colleges visited and souvenirs purchased.
 *
 * This class provides an interface for displaying the trip's details, such as
 * the list of colleges visited, total distance traveled, and souvenirs purchased.
 */
class tripdisplay : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the tripdisplay dialog.
     * @param parent Optional parent widget.
     */
    explicit tripdisplay(QWidget *parent = nullptr);

    /**
     * @brief Constructs a tripdisplay dialog with provided trip data.
     * @param data Vector of trip entries (each with origin, destination, etc.)
     * @param totalDistance Total distance traveled in the trip.
     * @param souvenirDisp Whether to display the souvenir purchase option.
     * @param parent Optional parent widget.
     */
    explicit tripdisplay(const std::vector<TripEntry>& data, float totalDistance,
                         bool souvenirDisp = true, QWidget *parent = nullptr);

    /**
     * @brief Destructor for tripdisplay.
     */
    ~tripdisplay();

private slots:
    /**
     * @brief Slot triggered when the user accepts (OK) the dialog.
     */
    void on_buttonBox_accepted();

    /**
     * @brief Slot triggered to open the souvenir purchase dialog.
     */
    void on_saddlebackPB_clicked();

    /**
     * @brief Slot triggered to display the trip route on a graphical map.
     */
    void on_pbMap_clicked();

public slots:
    /**
     * @brief Filters the table based on user input.
     * @param filter The filter string used for searching.
     *
     * This function allows filtering of the trip data table based on the
     * provided search string.
     */
    void filterTable(QString filter) {
        QString filterString = filter;
        QString pattern = QRegularExpression::escape(filterString);
        QRegularExpression regex(pattern);
        //QRegExp regex(QRegExp::escape(filterString), Qt::CaseSensitive, QRegExp::FixedString);
        proxyModel->setFilterKeyColumn(0); // Filter by column 0
        //proxyModel->setFilterRegExp(regex);
        regex.setPatternOptions(QRegularExpression::NoPatternOption); // Case-sensitive
        proxyModel->setFilterRegularExpression(regex);
    }

    /**
     * @brief Checks if a given college name is present in the model.
     * @param model The QStandardItemModel containing the college data.
     * @param searchValue The college name to search for.
     * @return True if the college is found, otherwise false.
     */
    bool isCollegeMatch(QStandardItemModel* model, const QString& searchValue) {
        if (!model) return false;

        for (int row = 0; row < model->rowCount(); ++row) {
            QStandardItem* startItem = model->item(row, 0); // Column 0: collegeStart
            QStandardItem* endItem = model->item(row, 1);   // Column 1: collegeEnd

            if (startItem && startItem->text() == searchValue) {
                return true; // Match found
            } else if (endItem && endItem->text() == searchValue) {
                return true; // Match found
            }
        }
        return false; // No match found
    }

    /**
     * @brief Sets the list of teams involved in the trip.
     * @param list Vector of team names.
     */
    void setTeams(const std::vector<std::string>& list) {
        teams = list;
    }

private:
    Ui::tripdisplay *ui;  /**< Pointer to the UI instance of the tripdisplay dialog. */
    QStandardItemModel *model; /**< Pointer to the table model for displaying trip details. */
    QSortFilterProxyModel *proxyModel; /**< Proxy model for filtering trip data. */
    std::vector<SouvenirData> souvenirList; /**< List of souvenirs purchased during the trip. */
    std::vector<std::string> teams;
};

#endif // TRIPDISPLAY_H
