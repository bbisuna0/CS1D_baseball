#include "tripplanner.h"

// Constructor
TripPlanner::TripPlanner()
    : totalDistance(0.0)
{
    // Add all stadium connections
    stadiums.add_undirected_edge("Angel Stadium", "Petco Park", 110);
    stadiums.add_undirected_edge("Angel Stadium", "Dodger Stadium", 50);
    stadiums.add_undirected_edge("Busch Stadium", "Minute Maid Park", 680);
    stadiums.add_undirected_edge("Busch Stadium", "Great American Ball Park", 310);
    stadiums.add_undirected_edge("Busch Stadium", "Target Field", 465);
    stadiums.add_undirected_edge("Busch Stadium", "Kauffman Stadium", 235);
    stadiums.add_undirected_edge("Chase Field", "Coors Field", 580);
    stadiums.add_undirected_edge("Chase Field", "Globe Life Park in Arlington", 870);
    stadiums.add_undirected_edge("Chase Field", "Minute Maid Park", 1115);
    stadiums.add_undirected_edge("Chase Field", "Oakland–Alameda County Coliseum", 650);
    stadiums.add_undirected_edge("Chase Field", "Petco Park", 300);
    stadiums.add_undirected_edge("Citi Field", "Fenway Park", 195);
    stadiums.add_undirected_edge("Citi Field", "Yankee Stadium", 50);
    stadiums.add_undirected_edge("Citizens Bank Park", "Yankee Stadium", 80);
    stadiums.add_undirected_edge("Citizens Bank Park", "Oriole Park at Camden Yards", 90);
    stadiums.add_undirected_edge("Comerica Park", "Guaranteed Rate Field", 240);
    stadiums.add_undirected_edge("Comerica Park", "Rogers Centre", 210);
    stadiums.add_undirected_edge("Comerica Park", "Progressive Field", 90);
    stadiums.add_undirected_edge("Coors Field", "Kauffman Stadium", 560);
    stadiums.add_undirected_edge("Coors Field", "Globe Life Park in Arlington", 650);
    stadiums.add_undirected_edge("Coors Field", "Petco Park", 830);
    stadiums.add_undirected_edge("Dodger Stadium", "Target Field", 1500);
    stadiums.add_undirected_edge("Dodger Stadium", "Oakland–Alameda County Coliseum", 340);
    stadiums.add_undirected_edge("Fenway Park", "Marlins Park", 1255);
    stadiums.add_undirected_edge("Fenway Park", "Rogers Centre", 430);
    stadiums.add_undirected_edge("Globe Life Park in Arlington", "Kauffman Stadium", 460);
    stadiums.add_undirected_edge("Globe Life Park in Arlington", "SunTrust Park", 740);
    stadiums.add_undirected_edge("Globe Life Park in Arlington", "Minute Maid Park", 230);
    stadiums.add_undirected_edge("Globe Life Park in Arlington", "Coors Field", 650);
    stadiums.add_undirected_edge("Great American Ball Park", "PNC Park", 260);
    stadiums.add_undirected_edge("Great American Ball Park", "Progressive Field", 225);
    stadiums.add_undirected_edge("Great American Ball Park", "Guaranteed Rate Field", 250);
    stadiums.add_undirected_edge("Great American Ball Park", "Tropicana Field", 790);
    stadiums.add_undirected_edge("Great American Ball Park", "SunTrust Park", 375);
    stadiums.add_undirected_edge("Guaranteed Rate Field", "Wrigley Field", 50);
    stadiums.add_undirected_edge("Kauffman Stadium", "Wrigley Field", 415);
    stadiums.add_undirected_edge("Marlins Park", "SunTrust Park", 600);
    stadiums.add_undirected_edge("Marlins Park", "Tropicana Field", 210);
    stadiums.add_undirected_edge("Marlins Park", "Nationals Park", 930);
    stadiums.add_undirected_edge("Marlins Park", "Minute Maid Park", 965);
    stadiums.add_undirected_edge("Miller Park", "Rogers Centre", 430);
    stadiums.add_undirected_edge("Miller Park", "Wrigley Field", 80);
    stadiums.add_undirected_edge("Miller Park", "Target Field", 300);
    stadiums.add_undirected_edge("Minute Maid Park", "Tropicana Field", 790);
    stadiums.add_undirected_edge("Minute Maid Park", "Busch Stadium", 680);
    stadiums.add_undirected_edge("Nationals Park", "Oriole Park at Camden Yards", 50);
    stadiums.add_undirected_edge("Nationals Park", "PNC Park", 195);
    stadiums.add_undirected_edge("Nationals Park", "SunTrust Park", 560);
    stadiums.add_undirected_edge("Oakland–Alameda County Coliseum", "Oracle Park", 50);
    stadiums.add_undirected_edge("Oracle Park", "Safeco Field", 680);
    stadiums.add_undirected_edge("Oriole Park at Camden Yards", "Citizens Bank Park", 90);
    stadiums.add_undirected_edge("Petco Park", "Coors Field", 830);
    stadiums.add_undirected_edge("PNC Park", "Progressive Field", 115);
    stadiums.add_undirected_edge("PNC Park", "Great American Ball Park", 260);
    stadiums.add_undirected_edge("PNC Park", "Yankee Stadium", 315);
    stadiums.add_undirected_edge("Progressive Field", "PNC Park", 115);
    stadiums.add_undirected_edge("Progressive Field", "Comerica Park", 90);
    stadiums.add_undirected_edge("Rogers Centre", "Safeco Field", 2070);
    stadiums.add_undirected_edge("Safeco Field", "Target Field", 1390);
    stadiums.add_undirected_edge("SunTrust Park", "Great American Ball Park", 375);
    stadiums.add_undirected_edge("Target Field", "Busch Stadium", 465);
    stadiums.add_undirected_edge("Target Field", "Miller Park", 300);
    stadiums.add_undirected_edge("Tropicana Field", "Minute Maid Park", 790);
    stadiums.add_undirected_edge("Wrigley Field", "Guaranteed Rate Field", 50);
    stadiums.add_undirected_edge("Wrigley Field", "Miller Park", 80);
    stadiums.add_undirected_edge("Wrigley Field", "Kauffman Stadium", 415);
    stadiums.add_undirected_edge("Yankee Stadium", "Citizens Bank Park", 80);
    stadiums.add_undirected_edge("Yankee Stadium", "Citi Field", 50);

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

Graph<std::string>* TripPlanner::getGraph() {
    return &stadiums;
}
