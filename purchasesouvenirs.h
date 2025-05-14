#ifndef PURCHASESOUVENIRS_H
#define PURCHASESOUVENIRS_H

#include <QDialog>
#include "utility.h"
#include <QStandardItemModel>
#include "mergedtableview.h"


namespace Ui {
class purchasesouvenirs;
}

/**
 * @class purchasesouvenirs
 * @brief Dialog for purchasing souvenirs.
 *
 * This class provides a user interface for selecting and purchasing souvenirs.
 * It manages a list of available souvenir purchases and interacts with the UI.
 */
class purchasesouvenirs : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the purchasesouvenirs dialog.
     * @param parent Optional parent widget.
     */
    explicit purchasesouvenirs(QWidget *parent = nullptr);

    /**
     * @brief Constructs the purchasesouvenirs dialog with purchase data.
     * @param data Reference to a list of souvenir purchases.
     * @param parent Optional parent widget.
     */
    explicit purchasesouvenirs(const std::vector<SouvenirPurchase>& data, QWidget *parent = nullptr);

    /// @brief Destructor for purchasesouvenirs.
    ~purchasesouvenirs();

private slots:
    /// @brief Handles the event when the purchase button is clicked.
    void on_purchaseButton_clicked();

private:
    Ui::purchasesouvenirs *ui; /**< Pointer to the UI instance of the purchasesouvenirs dialog. */
    QStandardItemModel *model; /**< Pointer to the table model for displaying souvenir purchases. */
};

#endif // PURCHASESOUVENIRS_H
