#ifndef PURCHASESOUVENIRS_H
#define PURCHASESOUVENIRS_H

#include <QDialog>
#include "utility.h"
#include <QStandardItemModel>
#include "mergedtableview.h"
#include <QStyledItemDelegate>
#include <QSpinBox>


/**
 * @class SpinBoxDelegate
 * @brief A delegate for editing table cells using a QSpinBox.
 *
 * This delegate is used to edit integer values (quantities) in a table view using a spin box widget.
 */
class SpinBoxDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    /**
     * @brief Constructs the SpinBoxDelegate.
     * @param parent Optional parent object.
     */
    explicit SpinBoxDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}


    /**
     * @brief Creates the spin box editor widget.
     * @param parent Parent widget.
     * @return A pointer to the created spin box.
     */
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex&) const override {
        QSpinBox* editor = new QSpinBox(parent);
        editor->setMinimum(0);  // Allow 0 and positive numbers only
        editor->setMaximum(1000);  // Arbitrary high limit
        return editor;
    }


    /**
     * @brief Sets the editor's value from the model data.
     * @param editor The spin box widget.
     * @param index The model index containing the data.
     */
    void setEditorData(QWidget* editor, const QModelIndex& index) const override {
        int value = index.model()->data(index, Qt::EditRole).toInt();
        QSpinBox* spinBox = qobject_cast<QSpinBox*>(editor);
        spinBox->setValue(value);
    }


    /**
     * @brief Updates the model with the editor's value.
     * @param editor The spin box widget.
     * @param model The model to update.
     * @param index The index in the model to update.
     */
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override {
        QSpinBox* spinBox = qobject_cast<QSpinBox*>(editor);
        model->setData(index, spinBox->value(), Qt::EditRole);
    }


    /**
     * @brief Sets the geometry of the editor widget.
     * @param editor The spin box widget.
     * @param option The style options.
     * @param index The index in the model.
     */
    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex&) const override {
        editor->setGeometry(option.rect);
    }
};

namespace Ui {
class purchasesouvenirs;
}

/**
 * @class purchasesouvenirs
 * @brief Dialog for purchasing souvenirs.
 *
 * This class provides a user interface for selecting and purchasing souvenirs.
 * It manages a list of available souvenir purchases and allows users to specify quantities.
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

    /**
     * @brief Destructor for purchasesouvenirs.
     */
    ~purchasesouvenirs();

private slots:
    /**
     * @brief Slot triggered when the "Purchase" button is clicked.
     * Displays the purchase summary dialog.
     */
    void on_purchaseButton_clicked();

private:
    Ui::purchasesouvenirs *ui; /**< Pointer to the UI instance of the purchasesouvenirs dialog. */
    QStandardItemModel *model; /**< Pointer to the table model for displaying souvenir purchases. */
};

#endif // PURCHASESOUVENIRS_H
