#include <gtest/gtest.h>

#include <algorithm>
#include <vector>
#include <set>
#include <stdexcept>

#include "modelo/geometria/KruskalClusterer.hpp"

using modelo::geometria::KruskalClusterer;
using modelo::geometria::Point2D;
using modelo::geometria::Edge;
using modelo::geometria::DelaunayGraph;
using modelo::geometria::IClusterer;

TEST(KruskalTest, ExtremesTest) {

    std::vector<Point2D> pontos = {{0,0}, {1, 0}, {2,0}, {3,0}};

    DelaunayGraph grafo(4);
    grafo.addEdge(0, 1);
    grafo.addEdge(1, 2);
    grafo.addEdge(2, 3);

    KruskalClusterer kruskal;
    IClusterer& clusterer = kruskal;

    std::vector<int> rotulos = clusterer.cluster(pontos, grafo, 4);

    ASSERT_EQ(rotulos.size(), 4u);

    std::set<int> rotuloSet;
    rotuloSet.insert(rotulos.begin(), rotulos.end());

    ASSERT_EQ(rotuloSet.size(), 4u);

    std::vector<int> juntos = clusterer.cluster(pontos, grafo, 1);

    ASSERT_EQ(juntos.size(), 4u);

    std::set<int> juntoSet;
    juntoSet.insert(juntos.begin(), juntos.end());

    ASSERT_EQ(juntoSet.size(), 1u);

}

// C5: dois triângulos distantes, ligados por uma única aresta longa.
// Com k = 2, o Kruskal tem que cortar justamente essa aresta (ligação simples).
TEST(KruskalTest, DoisGruposSeparados) {

    std::vector<Point2D> pontos = {
        {0, 0}, {0, 1}, {1, 0},          // triângulo perto de (0,0): pontos 0, 1, 2
        {10, 10}, {10, 11}, {11, 10}     // triângulo perto de (10,10): pontos 3, 4, 5
    };

    DelaunayGraph grafo(6);
    grafo.addEdge(0, 1);
    grafo.addEdge(1, 2);
    grafo.addEdge(0, 2);
    grafo.addEdge(3, 4);
    grafo.addEdge(4, 5);
    grafo.addEdge(3, 5);
    grafo.addEdge(2, 3);                 // a ponte longa entre os dois triângulos

    KruskalClusterer kruskal;
    IClusterer& clusterer = kruskal;

    std::vector<int> rotulos = clusterer.cluster(pontos, grafo, 2);

    ASSERT_EQ(rotulos.size(), 6u);

    // Cada triângulo inteiro no mesmo grupo...
    EXPECT_EQ(rotulos[0], rotulos[1]);
    EXPECT_EQ(rotulos[1], rotulos[2]);
    EXPECT_EQ(rotulos[3], rotulos[4]);
    EXPECT_EQ(rotulos[4], rotulos[5]);

    // ...e os dois triângulos em grupos diferentes.
    EXPECT_NE(rotulos[0], rotulos[3]);
}

// C6: para todo k de 1 até n, aparecem exatamente k rótulos, todos entre 0 e k - 1.
TEST(KruskalTest, RotulosVaoDeZeroAteKMenosUm) {

    std::vector<Point2D> pontos = {{0, 0}, {1, 0}, {3, 0}, {7, 0}, {8, 1}, {20, 5}};

    // Um caminho 0-1-2-3-4-5 e mais duas arestas, para o grafo não ser só uma linha.
    DelaunayGraph grafo(6);
    for (int i = 0; i + 1 < 6; i++) {
        grafo.addEdge(i, i + 1);
    }
    grafo.addEdge(0, 2);
    grafo.addEdge(3, 5);

    KruskalClusterer kruskal;
    IClusterer& clusterer = kruskal;

    for (int k = 1; k <= 6; k++) {
        std::vector<int> rotulos = clusterer.cluster(pontos, grafo, k);

        ASSERT_EQ(rotulos.size(), 6u) << "k = " << k;

        std::set<int> distintos(rotulos.begin(), rotulos.end());
        EXPECT_EQ(distintos.size(), static_cast<size_t>(k)) << "k = " << k;

        for (int rotulo : rotulos) {
            EXPECT_GE(rotulo, 0) << "k = " << k;
            EXPECT_LT(rotulo, k) << "k = " << k;
        }
    }
}

// C7: k fora do intervalo [1, n] tem que lançar std::invalid_argument.
TEST(KruskalTest, KInvalidoLancaExcecao) {

    std::vector<Point2D> pontos = {{0, 0}, {1, 0}, {2, 0}};

    DelaunayGraph grafo(3);
    grafo.addEdge(0, 1);
    grafo.addEdge(1, 2);

    KruskalClusterer kruskal;
    IClusterer& clusterer = kruskal;

    EXPECT_THROW(clusterer.cluster(pontos, grafo, 0), std::invalid_argument);
    EXPECT_THROW(clusterer.cluster(pontos, grafo, 4), std::invalid_argument);
}
