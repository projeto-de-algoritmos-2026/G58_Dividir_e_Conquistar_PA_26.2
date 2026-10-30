#include "DelaunayGraph.hpp"

#include <algorithm>

namespace modelo::geometria {

std::vector<Edge> DelaunayGraph::edges() const {

	std::vector<Edge> result;

	for (int u = 0; u < size(); u++) {
		for (const int v : adjacency[u]) {
			if (u < v) {
				result.push_back(Edge{u, v, 0.0});
			}
		}
	}
	return result;
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
