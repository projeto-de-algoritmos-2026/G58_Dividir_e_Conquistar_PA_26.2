#ifndef MODELO_GEOMETRIA_DELAUNAY_GRAPH_H
#define MODELO_GEOMETRIA_DELAUNAY_GRAPH_H

#include <vector>

#include "modelo/geometria/Edge.hpp"

namespace modelo::geometria {

class DelaunayGraph {

private:
	std::vector<std::vector<int>> adj;

public:
	const std::vector<int>& neighbors(int v)const;

	std::vector<Edge> edges() const;

	int size() const;

	DelaunayGraph(int n) : adj(n) {};

	void addEdge(int u, int v);

};

}  // namespace modelo::geometria
#endif
