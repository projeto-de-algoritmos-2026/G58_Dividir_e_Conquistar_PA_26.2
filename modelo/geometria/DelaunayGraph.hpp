#ifndef MODELO_GEOMETRIA_DELAUNAY_GRAPH_H
#define MODELO_GEOMETRIA_DELAUNAY_GRAPH_H

#include <vector>

#include "modelo/geometria/Edge.hpp"

namespace modelo::geometria {

class DelaunayGraph {

private:
	std::vector<std::vector<int>> adjacency;

public:
	const std::vector<int>& neighbors(int vertex)const;

	std::vector<Edge> edges() const;

	int size() const;

	DelaunayGraph(int vertexCount) : adjacency(vertexCount) {};

	void addEdge(int u, int v);

};

}  // namespace modelo::geometria
#endif
