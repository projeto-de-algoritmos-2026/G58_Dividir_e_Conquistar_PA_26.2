#ifndef MODELO_GEOMETRIA_QUAD_EDGE_H
#define MODELO_GEOMETRIA_QUAD_EDGE_H

#include <deque>

namespace modelo::geometria {
struct QuadEdge {

private:
	QuadEdge* next = nullptr;
	QuadEdge* r = nullptr;

public:
	int org = -1;

public:
	QuadEdge* rot() { return r; }

	QuadEdge* sym() { return r->r; }

	QuadEdge* onext() { return next; }

	int dest() { return sym()->org; }

	static QuadEdge* makeEdge(std::deque<QuadEdge>& pool);

	static void splice(QuadEdge* a, QuadEdge* b);

	static QuadEdge* connect(QuadEdge* a, QuadEdge* b, std::deque<QuadEdge>& pool);

	static void deleteEdge(QuadEdge* e);

	QuadEdge* invRot() { return r->r->r; }

	QuadEdge* lnext() { return invRot()->onext()->rot(); }

	QuadEdge* oprev() {return rot()->onext()->rot();  }

	QuadEdge* rprev() { return sym()->onext(); }

};

}  // namespace modelo::geometria
#endif
