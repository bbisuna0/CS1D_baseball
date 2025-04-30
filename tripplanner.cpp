#include "tripplanner.h"

// Constructor
TripPlanner::TripPlanner()
    : totalDistance(0.0)
{
    // Add all stadium connections
    stadiums.add_undirected_edges("Angel Stadium", "Petco Park", 110);
    stadiums.add_undirected_edges("Angel Stadium", "Dodger Stadium", 50);
    stadiums.add_undirected_edges("Busch Stadium", "Minute Maid Park", 680);
    stadiums.add_undirected_edges("Busch Stadium", "Great American Ball Park", 310);
    stadiums.add_undirected_edges("Busch Stadium", "Target Field", 465);
    stadiums.add_undirected_edges("Busch Stadium", "Kauffman Stadium", 235);
    stadiums.add_undirected_edges("Chase Field", "Coors Field", 580);
    stadiums.add_undirected_edges("Chase Field", "Globe Life Park in Arlington", 870);
    stadiums.add_undirected_edges("Chase Field", "Minute Maid Park", 1115);
    stadiums.add_undirected_edges("Chase Field", "Oakland–Alameda County Coliseum", 650);
    stadiums.add_undirected_edges("Chase Field", "Petco Park", 300);
    stadiums.add_undirected_edges("Citi Field", "Fenway Park", 195);
    stadiums.add_undirected_edges("Citi Field", "Yankee Stadium", 50);
    stadiums.add_undirected_edges("Citizens Bank Park", "Yankee Stadium", 80);
    stadiums.add_undirected_edges("Citizens Bank Park", "Oriole Park at Camden Yards", 90);
    stadiums.add_undirected_edges("Comerica Park", "Guaranteed Rate Field", 240);
    stadiums.add_undirected_edges("Comerica Park", "Rogers Centre", 210);
    stadiums.add_undirected_edges("Comerica Park", "Progressive Field", 90);
    stadiums.add_undirected_edges("Coors Field", "Kauffman Stadium", 560);
    stadiums.add_undirected_edges("Coors Field", "Globe Life Park in Arlington", 650);
    stadiums.add_undirected_edges("Coors Field", "Petco Park", 830);
    stadiums.add_undirected_edges("Dodger Stadium", "Target Field", 1500);
    stadiums.add_undirected_edges("Dodger Stadium", "Oakland–Alameda County Coliseum", 340);
    stadiums.add_undirected_edges("Fenway Park", "Marlins Park", 1255);
    stadiums.add_undirected_edges("Fenway Park", "Rogers Centre", 430);
    stadiums.add_undirected_edges("Globe Life Park in Arlington", "Kauffman Stadium", 460);
    stadiums.add_undirected_edges("Globe Life Park in Arlington", "SunTrust Park", 740);
    stadiums.add_undirected_edges("Globe Life Park in Arlington", "Minute Maid Park", 230);
    stadiums.add_undirected_edges("Globe Life Park in Arlington", "Coors Field", 650);
    stadiums.add_undirected_edges("Great American Ball Park", "PNC Park", 260);
    stadiums.add_undirected_edges("Great American Ball Park", "Progressive Field", 225);
    stadiums.add_undirected_edges("Great American Ball Park", "Guaranteed Rate Field", 250);
    stadiums.add_undirected_edges("Great American Ball Park", "Tropicana Field", 790);
    stadiums.add_undirected_edges("Great American Ball Park", "SunTrust Park", 375);
    stadiums.add_undirected_edges("Guaranteed Rate Field", "Wrigley Field", 50);
    stadiums.add_undirected_edges("Kauffman Stadium", "Wrigley Field", 415);
    stadiums.add_undirected_edges("Marlins Park", "SunTrust Park", 600);
    stadiums.add_undirected_edges("Marlins Park", "Tropicana Field", 210);
    stadiums.add_undirected_edges("Marlins Park", "Nationals Park", 930);
    stadiums.add_undirected_edges("Marlins Park", "Minute Maid Park", 965);
    stadiums.add_undirected_edges("Miller Park", "Rogers Centre", 430);
    stadiums.add_undirected_edges("Miller Park", "Wrigley Field", 80);
    stadiums.add_undirected_edges("Miller Park", "Target Field", 300);
    stadiums.add_undirected_edges("Minute Maid Park", "Tropicana Field", 790);
    stadiums.add_undirected_edges("Minute Maid Park", "Busch Stadium", 680);
    stadiums.add_undirected_edges("Nationals Park", "Oriole Park at Camden Yards", 50);
    stadiums.add_undirected_edges("Nationals Park", "PNC Park", 195);
    stadiums.add_undirected_edges("Nationals Park", "SunTrust Park", 560);
    stadiums.add_undirected_edges("Oakland–Alameda County Coliseum", "Oracle Park", 50);
    stadiums.add_undirected_edges("Oracle Park", "Safeco Field", 680);
    stadiums.add_undirected_edges("Oriole Park at Camden Yards", "Citizens Bank Park", 90);
    stadiums.add_undirected_edges("Petco Park", "Coors Field", 830);
    stadiums.add_undirected_edges("PNC Park", "Progressive Field", 115);
    stadiums.add_undirected_edges("PNC Park", "Great American Ball Park", 260);
    stadiums.add_undirected_edges("PNC Park", "Yankee Stadium", 315);
    stadiums.add_undirected_edges("Progressive Field", "PNC Park", 115);
    stadiums.add_undirected_edges("Progressive Field", "Comerica Park", 90);
    stadiums.add_undirected_edges("Rogers Centre", "Safeco Field", 2070);
    stadiums.add_undirected_edges("Safeco Field", "Target Field", 1390);
    stadiums.add_undirected_edges("SunTrust Park", "Great American Ball Park", 375);
    stadiums.add_undirected_edges("Target Field", "Busch Stadium", 465);
    stadiums.add_undirected_edges("Target Field", "Miller Park", 300);
    stadiums.add_undirected_edges("Tropicana Field", "Minute Maid Park", 790);
    stadiums.add_undirected_edges("Wrigley Field", "Guaranteed Rate Field", 50);
    stadiums.add_undirected_edges("Wrigley Field", "Miller Park", 80);
    stadiums.add_undirected_edges("Wrigley Field", "Kauffman Stadium", 415);
    stadiums.add_undirected_edges("Yankee Stadium", "Citizens Bank Park", 80);
    stadiums.add_undirected_edges("Yankee Stadium", "Citi Field", 50);

}

// Placeholder for actual shortest trip logic
void TripPlanner::planShortestTrip() {
    // TODO: Implement Dijkstra or MST
}

// Sum from Graph's adjacency matrix (optional real logic)
double TripPlanner::calculateTotalDistance() {
    // Here we would normally compute real trip distances
    return totalDistance;
}

double TripPlanner::getTotalDistance() const {
    return totalDistance;
}

void TripPlanner::performDFS(const std::string& start_vertex, QTextEdit* output) {
    stadiums.run_dfs(start_vertex, output);
}

void TripPlanner::performBFS(const std::string& start_vertex, QTextEdit* output) {
    stadiums.run_bfs(start_vertex, output);
}

void TripPlanner::performDijkstra(const std::string& start_vertex, QTextEdit* output)
{
    stadiums.Dijkstra(start_vertex, output);
}
void TripPlanner::performMST(const std::string& start_vertex, QTextEdit* output)
{
    stadiums.mst(start_vertex, output);
}

Graph<std::string>* TripPlanner::getGraph() {
    return &stadiums;
}
