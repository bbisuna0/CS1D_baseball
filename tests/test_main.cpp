// test_main.cpp
#include <gtest/gtest.h>
//#include "utility.h"

TEST(SampleTest, BasicAssertion) {
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// TEST(GreedyVacationRouteTest, Simple3StopPath) {
//     std::vector<std::string> cities = {"A", "B", "C"};

//     GraphDijkstra graph(cities);

// }
