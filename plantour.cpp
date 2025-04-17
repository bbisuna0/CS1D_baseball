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

    Graph<std::string> g;

    // Add all stadium connections
    g.add_undirected_edge("Angel Stadium", "Petco Park", 110);
    g.add_undirected_edge("Angel Stadium", "Dodger Stadium", 50);
    g.add_undirected_edge("Busch Stadium", "Minute Maid Park", 680);
    g.add_undirected_edge("Busch Stadium", "Great American Ball Park", 310);
    g.add_undirected_edge("Busch Stadium", "Target Field", 465);
    g.add_undirected_edge("Busch Stadium", "Kauffman Stadium", 235);
    g.add_undirected_edge("Chase Field", "Coors Field", 580);
    g.add_undirected_edge("Chase Field", "Globe Life Park in Arlington", 870);
    g.add_undirected_edge("Chase Field", "Minute Maid Park", 1115);
    g.add_undirected_edge("Chase Field", "Oakland–Alameda County Coliseum", 650);
    g.add_undirected_edge("Chase Field", "Petco Park", 300);
    g.add_undirected_edge("Citi Field", "Fenway Park", 195);
    g.add_undirected_edge("Citi Field", "Yankee Stadium", 50);
    g.add_undirected_edge("Citizens Bank Park", "Yankee Stadium", 80);
    g.add_undirected_edge("Citizens Bank Park", "Oriole Park at Camden Yards", 90);
    g.add_undirected_edge("Comerica Park", "Guaranteed Rate Field", 240);
    g.add_undirected_edge("Comerica Park", "Rogers Centre", 210);
    g.add_undirected_edge("Comerica Park", "Progressive Field", 90);
    g.add_undirected_edge("Coors Field", "Kauffman Stadium", 560);
    g.add_undirected_edge("Coors Field", "Globe Life Park in Arlington", 650);
    g.add_undirected_edge("Coors Field", "Petco Park", 830);
    g.add_undirected_edge("Dodger Stadium", "Target Field", 1500);
    g.add_undirected_edge("Dodger Stadium", "Oakland–Alameda County Coliseum", 340);
    g.add_undirected_edge("Fenway Park", "Marlins Park", 1255);
    g.add_undirected_edge("Fenway Park", "Rogers Centre", 430);
    g.add_undirected_edge("Globe Life Park in Arlington", "Kauffman Stadium", 460);
    g.add_undirected_edge("Globe Life Park in Arlington", "SunTrust Park", 740);
    g.add_undirected_edge("Globe Life Park in Arlington", "Minute Maid Park", 230);
    g.add_undirected_edge("Globe Life Park in Arlington", "Coors Field", 650);
    g.add_undirected_edge("Great American Ball Park", "PNC Park", 260);
    g.add_undirected_edge("Great American Ball Park", "Progressive Field", 225);
    g.add_undirected_edge("Great American Ball Park", "Guaranteed Rate Field", 250);
    g.add_undirected_edge("Great American Ball Park", "Tropicana Field", 790);
    g.add_undirected_edge("Great American Ball Park", "SunTrust Park", 375);
    g.add_undirected_edge("Guaranteed Rate Field", "Wrigley Field", 50);
    g.add_undirected_edge("Kauffman Stadium", "Wrigley Field", 415);
    g.add_undirected_edge("Marlins Park", "SunTrust Park", 600);
    g.add_undirected_edge("Marlins Park", "Tropicana Field", 210);
    g.add_undirected_edge("Marlins Park", "Nationals Park", 930);
    g.add_undirected_edge("Marlins Park", "Minute Maid Park", 965);
    g.add_undirected_edge("Miller Park", "Rogers Centre", 430);
    g.add_undirected_edge("Miller Park", "Wrigley Field", 80);
    g.add_undirected_edge("Miller Park", "Target Field", 300);
    g.add_undirected_edge("Minute Maid Park", "Tropicana Field", 790);
    g.add_undirected_edge("Minute Maid Park", "Busch Stadium", 680);
    g.add_undirected_edge("Nationals Park", "Oriole Park at Camden Yards", 50);
    g.add_undirected_edge("Nationals Park", "PNC Park", 195);
    g.add_undirected_edge("Nationals Park", "SunTrust Park", 560);
    g.add_undirected_edge("Oakland–Alameda County Coliseum", "Oracle Park", 50);
    g.add_undirected_edge("Oracle Park", "Safeco Field", 680);
    g.add_undirected_edge("Oriole Park at Camden Yards", "Citizens Bank Park", 90);
    g.add_undirected_edge("Petco Park", "Coors Field", 830);
    g.add_undirected_edge("PNC Park", "Progressive Field", 115);
    g.add_undirected_edge("PNC Park", "Great American Ball Park", 260);
    g.add_undirected_edge("PNC Park", "Yankee Stadium", 315);
    g.add_undirected_edge("Progressive Field", "PNC Park", 115);
    g.add_undirected_edge("Progressive Field", "Comerica Park", 90);
    g.add_undirected_edge("Rogers Centre", "Safeco Field", 2070);
    g.add_undirected_edge("Safeco Field", "Target Field", 1390);
    g.add_undirected_edge("SunTrust Park", "Great American Ball Park", 375);
    g.add_undirected_edge("Target Field", "Busch Stadium", 465);
    g.add_undirected_edge("Target Field", "Miller Park", 300);
    g.add_undirected_edge("Tropicana Field", "Minute Maid Park", 790);
    g.add_undirected_edge("Wrigley Field", "Guaranteed Rate Field", 50);
    g.add_undirected_edge("Wrigley Field", "Miller Park", 80);
    g.add_undirected_edge("Wrigley Field", "Kauffman Stadium", 415);
    g.add_undirected_edge("Yankee Stadium", "Citizens Bank Park", 80);
    g.add_undirected_edge("Yankee Stadium", "Citi Field", 50);

    QTextEdit* outputWidget = print_ptr->findChild<QTextEdit*>("textEdit");
    // Run DFS from Oracle Park and collect output into buffer
    g.run_dfs("Oracle Park", outputWidget);
}


