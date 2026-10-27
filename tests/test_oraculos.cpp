#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
#include <utility>
#include <vector>

#include "BruteForce.hpp"
#include "modelo/geometria/DelaunayGraph.hpp"
#include "modelo/geometria/DivideConquerDelaunay.hpp"
#include "modelo/geometria/Edge.hpp"
#include "modelo/geometria/KruskalClusterer.hpp"
#include "modelo/geometria/UnionFind.hpp"
#include "modelo/geometria/predicates.h"

using modelo::geometria::DelaunayGraph;
using modelo::geometria::DivideConquerDelaunay;
using modelo::geometria::Edge;
using modelo::geometria::ITriangulator;
using modelo::geometria::KruskalClusterer;
using modelo::geometria::Point2D;
using modelo::geometria::UnionFind;
using forca_bruta::Arestas;

static Arestas arestasDe(const DelaunayGraph& grafo) {
    Arestas resultado;
    for (const Edge& e : grafo.edges()) {
        resultado.insert({e.u, e.v});
    }
    return resultado;
}

static DelaunayGraph triangular(const std::vector<Point2D>& pontos) {
    DivideConquerDelaunay dc;
    ITriangulator& triangulador = dc;
    return triangulador.triangulate(pontos);
}

TEST(OraculoDelaunay, IgualForcaBrutaEmConjuntosAleatorios) {
    for (int t = 0; t < 200; t++) {
        int n = 3 + t % 28;
        std::vector<Point2D> pontos = forca_bruta::pontosAleatorios(n, 100 + t);

        ASSERT_EQ(arestasDe(triangular(pontos)), forca_bruta::delaunay(pontos))
            << "conjunto " << t << " com " << n << " pontos";
    }
}

TEST(OraculoDelaunay, MenorArestaEhParMaisProximo) {
    std::vector<Point2D> pontos = forca_bruta::pontosAleatorios(2000, 7);

    double menor = std::numeric_limits<double>::infinity();
    std::pair<int, int> parDaTriangulacao = {-1, -1};
    for (const Edge& e : triangular(pontos).edges()) {
        double d = forca_bruta::distancia(pontos[e.u], pontos[e.v]);
        if (d < menor) {
            menor = d;
            parDaTriangulacao = {e.u, e.v};
        }
    }

    EXPECT_EQ(parDaTriangulacao, forca_bruta::parMaisProximo(pontos));
}

TEST(OraculoDelaunay, VizinhoMaisProximoEstaNoGrafo) {
    std::vector<Point2D> pontos = forca_bruta::pontosAleatorios(500, 8);
    DelaunayGraph grafo = triangular(pontos);

    for (int i = 0; i < static_cast<int>(pontos.size()); i++) {
        int maisProximo = forca_bruta::vizinhoMaisProximo(pontos, i);
        const std::vector<int>& vizinhos = grafo.neighbors(i);

        EXPECT_NE(std::find(vizinhos.begin(), vizinhos.end(), maisProximo), vizinhos.end())
            << "ponto " << i;
    }
}

TEST(OraculoKruskal, ArvoreSobreDelaunayTemOPesoDoPrim) {
    std::vector<Point2D> pontos = forca_bruta::pontosAleatorios(200, 9);

    std::vector<Edge> arestas = triangular(pontos).edges();
    for (Edge& e : arestas) {
        e.length = forca_bruta::distancia(pontos[e.u], pontos[e.v]);
    }
    std::sort(arestas.begin(), arestas.end());

    UnionFind uf(static_cast<int>(pontos.size()));
    double peso = 0.0;
    for (const Edge& e : arestas) {
        if (uf.unite(e.u, e.v)) {
            peso += e.length;
        }
    }

    EXPECT_EQ(uf.count(), 1);
    EXPECT_NEAR(peso, forca_bruta::pesoArvorePrim(pontos), 1e-9);
}

TEST(OraculoKruskal, MesmosClustersQueNoGrafoCompleto) {
    const int n = 200;
    std::vector<Point2D> pontos = forca_bruta::pontosAleatorios(n, 10);

    DelaunayGraph completo(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            completo.addEdge(i, j);
        }
    }

    KruskalClusterer kruskal;
    std::vector<int> naDelaunay = kruskal.cluster(pontos, triangular(pontos), 10);
    std::vector<int> noCompleto = kruskal.cluster(pontos, completo, 10);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ASSERT_EQ(naDelaunay[i] == naDelaunay[j], noCompleto[i] == noCompleto[j])
                << "pontos " << i << " e " << j;
        }
    }
}

TEST(OraculoPredicados, QuaseColineares) {
    exactinit();
    const double passo = std::ldexp(1.0, -53);
    double q[2] = {12.0, 12.0};
    double r[2] = {24.0, 24.0};

    int errosDaContaDireta = 0;
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            double p[2] = {0.5 + i * passo, 0.5 + j * passo};
            int esperado = (j > i) - (j < i);

            double exato = orient2d(p, q, r);
            EXPECT_EQ((exato > 0) - (exato < 0), esperado) << "i = " << i << ", j = " << j;

            double direto = (p[0] - r[0]) * (q[1] - r[1]) - (p[1] - r[1]) * (q[0] - r[0]);
            if ((direto > 0) - (direto < 0) != esperado) {
                errosDaContaDireta++;
            }
        }
    }

    EXPECT_GT(errosDaContaDireta, 0);
    RecordProperty("errosDaContaDireta", errosDaContaDireta);
}
