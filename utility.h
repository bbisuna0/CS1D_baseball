#ifndef UTILITY_H
#define UTILITY_H

#include <QDebug>
#include <QApplication>
#include <QSql>
// #include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>

#include <QSqlDatabase>
#include <QTableView>
#include <QStandardItemModel>
#include <QPainter>
#include <QHeaderView>
#include <unordered_set>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QStringList>
#include <QString>
#include <vector>
#include <string>
#include <set>
#include <QLabel>
#include <QSqlTableModel>


// Function declarations
void createUserTable(); // QSqlDatabase &db
bool checkUserTable(); // check if user table exists
void addUser(int ID, QString username, QString password, bool admin); // add user data into database
bool checkPassword(QString uname, QString pass, bool &admin); // check if user table exists
bool tableExists(QSqlDatabase& db, const QString& tableName);
// class utility
// {
// public:
//     utility();
// };


/*

This works but creates a duplicate column with logos

#include <QSqlTableModel>
#include <QModelIndex>
#include <QPixmap>
#include <QIcon>
#include <QVariant>
#include <QString>
#include <QHash>

class TeamLogoModel : public QSqlTableModel
{
    Q_OBJECT

public:
    using QSqlTableModel::QSqlTableModel;

    TeamLogoModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase())
        : QSqlTableModel(parent, db), m_teamNameColumn(-1)
    {
    }

    void setTable(const QString &tableName) override
    {
        QSqlTableModel::setTable(tableName);
        select();
        // Find the column index for the "team_name" column
        for (int i = 0; i < columnCount(); ++i) {
            if (headerData(i, Qt::Horizontal).toString() == "team_name") {
                m_teamNameColumn = i;
                break;
            }
        }
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        if (role == Qt::DecorationRole && index.column() == 0) {
            if (m_teamNameColumn != -1) {
                QString teamName = QSqlTableModel::data(this->index(index.row(), m_teamNameColumn), Qt::DisplayRole).toString();
                if (!teamName.isEmpty()) {
                    if (!m_logoCache.contains(teamName)) {
                        QString logoPath = QString(":/logos/%1.png").arg(teamName.toLower().replace(' ', '-'));
                        QPixmap pixmap(logoPath);
                        if (!pixmap.isNull()) {
                            m_logoCache.insert(teamName, QIcon(pixmap));
                        } else {
                            m_logoCache.insert(teamName, QIcon()); // Store an empty icon if not found
                        }
                    }
                    return m_logoCache.value(teamName);
                }
            }
            return QVariant(); // Return an invalid QVariant if team name not found or column 0
        }
        return QSqlTableModel::data(index, role);
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return QSqlTableModel::columnCount(parent) + 1; // Add one column for the logo
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override
    {
        if (orientation == Qt::Horizontal && role == Qt::DisplayRole && section == 0) {
            return QString("Logo");
        }
        return QSqlTableModel::headerData(section - 1, orientation, role);
    }

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override
    {
        if (column == 0) {
            return createIndex(row, column);
        }
        return QSqlTableModel::index(row, column - 1, parent);
    }

    Qt::ItemFlags flags(const QModelIndex &index) const override
    {
        if (index.column() == 0) {
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
        }
        return QSqlTableModel::flags(index);
    }

private:
    int m_teamNameColumn;
    mutable QHash<QString, QIcon> m_logoCache;
};
*/

#include <QStyledItemDelegate>
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QSize>
#include <QString>
#include <QRect>
#include <QFontMetrics>

class TeamLogoDelegate : public QStyledItemDelegate
{
public:
    TeamLogoDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        if (index.column() == 0) {
            QString teamName = index.model()->data(index, Qt::DisplayRole).toString();
            if (!teamName.isEmpty()) {
                QString logoPath = QString(":/logos/%1.png").arg(teamName.toLower().replace(' ', '-'));
                QPixmap pixmap(logoPath);

                // Draw the background
                painter->save();
                painter->fillRect(option.rect, option.palette.base());
                painter->restore();

                QRect textRect = option.rect;
                QRect imageRect;
                int spacing = 5; // Adjust spacing as needed

                if (!pixmap.isNull()) {
                    int imageWidth = option.rect.height() - 2 * spacing; // Keep image size proportional to row height
                    imageRect = QRect(option.rect.left() + spacing,
                                      option.rect.top() + spacing,
                                      imageWidth,
                                      imageWidth);
                    textRect.setLeft(imageRect.right() + spacing);
                    painter->drawPixmap(imageRect, pixmap);
                }

                // Draw the text
                painter->save();
                painter->drawText(textRect, option.displayAlignment, teamName);
                painter->restore();
            } else {
                QStyledItemDelegate::paint(painter, option, index); // Default painting if team name is empty
            }
        } else {
            QStyledItemDelegate::paint(painter, option, index); // Default painting for other columns
        }
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        if (index.column() == 0) {
            QString teamName = index.model()->data(index, Qt::DisplayRole).toString();
            if (!teamName.isEmpty()) {
                QString logoPath = QString(":/logos/%1.png").arg(teamName.toLower().replace(' ', '-'));
                QPixmap pixmap(logoPath);
                QFontMetrics fm = option.fontMetrics;
                int textWidth = fm.horizontalAdvance(teamName);
                int imageHeight = option.rect.height();
                int spacing = 5;

                if (!pixmap.isNull()) {
                    return QSize(imageHeight + spacing + textWidth + 2 * spacing, imageHeight + 2 * spacing);
                } else {
                    return QSize(textWidth + 2 * spacing, fm.height() + 2 * spacing);
                }
            }
        }
        return QStyledItemDelegate::sizeHint(option, index);
    }
};
#endif // UTILITY_H
