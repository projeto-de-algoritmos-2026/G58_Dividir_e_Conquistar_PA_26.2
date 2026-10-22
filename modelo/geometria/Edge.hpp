#ifndef MODELO_GEOMETRIA_EDGE_H
#define MODELO_GEOMETRIA_EDGE_H

namespace modelo::geometria {

struct Edge {

public:
	int u;

	int v;

	double length;

public:
	bool operator<(const Edge& other) const { return length < other.length; }

};

}  // namespace modelo::geometria
#endif
