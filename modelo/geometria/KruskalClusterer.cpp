#include "KruskalClusterer.hpp"
#include "modelo/geometria/UnionFind.hpp"

#include <cmath>
#include <stdexcept>
#include <algorithm>

namespace modelo::geometria {

std::vector<int> KruskalClusterer::cluster(const std::vector<Point2D>& points, const DelaunayGraph& graph, int k) {

	int n = static_cast<int>(points.size());

	if (k < 1 || k > n) {
		throw std::invalid_argument("k precisa estar entre 1 e o número de pontos");
	}

	UnionFind unionFind(n);

	std::vector<Edge> arestas = KruskalClusterer::sortedEdges(points, graph);

	for (const Edge& e : arestas) {
		if (unionFind.count() == k) {
			break;
		} else {
			unionFind.unite(e.u, e.v);
		}
	}

	std::vector<int> rotuloDaRaiz(n, -1);
	std::vector<int> rotulos(n, -1);
	int proximo = 0;

	for (int i = 0; i < n; i++) {
		int r = unionFind.find(i);
		if (rotuloDaRaiz[r] == -1) {
			rotuloDaRaiz[r] = proximo;
			proximo++;
		}
		rotulos[i] = rotuloDaRaiz[r];
	}
	return rotulos;
}

std::vector<Edge> KruskalClusterer::sortedEdges(const std::vector<Point2D>& points, const DelaunayGraph& graph) {

	std::vector<Edge> edges = graph.edges();

	for (Edge& e : edges) {
		double dx = points[e.u].x - points[e.v].x;
		double dy = points[e.u].y - points[e.v].y;

		e.length = std::hypot(dx, dy);
	}

	std::sort(edges.begin(), edges.end());

	return edges;
}
}  // namespace modelo::geometria
