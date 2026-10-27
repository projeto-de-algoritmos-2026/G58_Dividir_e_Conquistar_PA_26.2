#ifndef TESTS_BRUTE_FORCE_HPP
#define TESTS_BRUTE_FORCE_HPP

#include <algorithm>
#include <cmath>
#include <limits>
#include <random>
#include <set>
#include <utility>
#include <vector>

#include "modelo/geometria/Point2D.hpp"
#include "modelo/geometria/predicates.h"

namespace forca_bruta {

using modelo::geometria::Point2D;
using Arestas = std::set<std::pair<int, int>>;

inline std::vector<Point2D> pontosAleatorios(int n, unsigned semente) {
    std::mt19937 gerador(semente);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    std::vector<Point2D> pontos;
    for (int i = 0; i < n; i++) {
        pontos.push_back({dist(gerador), dist(gerador)});
    }
    return pontos;
}

inline double distancia(const Point2D& a, const Point2D& b) {
    return std::hypot(a.x - b.x, a.y - b.y);
}

inline Arestas delaunay(const std::vector<Point2D>& p) {
    exactinit();
    int n = static_cast<int>(p.size());
    Arestas arestas;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                double a[2] = {p[i].x, p[i].y};
                double b[2] = {p[j].x, p[j].y};
                double c[2] = {p[k].x, p[k].y};

                double orientacao = orient2d(a, b, c);
                if (orientacao == 0.0) {
                    continue;
                }

                double* segundo = b;
                double* terceiro = c;
                if (orientacao < 0.0) {
                    std::swap(segundo, terceiro);
                }

                bool circuloVazio = true;
                for (int l = 0; l < n && circuloVazio; l++) {
                    if (l == i || l == j || l == k) {
                        continue;
                    }
                    double d[2] = {p[l].x, p[l].y};
                    if (incircle(a, segundo, terceiro, d) > 0.0) {
                        circuloVazio = false;
                    }
                }

                if (circuloVazio) {
                    arestas.insert({i, j});
                    arestas.insert({j, k});
                    arestas.insert({i, k});
                }
            }
        }
    }
    return arestas;
}

inline std::pair<int, int> parMaisProximo(const std::vector<Point2D>& p) {
    int n = static_cast<int>(p.size());
    double melhor = std::numeric_limits<double>::infinity();
    std::pair<int, int> par = {-1, -1};

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double d = distancia(p[i], p[j]);
            if (d < melhor) {
                melhor = d;
                par = {i, j};
            }
        }
    }
    return par;
}

inline int vizinhoMaisProximo(const std::vector<Point2D>& p, int i) {
    int n = static_cast<int>(p.size());
    double melhor = std::numeric_limits<double>::infinity();
    int vizinho = -1;

    for (int j = 0; j < n; j++) {
        if (j == i) {
            continue;
        }
        double d = distancia(p[i], p[j]);
        if (d < melhor) {
            melhor = d;
            vizinho = j;
        }
    }
    return vizinho;
}

inline double pesoArvorePrim(const std::vector<Point2D>& p) {
    int n = static_cast<int>(p.size());
    if (n == 0) {
        return 0.0;
    }

    std::vector<bool> naArvore(n, false);
    std::vector<double> custo(n, std::numeric_limits<double>::infinity());
    custo[0] = 0.0;
    double peso = 0.0;

    for (int passo = 0; passo < n; passo++) {
        int escolhido = -1;
        for (int v = 0; v < n; v++) {
            if (!naArvore[v] && (escolhido == -1 || custo[v] < custo[escolhido])) {
                escolhido = v;
            }
        }

        naArvore[escolhido] = true;
        peso += custo[escolhido];

        for (int v = 0; v < n; v++) {
            if (!naArvore[v]) {
                custo[v] = std::min(custo[v], distancia(p[escolhido], p[v]));
            }
        }
    }
    return peso;
}

}  // namespace forca_bruta

#endif
