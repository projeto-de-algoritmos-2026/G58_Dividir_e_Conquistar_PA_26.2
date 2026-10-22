#include "DelaunayGraph.hpp"

#include <algorithm>

namespace modelo::geometria {

const std::vector<int>& DelaunayGraph::neighbors(int v) const {
	return adj.at(v);
}

std::vector<Edge> DelaunayGraph::edges() const {

	std::vector<Edge> resultado;

	for (int u = 0; u < size(); u++) {
		for (int v : adj[u]) {
			if (u < v) {
				resultado.push_back(Edge{u, v, 0.0});
			}
		}
	}
	return resultado;
}

int DelaunayGraph::size() const {
	return static_cast<int>(adj.size());
}

void DelaunayGraph::addEdge(int u, int v) {
	if (u != v) {
		if (std::find(adj.at(u).begin(), adj.at(u).end(), v) == adj.at(u).end()) {
			adj[v].push_back(u);
			adj[u].push_back(v);
		}
	}

}
}  // namespace modelo::geometria
