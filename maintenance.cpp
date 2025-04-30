#include "maintenance.h"
#include "ui_maintenance.h"

maintenance::maintenance(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::maintenance)
{
    ui->setupUi(this);
}

maintenance::~maintenance()
{
    delete ui;
}

void maintenance::on_pb_exit_clicked()
{
    close();
}



void maintenance::on_pb_content_default_clicked()
{

}


void maintenance::on_pb_display_distances_clicked()
{

}


void maintenance::on_pb_bulk_update_clicked()
{

}


void maintenance::on_pb_upload_image_clicked()
{

}


void maintenance::on_pb_full_reset_clicked()
{

}