void plantour::on_pushButton_2_clicked()
{
    print_ptr  = new display_dfs(this);
    print_ptr->show();

    Graph<std::string> g;

    // Add all stadium connections
    g.add_undirected_edge("Angel Stadium", "Petco Park", 110);
    g.add_undirected_edge("Angel Stadium", "Dodger Stadium", 50);
    g.add_undirected_edge("Busch Stadium", "Minute Maid Park", 680);
    g.add_undirected_edge("Busch Stadium", "Great American Ball Park", 310);
    g.add_undirected_edge("Busch Stadium", "Target Field", 465);
    g.add_undirected_edge("Busch Stadium", "Kauffman Stadium", 235);
    g.add_undirected_edge("Chase Field", "Coors Field", 580);
    g.add_undirected_edge("Chase Field", "Globe Life Park in Arlington", 870);
    g.add_undirected_edge("Chase Field", "Minute Maid Park", 1115);
    g.add_undirected_edge("Chase Field", "Oakland–Alameda County Coliseum", 650);
    g.add_undirected_edge("Chase Field", "Petco Park", 300);
    g.add_undirected_edge("Citi Field", "Fenway Park", 195);
    g.add_undirected_edge("Citi Field", "Yankee Stadium", 50);
    g.add_undirected_edge("Citizens Bank Park", "Yankee Stadium", 80);
    g.add_undirected_edge("Citizens Bank Park", "Oriole Park at Camden Yards", 90);
    g.add_undirected_edge("Comerica Park", "Guaranteed Rate Field", 240);
    g.add_undirected_edge("Comerica Park", "Rogers Centre", 210);
    g.add_undirected_edge("Comerica Park", "Progressive Field", 90);
    g.add_undirected_edge("Coors Field", "Kauffman Stadium", 560);
    g.add_undirected_edge("Coors Field", "Globe Life Park in Arlington", 650);
    g.add_undirected_edge("Coors Field", "Petco Park", 830);
    g.add_undirected_edge("Dodger Stadium", "Target Field", 1500);
    g.add_undirected_edge("Dodger Stadium", "Oakland–Alameda County Coliseum", 340);
    g.add_undirected_edge("Fenway Park", "Marlins Park", 1255);
    g.add_undirected_edge("Fenway Park", "Rogers Centre", 430);
    g.add_undirected_edge("Globe Life Park in Arlington", "Kauffman Stadium", 460);
    g.add_undirected_edge("Globe Life Park in Arlington", "SunTrust Park", 740);
    g.add_undirected_edge("Globe Life Park in Arlington", "Minute Maid Park", 230);
    g.add_undirected_edge("Globe Life Park in Arlington", "Coors Field", 650);
    g.add_undirected_edge("Great American Ball Park", "PNC Park", 260);
    g.add_undirected_edge("Great American Ball Park", "Progressive Field", 225);
    g.add_undirected_edge("Great American Ball Park", "Guaranteed Rate Field", 250);
    g.add_undirected_edge("Great American Ball Park", "Tropicana Field", 790);
    g.add_undirected_edge("Great American Ball Park", "SunTrust Park", 375);
    g.add_undirected_edge("Guaranteed Rate Field", "Wrigley Field", 50);
    g.add_undirected_edge("Kauffman Stadium", "Wrigley Field", 415);
    g.add_undirected_edge("Marlins Park", "SunTrust Park", 600);
    g.add_undirected_edge("Marlins Park", "Tropicana Field", 210);
    g.add_undirected_edge("Marlins Park", "Nationals Park", 930);
    g.add_undirected_edge("Marlins Park", "Minute Maid Park", 965);
    g.add_undirected_edge("Miller Park", "Rogers Centre", 430);
    g.add_undirected_edge("Miller Park", "Wrigley Field", 80);
    g.add_undirected_edge("Miller Park", "Target Field", 300);
    g.add_undirected_edge("Minute Maid Park", "Tropicana Field", 790);
    g.add_undirected_edge("Minute Maid Park", "Busch Stadium", 680);
    g.add_undirected_edge("Nationals Park", "Oriole Park at Camden Yards", 50);
    g.add_undirected_edge("Nationals Park", "PNC Park", 195);
    g.add_undirected_edge("Nationals Park", "SunTrust Park", 560);
    g.add_undirected_edge("Oakland–Alameda County Coliseum", "Oracle Park", 50);
    g.add_undirected_edge("Oracle Park", "Safeco Field", 680);
    g.add_undirected_edge("Oriole Park at Camden Yards", "Citizens Bank Park", 90);
    g.add_undirected_edge("Petco Park", "Coors Field", 830);
    g.add_undirected_edge("PNC Park", "Progressive Field", 115);
    g.add_undirected_edge("PNC Park", "Great American Ball Park", 260);
    g.add_undirected_edge("PNC Park", "Yankee Stadium", 315);
    g.add_undirected_edge("Progressive Field", "PNC Park", 115);
    g.add_undirected_edge("Progressive Field", "Comerica Park", 90);
    g.add_undirected_edge("Rogers Centre", "Safeco Field", 2070);
    g.add_undirected_edge("Safeco Field", "Target Field", 1390);
    g.add_undirected_edge("SunTrust Park", "Great American Ball Park", 375);
    g.add_undirected_edge("Target Field", "Busch Stadium", 465);
    g.add_undirected_edge("Target Field", "Miller Park", 300);
    g.add_undirected_edge("Tropicana Field", "Minute Maid Park", 790);
    g.add_undirected_edge("Wrigley Field", "Guaranteed Rate Field", 50);
    g.add_undirected_edge("Wrigley Field", "Miller Park", 80);
    g.add_undirected_edge("Wrigley Field", "Kauffman Stadium", 415);
    g.add_undirected_edge("Yankee Stadium", "Citizens Bank Park", 80);
    g.add_undirected_edge("Yankee Stadium", "Citi Field", 50);

    QTextEdit* outputWidget = print_ptr->findChild<QTextEdit*>("textEdit");
    // Run DFS from Oracle Park and collect output into buffer
    g.run_bfs("Target Field", outputWidget);
}

