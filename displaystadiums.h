#ifndef DISPLAYSTADIUMS_H
#define DISPLAYSTADIUMS_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class DisplayStadiums;
}

/**
 * @class DisplayStadiums
 * @brief UI class to display and sort MLB stadium information in a table view.
 *
 * Provides filtering and sorting options for stadiums based on name, typology,
 * roof type, opening date, seating capacity, and center field distance.
 */
class DisplayStadiums : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the DisplayStadiums widget and initializes the UI.
     * @param parent Pointer to the parent widget.
     */
    explicit DisplayStadiums(QWidget *parent = nullptr);

    /**
     * @brief Destructor for DisplayStadiums.
     */
    ~DisplayStadiums();

private slots:
    /**
     * @brief Closes the stadium display window.
     */
    void on_pb_exit_clicked();

    /**
     * @brief Displays all stadiums sorted alphabetically by stadium name.
     */
    void on_pb_stadium_clicked();

    /**
     * @brief Displays stadiums sorted by ballpark typology.
     */
    void on_pb_typology_clicked();

    /**
     * @brief Filters and displays only stadiums with an open roof type,
     *        appending a row showing the count.
     */
    void on_pb_openroof_clicked();

    /**
     * @brief Sorts stadiums chronologically by their date of opening.
     */
    void on_pb_chronological_clicked();

    /**
     * @brief Sorts stadiums by seating capacity and appends a row with total capacity.
     */
    void on_pb_seating_clicked();

    /**
     * @brief Filters and displays stadium(s) with the largest center field distance.
     */
    void on_pb_largedistance_clicked();

    /**
     * @brief Filters and displays stadium(s) with the smallest center field distance.
     */
    void on_pb_smalldistance_clicked();

private:
    Ui::DisplayStadiums *ui;       /**< UI pointer for the form. */
    QSqlTableModel *team_data;     /**< Model for managing team and stadium data from the database. */
};

#endif // DISPLAYSTADIUMS_H
