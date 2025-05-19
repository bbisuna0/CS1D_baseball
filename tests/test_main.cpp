// test_main.cpp
#include <gtest/gtest.h>
#include "utility.h"
#include "db.h"

TEST(SampleTest, BasicAssertion) {
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/**
 * @file test_graphgreedythrough.cpp
 * @brief Unit tests for the GraphGreedyThrough class using Google Test.
 *
 * This file contains unit tests that verify the correctness of various pathfinding
 * strategies implemented in the GraphGreedyThrough class, including greedy vacation
 * routes, dream vacation routes, and BFS-based greedy traversals.
 */

/**
 * @file test_graphgreedythrough.cpp
 * @brief Unit tests for the GraphGreedyThrough class using Google Test.
 */


/**
 * @brief Creates a small triangle graph of stadiums for testing.
 * @return Initialized GraphGreedyThrough instance.
 */
GraphGreedyThrough createTestGraph() {
    std::vector<std::string> nodes = {"Marlins Park", "Yankee Stadium", "Fenway Park"};
    GraphGreedyThrough graph(nodes);
    graph.addEdge("Marlins Park", "Yankee Stadium", 10);
    graph.addEdge("Yankee Stadium", "Fenway Park", 5);
    graph.addEdge("Marlins Park", "Fenway Park", 15);
    return graph;
}

// /**
//  * @test GreedyVacationRouteOrderMatters
//  * @brief Tests greedy path selection with order-dependent destinations.
//  */
// TEST(GraphGreedyThroughTest, GreedyVacationRouteOrderMatters) {
//     auto graph = createTestGraph();

//     std::vector<std::string> destinations = {"Fenway Park", "Yankee Stadium"};
//     graph.greedyVacationRoute("Marlins Park", destinations);

//     EXPECT_EQ(graph.getTotalCost(), 15);

//     auto trips = graph.getTripDetails();
//     ASSERT_EQ(trips.size(), 2);

//     EXPECT_EQ(trips[0].origin.toStdString(), "Marlins Park");
//     EXPECT_EQ(trips[0].destination.toStdString(), "Yankee Stadium");
//     EXPECT_EQ(trips[0].distance, 10);

//     EXPECT_EQ(trips[1].origin.toStdString(), "Yankee Stadium");
//     EXPECT_EQ(trips[1].destination.toStdString(), "Fenway Park");
//     EXPECT_EQ(trips[1].distance, 5);
//     trips.clear();
// }

/**
 * @test DreamVacationRouteStrictOrder
 * @brief Ensures order is strictly followed in dream route.
 */
TEST(GraphGreedyThroughTest, DreamVacationRouteStrictOrder) {
    auto graph = createTestGraph();

    std::vector<std::string> destinations = {"Yankee Stadium", "Fenway Park"};
    graph.dreamVacationRoute("Marlins Park", destinations);

    EXPECT_EQ(graph.getTotalCost(), 15);

    auto trips = graph.getTripDetails();
    ASSERT_EQ(trips.size(), 2);

    EXPECT_EQ(trips[0].origin.toStdString(), "Marlins Park");
    EXPECT_EQ(trips[0].destination.toStdString(), "Yankee Stadium");
    EXPECT_EQ(trips[0].distance, 10);

    EXPECT_EQ(trips[1].origin.toStdString(), "Yankee Stadium");
    EXPECT_EQ(trips[1].destination.toStdString(), "Fenway Park");
    EXPECT_EQ(trips[1].distance, 5);
    trips.clear();
}

/**
 * @test GreedyRouteThroughBFS
 * @brief Verifies BFS-based greedy route traverses stadiums efficiently.
 */
TEST(GraphGreedyThroughTest, GreedyRouteThroughBFS) {
    auto graph = createTestGraph();

    std::vector<std::string> toVisit = {"Yankee Stadium", "Fenway Park"};
    graph.greedyRouteThroughStadiums("Marlins Park", toVisit);

    EXPECT_EQ(graph.getTotalCost(), 15);

    auto trips = graph.getTripDetails();
    ASSERT_EQ(trips.size(), 2);
}

/**
 * @test GreedyRouteUnreachableStadium
 * @brief Checks handling of a destination that doesn't exist in the graph.
 */
TEST(GraphGreedyThroughTest, GreedyRouteUnreachableStadium) {
    std::vector<std::string> nodes = {"Marlins Park", "Yankee Stadium"};
    GraphGreedyThrough graph(nodes);
    graph.addEdge("Marlins Park", "Yankee Stadium", 10);

    std::vector<std::string> toVisit = {"Fenway Park"}; // Not in graph

    testing::internal::CaptureStdout();
    graph.greedyRouteThroughStadiums("Marlins Park", toVisit);
    std::string output = testing::internal::GetCapturedStdout();

    // EXPECT_TRUE(output.find("Invalid destination") != std::string::npos ||
    //             output.find("No reachable") != std::string::npos);
    nodes.clear();
    toVisit.clear();
}


/**
 * @brief Test Kruskal's MST on a simple triangle graph.
 */
TEST(GraphMSTTest, KruskalMST_TriangleGraph) {
    std::vector<std::string> nodes = {"A", "B", "C"};
    GraphMST graph(nodes);

    // Construct a triangle
    graph.addEdge("A", "B", 4);
    graph.addEdge("A", "C", 3);
    graph.addEdge("B", "C", 2);

    graph.computeKruskalMST();

    EXPECT_EQ(graph.totalCost(), 5); // MST: edges B-C (2) and A-C (3)

    std::vector<TripEntry> result = graph.getTrips();

    std::vector<std::pair<std::string, std::string>> expected_edges = {
        {"B", "C"}, {"A", "C"}
    };

    std::vector<int> expected_distances = {2, 3};

    ASSERT_EQ(result.size(), 2);
    for (int i = 0; i < result.size(); ++i) {
        std::string u = result[i].origin.toStdString();
        std::string v = result[i].destination.toStdString();
        int dist = result[i].distance;

        // The MST edges can be in either order
        bool match = false;
        for (int j = 0; j < expected_edges.size(); ++j) {
            if (((u == expected_edges[j].first && v == expected_edges[j].second) ||
                 (v == expected_edges[j].first && u == expected_edges[j].second)) &&
                dist == expected_distances[j]) {
                match = true;
                break;
            }
        }
        EXPECT_TRUE(match);
    }
}

/**
 * @brief Helper to create a basic test graph with 4 stadiums.
 */
GraphDijkstra createBasicGraph() {
    std::vector<std::string> nodes = {"A", "B", "C", "D"};
    GraphDijkstra graph(nodes);
    graph.addEdge("A", "B", 3);
    graph.addEdge("B", "C", 4);
    graph.addEdge("A", "D", 10);
    graph.addEdge("C", "D", 2);
    return graph;
}

/**
 * @test DijkstraSingleSource
 * @brief Verifies basic Dijkstra computation from a single source.
 */
TEST(GraphDijkstraTest, DijkstraSingleSource) {
    auto graph = createBasicGraph();
    graph.dijkstra("A");

    auto trips = graph.getTrips();
    std::map<std::string, int> expectedDistances = {
        {"B", 3},
        {"C", 7}, // A -> B -> C
        {"D", 9}  // A -> B -> C -> D
    };

    for (const auto& trip : trips) {
        std::string dest = trip.destination.toStdString();
        if (dest.find(" -> ") == std::string::npos) continue; // Skip origin marker
        std::string finalNode = dest.substr(dest.rfind(" ") + 1);
        EXPECT_EQ(trip.distance, expectedDistances[finalNode]);
    }
}

/**
 * @test TraverseAllFromDijkstra
 * @brief Tests discovery traversal with Dijkstra.
 */
TEST(GraphDijkstraTest, TraverseAllFromDijkstra) {
    auto graph = createBasicGraph();
    testing::internal::CaptureStdout();
    graph.traverseAllFrom("A");
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Discovery Edge") != std::string::npos);
    //EXPECT_TRUE(output.find("Back Edge") != std::string::npos || output.find("Cross Edge") != std::string::npos);
    EXPECT_EQ(graph.totalCost(), 9);
}

/**
 * @test DijkstraOptimizedRoute
 * @brief Verifies shortest route computation through permutations.
 */
TEST(GraphDijkstraTest, DijkstraOptimizedRoute) {
    auto graph = createBasicGraph();
    std::vector<std::string> stadiums = {"A", "C", "D"};

    testing::internal::CaptureStdout();
    graph.dijkstraOptimizedRoute(stadiums);
    std::string output = testing::internal::GetCapturedStdout();

    auto trips = graph.getTrips();
    EXPECT_EQ(graph.totalCost(), 9); // A -> B -> C -> D

    ASSERT_EQ(trips.size(), 2);
    EXPECT_EQ(trips[0].origin.toStdString(), "A");
    EXPECT_EQ(trips[0].distance, 7); // A -> B -> C

    EXPECT_EQ(trips[1].origin.toStdString(), "C");
    EXPECT_EQ(trips[1].distance, 2); // C -> D
}
