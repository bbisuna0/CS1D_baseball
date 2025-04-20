#include "plantour.h"
#include "ui_plantour.h"
#include "teamdisplay.h"
#include "graph.h"


plantour::plantour(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::plantour)
{
    ui->setupUi(this);
}

plantour::~plantour()
{
    delete ui;
}

void plantour::on_pb_exit_clicked()
{
    close();
}


void plantour::on_pb_team_details_clicked()
{
    teamdisplay *teamWin = new teamdisplay();
    teamWin->show();
}


void plantour::on_pushButton_clicked()
{
    print_ptr  = new display_dfs(this);
    print_ptr->show();

    QTextEdit* outputWidget = print_ptr->findChild<QTextEdit*>("textEdit");
    // Run DFS from Oracle Park and collect output into buffer
    plan.getGraph()->run_dfs("Oracle Park", outputWidget);
}


void plantour::on_pushButton_2_clicked()
{
    print_ptr  = new display_dfs(this);
    print_ptr->show();

    QTextEdit* outputWidget = print_ptr->findChild<QTextEdit*>("textEdit");
    // Run DFS from Oracle Park and collect output into buffer
    plan.getGraph()->run_bfs("Target Field", outputWidget);
}

