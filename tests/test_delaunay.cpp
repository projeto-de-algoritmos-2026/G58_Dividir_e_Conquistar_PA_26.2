#include <gtest/gtest.h>

#include <algorithm>
#include <vector>
#include <set>
#include <stdexcept>

#include "modelo/geometria/DivideConquerDelaunay.hpp"
#include "modelo/geometria/DelaunayGraph.hpp"

using modelo::geometria::DivideConquerDelaunay;
using modelo::geometria::ITriangulator;
using modelo::geometria::DelaunayGraph;
using modelo::geometria::Point2D;
using modelo::geometria::Edge;


TEST(DivideConquerDelaunayTest, TriangulateTest) {

    DivideConquerDelaunay dc;
    ITriangulator& triangulator = dc;

    std::vector<Point2D> points = {{0.0, 0.0}, {1.0, 0.0}};

    DelaunayGraph graph = triangulator.triangulate(points);
    std::vector<Edge> edges = graph.edges();

    ASSERT_EQ(edges.size(), 1u);
    EXPECT_EQ(edges[0].u, 0);
    EXPECT_EQ(edges[0].v, 1);

}