#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <QWidget>

namespace Ui {
class maintenance;
}

class maintenance : public QWidget
{
    Q_OBJECT

public:
    explicit maintenance(QWidget *parent = nullptr);
    ~maintenance();

private slots:
    void on_pb_exit_clicked();

    void on_pb_content_default_clicked();

    void on_pb_display_distances_clicked();

    void on_pb_bulk_update_clicked();

    void on_pb_upload_image_clicked();

    void on_pb_full_reset_clicked();

    void on_pb_res1_clicked();

private:
    Ui::maintenance *ui;
};

#endif // MAINTENANCE_H
