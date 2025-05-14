#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <QWidget>

namespace Ui {
class maintenance;
}

/**
 * @class maintenance
 * @brief A QWidget interface for performing administrative database operations.
 *
 * This class provides administrative tools such as resetting data tables,
 * bulk populating the database, displaying stadium maps, and uploading images.
 * It is accessible only to admin-level users.
 */
class maintenance : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the maintenance window and initializes the UI.
     * @param parent Optional parent widget.
     */
    explicit maintenance(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the maintenance class.
     */
    ~maintenance();

private slots:
    /**
     * @brief Closes the maintenance window.
     */
    void on_pb_exit_clicked();

    /**
     * @brief Resets core tables (teams, distances, souvenirs) to default content.
     */
    void on_pb_content_default_clicked();

    /**
     * @brief Displays stadium distance data.
     * @note This function is currently not implemented.
     */
    void on_pb_display_distances_clicked();

    /**
     * @brief Performs bulk insertion of predefined teams, locations, and distances.
     */
    void on_pb_bulk_update_clicked();

    /**
     * @brief Opens a file dialog to upload team or stadium images.
     * @note This function is currently not implemented.
     */
    void on_pb_upload_image_clicked();

    /**
     * @brief Fully resets all application data, including user-related tables.
     */
    void on_pb_full_reset_clicked();

    /**
     * @brief Launches the stadium map display window.
     */
    void on_pb_res1_clicked();

private:
    Ui::maintenance *ui; /**< UI pointer to the maintenance layout. */
};

#endif // MAINTENANCE_H
