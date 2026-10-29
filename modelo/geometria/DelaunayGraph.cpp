#include "DelaunayGraph.hpp"

#include <algorithm>

namespace modelo::geometria {

const std::vector<int>& DelaunayGraph::neighbors(int vertex) const {
	return adjacency.at(vertex);
}

std::vector<Edge> DelaunayGraph::edges() const {

	std::vector<Edge> result;

	for (int u = 0; u < size(); u++) {
		for (int v : adjacency[u]) {
			if (u < v) {
				result.push_back(Edge{u, v, 0.0});
			}
		}
	}
	return result;
}

int DelaunayGraph::size() const {
	return static_cast<int>(adjacency.size());
}

void DelaunayGraph::addEdge(int u, int v) {
	if (u != v) {
		if (std::find(adjacency.at(u).begin(), adjacency.at(u).end(), v) == adjacency.at(u).end()) {
			adjacency[v].push_back(u);
			adjacency[u].push_back(v);
		}
	}

}
}  // namespace modelo::geometria
