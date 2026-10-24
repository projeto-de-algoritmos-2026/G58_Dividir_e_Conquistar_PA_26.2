#include <gtest/gtest.h>

#include <algorithm>
#include <vector>
#include <set>
#include <stdexcept>
#include <utility>

#include "modelo/geometria/DivideConquerDelaunay.hpp"
#include "modelo/geometria/DelaunayGraph.hpp"

using modelo::geometria::DivideConquerDelaunay;
using modelo::geometria::ITriangulator;
using modelo::geometria::DelaunayGraph;
using modelo::geometria::Point2D;
using modelo::geometria::Edge;

using Arestas = std::set<std::pair<int, int>>;

static Arestas arestasDe(const std::vector<Point2D>& pontos) {
    DivideConquerDelaunay dc;
    ITriangulator& triangulator = dc;

    DelaunayGraph graph = triangulator.triangulate(pontos);
    std::vector<Edge> edges = graph.edges();

    Arestas resultado;

    for (const Edge& edge : edges) {
        resultado.insert({edge.u, edge.v});
    }

    return resultado;
}


TEST(DivideConquerDelaunayTest, DoisPontosTest) {

    EXPECT_EQ(arestasDe({{0.0, 0.0}, {1.0, 0.0}}), (Arestas{{0, 1}}));

}