#ifndef MERGEDTABLEVIEW_H
#define MERGEDTABLEVIEW_H

#include <QDebug>
#include <QApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <QTableView>
#include <QStandardItemModel>
#include <QPainter>
#include <QHeaderView>

/**
 * @class MergedTableView
 * @brief A custom QTableView with merged cells functionality.
 *
 * This class extends QTableView to provide the ability to merge visually
 * consecutive cells in a specified column when they contain the same value.
 * It is useful for grouped visual representation of table data.
 */
class MergedTableView : public QTableView {
public:
    /**
     * @brief Constructs a MergedTableView object.
     * @param parent Optional parent widget.
     */
    MergedTableView(QWidget *parent = nullptr) : QTableView(parent) {}

protected:
    /**
     * @brief Overrides the paint event to visually merge cells in a column.
     * @param event The paint event.
     *
     * This function traverses the table and, for a specified column, merges
     * rows with identical consecutive values by drawing them as a single block.
     */
    void paintEvent(QPaintEvent *event) override {
        QTableView::paintEvent(event);

        QPainter painter(viewport());
        painter.setRenderHint(QPainter::Antialiasing);

        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(this->model());
        if (!model) return;

        int mergeColumn = 0; // Column index to apply merging
        QString previousValue;
        int mergeStartRow = -1;

        for (int row = 0; row < model->rowCount(); ++row) {
            QString currentValue = model->item(row, mergeColumn) ? model->item(row, mergeColumn)->text() : "";

            if (row == 0) {
                previousValue = currentValue;
                mergeStartRow = 0;
                continue;
            }

            if (currentValue.isEmpty()) {
                continue;
            }

            if (currentValue != previousValue) {
                if (row - mergeStartRow > 1) {
                    mergeCells(mergeColumn, mergeStartRow, row - 1);
                }
                previousValue = currentValue;
                mergeStartRow = row;
            } else if (row == model->rowCount() - 1) {
                if (row - mergeStartRow + 1 > 1) {
                    mergeCells(mergeColumn, mergeStartRow, row);
                }
            }
        }
    }

private:
    /**
     * @brief Merges consecutive cells in a column by clearing duplicates.
     * @param column The column to apply merging to.
     * @param startRow The starting row index for the merge.
     * @param endRow The ending row index for the merge.
     *
     * This function keeps the content in the top cell and clears the data
     * in subsequent cells to simulate a merged cell appearance.
     */
    void mergeCells(int column, int startRow, int endRow) {
        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(this->model());
        if (!model) return;

        QModelIndex topIndex = model->index(startRow, column);
        QModelIndex bottomIndex = model->index(endRow, column);
        QRect mergeRect = visualRect(topIndex).united(visualRect(bottomIndex));

        model->setData(topIndex, model->data(topIndex).toString());
        for (int row = startRow + 1; row <= endRow; ++row) {
            model->setData(model->index(row, column), "");
        }
    }
};

#endif // MERGEDTABLEVIEW_H
