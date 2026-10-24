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

TEST(DivideConquerDelaunayTest, TresPontosTest) {
    EXPECT_EQ(arestasDe({{0.0, 0.0}, {1.0, -1.0}, {2.0, 0.0}}), (Arestas{{0.0, 1.0}, {0.0, 2.0}, {1.0, 2.0}}));

    EXPECT_EQ(arestasDe({{0.0, 0.0}, {1.0, 1.0}, {2.0, 0.0}}), (Arestas{{0.0, 1.0}, {0.0, 2.0}, {1.0, 2.0}}));

    EXPECT_EQ(arestasDe({{0.0, 0.0}, {1.0, 1.0}, {2.0, 2.0}}), (Arestas{{0.0, 1.0}, {1.0, 2.0}}));

    EXPECT_EQ(arestasDe({{2.0, 2.0}, {0.0, 0.0}, {1.0, 1.0}}), (Arestas{{0.0, 2.0}, {1.0, 2.0}}));
}

TEST(DivideConquerDelaunayTest, InferiorTangent) {
    EXPECT_EQ(arestasDe({{0.0, 0.0}, {1.0, 3.0}, {2.0, 0.0}, {1.0, -3.0}}).count({2, 3}), 1u);
}

TEST(DivideConquerDelaunayTest, Pipa) {
    EXPECT_EQ(arestasDe({{0, 0}, {1, 3}, {2, 0}, {1, -3}}),
        (Arestas{{0, 1}, {1, 2}, {2, 3}, {0, 3}, {0,2}}));
}

TEST(DivideConquerDelaunayTest, PontoDentro) {
    EXPECT_EQ(arestasDe({{0, 0}, {4, 0}, {2, 4}, {2, 1}}),
        (Arestas{{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}}));
}

TEST(DivideConquerDelaunayTest, Quadrado) {
    Arestas a = arestasDe({{0, 0}, {1, 0}, {1, 1}, {0, 1}});
    EXPECT_EQ(a.size(), 5u);
    EXPECT_EQ(a.count({0, 1}), 1u);
    EXPECT_EQ(a.count({1, 2}), 1u);
    EXPECT_EQ(a.count({2, 3}), 1u);
    EXPECT_EQ(a.count({0, 3}), 1u);
}

TEST(DivideConquerDelaunay, ApagarArestaDireta) {
    EXPECT_EQ(arestasDe({{1, 6}, {3, 2}, {4, 6}, {5, 5}, {6, 2}}),
        (Arestas{{0, 1}, {0, 2}, {1, 2}, {1, 3}, { 1, 4}, {2, 3}, {3, 4}}));
}

TEST(DivideConquerDelaunay, ApagarArestaEsquerda) {
    EXPECT_EQ(arestasDe({{1, 3}, {2, 5}, {3, 6}, {4, 2}, {5, 0}, {6, 0}}),
        (Arestas{{0, 1}, {0, 3}, {0, 4}, { 1, 2}, {1, 3}, {2, 3}, {2, 5}, {3, 4}, {3, 5}, {4, 5}}));
}

TEST(DivideConquerDelaunayTest, Grade10x10) {
    std::vector<Point2D> pontos;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            pontos.push_back({static_cast<double>(i), static_cast<double>(j)});
        }
    }

    EXPECT_EQ(arestasDe(pontos).size(), 261u);
}

TEST(DivideConquerDelaunayTest, PontoRepetido) {
    EXPECT_THROW(arestasDe({{1, 1}, {0, 0}, {1, 1}}), std::invalid_argument);
}