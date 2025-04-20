#ifndef TRIPPLANNER_H
#define TRIPPLANNER_H

#include "graph.h"
#include <string>

class TripPlanner {
private:
    double totalDistance;
    Graph<std::string> stadiums;

public:
    // Constructor
    TripPlanner();

    // Main Features
    void planShortestTrip();
    double calculateTotalDistance();
    double getTotalDistance() const;

    // Traversals
    void performDFS(const std::string& start_vertex, QTextEdit* output);
    void performBFS(const std::string& start_vertex, QTextEdit* output);

    // Accessor
    Graph<std::string>* getGraph();
};

#endif // TRIPPLANNER_H
