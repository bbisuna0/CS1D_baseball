#ifndef TRIPDISPLAY_H
#define TRIPDISPLAY_H

#include <QDialog>
#include "utility.h"
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "db.h"

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
     * @brief Constructs the tripdisplay dialog with trip data.
     * @param data Reference to a list of colleges visited.
     * @param totalDistance The total distance traveled during the trip.
     * @param souvenirListParm Reference to a list of souvenirs purchased.
     * @param parent Optional parent widget.
     */
    explicit tripdisplay(const std::vector<TripEntry>& data, float totalDistance,
                         bool souvenirDisp = true, QWidget *parent = nullptr);

    /// @brief Destructor for tripdisplay.
    ~tripdisplay();

private slots:
    /// @brief Handles the event when the accept button is clicked.
    void on_buttonBox_accepted();

    /// @brief Handles the event when the Saddleback button is clicked.
    void on_saddlebackPB_clicked();

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
        QRegExp regex(QRegExp::escape(filterString), Qt::CaseSensitive, QRegExp::FixedString);
        proxyModel->setFilterKeyColumn(0); // Filter by column 0
        proxyModel->setFilterRegExp(regex);
    }

private:
    Ui::tripdisplay *ui;  /**< Pointer to the UI instance of the tripdisplay dialog. */
    QStandardItemModel *model; /**< Pointer to the table model for displaying trip details. */
    QSortFilterProxyModel *proxyModel; /**< Proxy model for filtering trip data. */
    std::vector<SouvenirData> souvenirList; /**< List of souvenirs purchased during the trip. */
};

#endif // TRIPDISPLAY_H
