#ifndef MODELO_GEOMETRIA_QUAD_EDGE_H
#define MODELO_GEOMETRIA_QUAD_EDGE_H

#include <deque>

namespace modelo::geometria {
struct QuadEdge {

private:
	QuadEdge* originNext = nullptr;
	QuadEdge* rotated = nullptr;

public:
	int origin = -1;

public:
	QuadEdge* rot() { return rotated; }

	QuadEdge* sym() { return rotated->rotated; }

	QuadEdge* onext() { return originNext; }

	int dest() { return sym()->origin; }

	static QuadEdge* makeEdge(std::deque<QuadEdge>& arena);

	static void splice(QuadEdge* first, QuadEdge* second);

	static QuadEdge* connect(QuadEdge* previous, QuadEdge* next, std::deque<QuadEdge>& arena);

	static void deleteEdge(QuadEdge* edge);

	QuadEdge* invRot() { return rotated->rotated->rotated; }

	QuadEdge* lnext() { return invRot()->onext()->rot(); }

	QuadEdge* oprev() {return rot()->onext()->rot();  }

	QuadEdge* rprev() { return sym()->onext(); }

};

}  // namespace modelo::geometria
#endif
