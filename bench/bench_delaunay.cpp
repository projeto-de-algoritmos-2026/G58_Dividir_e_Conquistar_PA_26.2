#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <functional>
#include <limits>
#include <random>
#include <string>
#include <vector>

#include "modelo/adaptadores/AcousticTranslator.hpp"
#include "modelo/adaptadores/CmuDictionary.hpp"
#include "modelo/geometria/DelaunayGraph.hpp"
#include "modelo/geometria/DivideConquerDelaunay.hpp"
#include "modelo/geometria/Edge.hpp"
#include "modelo/geometria/KruskalClusterer.hpp"
#include "modelo/geometria/UnionFind.hpp"
#include "modelo/nucleo/RhymeEngine.hpp"

using modelo::adaptadores::AcousticTranslator;
using modelo::adaptadores::CmuDictionary;
using modelo::geometria::DelaunayGraph;
using modelo::geometria::DivideConquerDelaunay;
using modelo::geometria::Edge;
using modelo::geometria::KruskalClusterer;
using modelo::geometria::Point2D;
using modelo::geometria::UnionFind;
using modelo::nucleo::RhymeEngine;

static const int REPETICOES = 5;
static const int K = 10;

static std::vector<Point2D> pontosAleatorios(int n, unsigned semente) {
    std::mt19937 gerador(semente);
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::vector<Point2D> pontos;
    for (int i = 0; i < n; i++) {
        pontos.push_back({dist(gerador), dist(gerador)});
    }
    return pontos;
}

static double distancia(const Point2D& a, const Point2D& b) {
    return std::hypot(a.x - b.x, a.y - b.y);
}

static double medir(const std::function<void()>& tarefa) {
    std::vector<double> tempos;
    for (int r = 0; r < REPETICOES; r++) {
        auto inicio = std::chrono::steady_clock::now();
        tarefa();
        auto fim = std::chrono::steady_clock::now();
        tempos.push_back(std::chrono::duration<double, std::milli>(fim - inicio).count());
    }
    std::sort(tempos.begin(), tempos.end());
    return tempos[tempos.size() / 2];
}

static std::vector<int> kruskalNoGrafoCompleto(const std::vector<Point2D>& p, int k) {
    int n = static_cast<int>(p.size());
    std::vector<Edge> arestas;
    arestas.reserve(static_cast<size_t>(n) * (n - 1) / 2);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            arestas.push_back({i, j, distancia(p[i], p[j])});
        }
    }
    std::sort(arestas.begin(), arestas.end());

    UnionFind uf(n);
    for (const Edge& e : arestas) {
        if (uf.count() == k) {
            break;
        }
        uf.unite(e.u, e.v);
    }

    std::vector<int> rotulos(n);
    for (int i = 0; i < n; i++) {
        rotulos[i] = uf.find(i);
    }
    return rotulos;
}

static double distancia2(const Point2D& a, const Point2D& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx * dx + dy * dy;
}

static double parMaisProximoForcaBruta(const std::vector<Point2D>& p) {
    double melhor = std::numeric_limits<double>::infinity();
    for (size_t i = 0; i < p.size(); i++) {
        for (size_t j = i + 1; j < p.size(); j++) {
            melhor = std::min(melhor, distancia2(p[i], p[j]));
        }
    }
    return std::sqrt(melhor);
}

static double parMaisProximoDelaunay(const std::vector<Point2D>& p) {
    DivideConquerDelaunay dc;
    double melhor = std::numeric_limits<double>::infinity();
    for (const Edge& e : dc.triangulate(p).edges()) {
        melhor = std::min(melhor, distancia2(p[e.u], p[e.v]));
    }
    return std::sqrt(melhor);
}

static void triangulacao() {
    std::printf("\n## Triangulação de Delaunay (dividir e conquistar)\n\n");
    std::printf("| n | arestas | tempo (ms) | t / (n log2 n) (ns) |\n");
    std::printf("|---:|---:|---:|---:|\n");

    for (int n = 1000; n <= 128000; n *= 2) {
        std::vector<Point2D> pontos = pontosAleatorios(n, n);
        size_t arestas = 0;
        double ms = medir([&] {
            DivideConquerDelaunay dc;
            arestas = dc.triangulate(pontos).edges().size();
        });
        double porNLogN = ms * 1e6 / (n * std::log2(static_cast<double>(n)));
        std::printf("| %d | %zu | %.2f | %.1f |\n", n, arestas, ms, porNLogN);
    }
}

