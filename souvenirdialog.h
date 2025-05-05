#ifndef SOUVENIRDIALOG_H
#define SOUVENIRDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QHeaderView>
#include "utility.h"
#include <set>
#include <map>

/**
 * @class SouvenirDialog
 * @brief Dialog for managing souvenir data.
 *
 * This class provides an interface for viewing, adding, editing, and deleting
 * souvenirs associated with different colleges.
 */
class SouvenirDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Constructs the SouvenirDialog.
     * @param souvenirList Reference to a list of souvenir data.
     * @param parent Optional parent widget.
     */
    explicit SouvenirDialog(std::vector<SouvenirData>& souvenirList, QWidget* parent = nullptr);

    /**
     * @brief Retrieves the updated souvenir list.
     * @return A vector of updated souvenir data.
     */
    std::vector<SouvenirData> getUpdatedSouvenirList() const;

private slots:
    /// @brief Handles the event when the college selection changes.
    void onCollegeSelectionChanged(int index);

    /// @brief Handles the event when a new row is added.
    void onAddRow();

    /// @brief Handles the event when a row is deleted.
    void onDeleteRow();

    /// @brief Handles the event when the save button is clicked.
    void onSave();

    /**
     * @brief Handles changes made to table cells.
     * @param row The row where the change occurred.
     * @param column The column where the change occurred.
     */
    void onCellChanged(int row, int column);

private:
    /// @brief Populates the college dropdown list.
    void populateColleges();

    /**
     * @brief Loads souvenirs for the selected college.
     * @param college The name of the selected college.
     */
    void loadSouvenirs(const std::string& college);

    /// @brief Stores the current souvenirs before switching colleges.
    void storeCurrentSouvenirs();

    /**
     * @brief Validates a specific row in the table.
     * @param row The row index to validate.
     * @return True if the row is valid, false otherwise.
     */
    bool validateRow(int row);

    /**
     * @brief Formats the cost field for a given row.
     * @param row The row index to format.
     */
    void formatCostField(int row);

    QComboBox* collegeComboBox; /**< Dropdown list for selecting a college. */
    QTableWidget* tableWidget; /**< Table widget for displaying souvenirs. */
    QPushButton* addButton; /**< Button for adding a new row. */
    QPushButton* deleteButton; /**< Button for deleting a selected row. */
    QPushButton* saveButton; /**< Button for saving the updated souvenir list. */

    std::vector<SouvenirData>& souvenirList; /**< Reference to the list of souvenir data. */
    std::map<std::string, std::vector<SouvenirData>> collegeSouvenirs; /**< Map storing souvenirs by college. */
    std::string currentCollege; /**< The currently selected college. */
};

#endif // SOUVENIRDIALOG_H
