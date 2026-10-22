#include <gtest/gtest.h>

#include <algorithm>
#include <utility>
#include <vector>

#include "modelo/geometria/DelaunayGraph.hpp"

using modelo::geometria::DelaunayGraph;
using modelo::geometria::Edge;

TEST(DelaunayGraphTest, MontagemDoGrafo) {

    DelaunayGraph graph(4);

    graph.addEdge(0, 1);
    graph.addEdge(1, 0);
    graph.addEdge(0, 1);
    graph.addEdge(2, 2);

    ASSERT_EQ(graph.neighbors(0), std::vector<int>{1});
    ASSERT_EQ(graph.neighbors(1), std::vector<int>{0});

    EXPECT_TRUE(graph.neighbors(2).empty());

    ASSERT_EQ(graph.size(), 4);

}

TEST(DelaunayGraphTest, VerificacaoDeEdges)
{
    // Triângulo 0-1-2 mais a ponta 2-3: 4 arestas no grafo inteiro.
    DelaunayGraph graph(4);

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(0, 2);

    graph.addEdge(2, 3);

    std::vector<Edge> arestas = graph.edges();

    // 1. Quantidade: 4, e não 8. Cada aresta está na lista das duas pontas,
    //    mas edges() deve devolvê-la uma vez só. O "4u" é um 4 sem sinal,
    //    do mesmo tipo que size() devolve.
    ASSERT_EQ(arestas.size(), 4u);

    // 2. Toda aresta sai com a ponta menor primeiro, e ainda sem comprimento.
    for (const Edge& e : arestas)
    {
        EXPECT_LT(e.u, e.v);
        EXPECT_EQ(e.length, 0.0);
    }

    // 3. Os pares certos, sem depender da ordem em que edges() devolve:
    //    copia cada aresta para um par (u, v), ordena e compara com o esperado.
    std::vector<std::pair<int, int>> pares;
    for (const Edge& e : arestas)
    {
        pares.push_back({e.u, e.v});
    }
    std::sort(pares.begin(), pares.end());

    // A lista esperada fica numa variável: assim as vírgulas não confundem a macro.
    std::vector<std::pair<int, int>> esperado = {{0, 1}, {0, 2}, {1, 2}, {2, 3}};
    EXPECT_EQ(pares, esperado);
}