static void kruskal() {
    std::printf("\n## Kruskal: sobre a Delaunay x sobre o grafo completo (k = %d)\n\n", K);
    std::printf("| n | arestas (Delaunay) | triangulação (ms) | Kruskal na Delaunay (ms) | total (ms) "
                "| arestas (completo) | Kruskal no completo (ms) |\n");
    std::printf("|---:|---:|---:|---:|---:|---:|---:|\n");

    for (int n : {500, 1000, 2000, 5000}) {
        std::vector<Point2D> pontos = pontosAleatorios(n, n + 1);

        DelaunayGraph grafo(0);
        double msTriangulacao = medir([&] {
            DivideConquerDelaunay dc;
            grafo = dc.triangulate(pontos);
        });

        KruskalClusterer clusterizador;
        double msKruskalDelaunay = medir([&] { clusterizador.cluster(pontos, grafo, K); });
        double msKruskalCompleto = medir([&] { kruskalNoGrafoCompleto(pontos, K); });

        std::printf("| %d | %zu | %.2f | %.2f | %.2f | %ld | %.2f |\n", n, grafo.edges().size(),
                    msTriangulacao, msKruskalDelaunay, msTriangulacao + msKruskalDelaunay,
                    static_cast<long>(n) * (n - 1) / 2, msKruskalCompleto);
    }
}

static void parMaisProximo() {
    std::printf("\n## Par mais próximo: menor aresta da Delaunay x força bruta\n\n");
    std::printf("| n | Delaunay (ms) | força bruta (ms) | mesma distância? |\n");
    std::printf("|---:|---:|---:|:---:|\n");

    for (int n = 1000; n <= 32000; n *= 2) {
        std::vector<Point2D> pontos = pontosAleatorios(n, n + 2);
        double dDelaunay = 0.0;
        double dForcaBruta = 0.0;
        double msDelaunay = medir([&] { dDelaunay = parMaisProximoDelaunay(pontos); });
        double msForcaBruta = medir([&] { dForcaBruta = parMaisProximoForcaBruta(pontos); });
        std::printf("| %d | %.2f | %.2f | %s |\n", n, msDelaunay, msForcaBruta,
                    dDelaunay == dForcaBruta ? "sim" : "NÃO");
    }
}

static void dicionarioInteiro(const std::string& caminho) {
    std::printf("\n## Dicionário inteiro do CMU\n\n");
    if (!std::ifstream(caminho)) {
        std::printf("Dicionário não encontrado em %s: medida pulada.\n", caminho.c_str());
        return;
    }

    auto inicio = std::chrono::steady_clock::now();
    CmuDictionary dicionario(caminho);
    auto lido = std::chrono::steady_clock::now();

    AcousticTranslator tradutor(0.9);
    DivideConquerDelaunay triangulador;
    KruskalClusterer clusterizador;
    RhymeEngine engine(dicionario, tradutor, triangulador, clusterizador);
    engine.build(15);
    auto pronto = std::chrono::steady_clock::now();

    auto ms = [](auto a, auto b) { return std::chrono::duration<double, std::milli>(b - a).count(); };
    std::printf("| etapa | tempo (ms) |\n|---|---:|\n");
    std::printf("| ler o dicionário (%zu entradas) | %.1f |\n", dicionario.entries().size(), ms(inicio, lido));
    std::printf("| build(15): índice, triangulação e Kruskal | %.1f |\n", ms(lido, pronto));
}

int main(int argc, char** argv) {
#ifndef NDEBUG
#endif
    std::string caminho = argc > 1 ? argv[1] : "data/cmudict.dict";

    triangulacao();
    kruskal();
    parMaisProximo();
    dicionarioInteiro(caminho);
    return 0;
}
