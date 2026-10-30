#include "KruskalClusterer.hpp"
#include "modelo/geometria/UnionFind.hpp"

#include <cmath>
#include <stdexcept>
#include <algorithm>

namespace modelo::geometria {

std::vector<int> KruskalClusterer::cluster(const std::vector<Point2D>& points, const DelaunayGraph& graph, int clusterCount) {

	const int pointCount = static_cast<int>(points.size());

	if (clusterCount < 1 || clusterCount > pointCount) {
		throw std::invalid_argument("k precisa estar entre 1 e o número de pontos");
	}

	UnionFind unionFind(pointCount);

	const std::vector<Edge> edges = KruskalClusterer::sortedEdges(points, graph);

	for (const Edge& edge : edges) {
		if (unionFind.componentCount() == clusterCount) {
			break;
		} else {
			unionFind.unite(edge.u, edge.v);
		}
	}

	std::vector<int> labelOfRoot(pointCount, -1);
	std::vector<int> labels(pointCount, -1);
	int nextLabel = 0;

	for (int i = 0; i < pointCount; i++) {
		const int root = unionFind.find(i);
		if (labelOfRoot[root] == -1) {
			labelOfRoot[root] = nextLabel;
			nextLabel++;
		}
		labels[i] = labelOfRoot[root];
	}
	return labels;
}

std::vector<Edge> KruskalClusterer::sortedEdges(const std::vector<Point2D>& points, const DelaunayGraph& graph) {

	std::vector<Edge> edges = graph.edges();

	for (Edge& edge : edges) edge.length = points[edge.u].distanceTo(points[edge.v]);

	std::sort(edges.begin(), edges.end());

	return edges;
}
}  // namespace modelo::geometria
