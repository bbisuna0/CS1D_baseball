#ifndef DISPLAYTEAMS_H
#define DISPLAYTEAMS_H

#include <QWidget>
#include <QSqlTableModel>
#include "db.h"

namespace Ui {
class DisplayTeams;
}

/**
 * @class DisplayTeams
 * @brief UI class to display and filter MLB teams by league using a QSqlTableModel.
 *
 * Allows sorting teams, viewing all teams, or filtering by American/National leagues.
 */
class DisplayTeams : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the DisplayTeams widget and initializes the UI.
     * @param parent Pointer to the parent widget.
     */
    explicit DisplayTeams(QWidget *parent = nullptr);

    /**
     * @brief Destructor for DisplayTeams. Cleans up UI and model.
     */
    ~DisplayTeams();

private slots:
    /**
     * @brief Displays all MLB teams sorted alphabetically by team name.
     */
    void on_pb_mlbteam_clicked();

    /**
     * @brief Closes the team display window.
     */
    void on_pb_exit_clicked();

    /**
     * @brief Filters and displays only teams in the American League.
     */
    void on_pb_american_clicked();

    /**
     * @brief Filters and displays only teams in the National League.
     */
    void on_pb_national_clicked();

private:
    Ui::DisplayTeams *ui;         /**< UI pointer for the form. */
    QSqlTableModel *team_data;    /**< SQL model for team data bound to the teams table. */
};

#endif // DISPLAYTEAMS_H
