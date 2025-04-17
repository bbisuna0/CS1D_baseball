#include "display_dfs_bfs.h"
#include "ui_display_dfs_bfs.h"

display_dfs::display_dfs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::display_dfs)
{
    ui->setupUi(this);
}

display_dfs::~display_dfs()
{
    delete ui;
}

void display_dfs::setOutput(const QString& text)
{
    ui->textEdit->setPlainText(text);
}
