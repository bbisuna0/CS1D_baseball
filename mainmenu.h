#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include "main.h"

/// Global instance representing the logged-in user.
extern User myUser;

namespace Ui {
class mainmenu;
}

/**
 * @class mainmenu
 * @brief The main menu interface for navigating core application features.
 *
 * This class provides buttons to access team details, plan stadium tours,
 * view team and stadium reports, and open the admin-only maintenance interface.
 */
class mainmenu : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the main menu and initializes UI components.
     * @param parent Optional parent widget.
     */
    explicit mainmenu(QWidget *parent = nullptr);

    /**
     * @brief Destructor for mainmenu. Cleans up UI resources.
     */
    ~mainmenu();

private slots:
    /**
     * @brief Closes the main menu window.
     */
    void on_pb_exit_clicked();

    /**
     * @brief Opens the team detail viewer.
     */
    void on_pb_team_details_clicked();

    /**
     * @brief Opens the vacation planning window.
     */
    void on_pb_plan_vacation_clicked();

    /**
     * @brief Opens the team report view.
     */
    void on_pb_team_report_clicked();

    /**
     * @brief Opens the stadium report view.
     */
    void on_pb_stadium_report_clicked();

    /**
     * @brief Opens the maintenance window for admin users.
     */
    void on_pb_maintenance_clicked();

private:
    Ui::mainmenu *ui;  /**< UI pointer to the mainmenu layout. */
};

#endif // MAINMENU_H
