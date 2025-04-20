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


void plantour::on_pb_stadium_report_clicked()
{
    print_ptr  = new display_dfs(this);  // or display_graph_algorithms if renamed
    print_ptr->show();

    // Find the QTextEdit named "textEdit" inside the UI
    QTextEdit* outputWidget = print_ptr->findChild<QTextEdit*>("textEdit");

    // Safety check in case textEdit was not found
    if (!outputWidget) {
        qWarning("Could not find QTextEdit named 'textEdit' in display window.");
        return;
    }

    // Clear any previous content before printing
    outputWidget->clear();

    // Run Dijkstra from "Oracle Park" and print to the QTextEdit
    plan.getGraph()->run_dijkstra("Marlins Park", outputWidget);
}

