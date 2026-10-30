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

	[[nodiscard]] QuadEdge *rot() const { return rotated; }

	[[nodiscard]] QuadEdge* sym() const { return rotated->rotated; }

	[[nodiscard]] QuadEdge* oNext() const { return originNext; }

	[[nodiscard]] int dest() const { return sym()->origin; }

	static QuadEdge* makeEdge(std::deque<QuadEdge>& arena);

	static void splice(QuadEdge* first, QuadEdge* second);

	static QuadEdge* connect(QuadEdge* previous, QuadEdge* next, std::deque<QuadEdge>& arena);

	static void deleteEdge(QuadEdge* edge);

	[[nodiscard]] QuadEdge* invRot() const { return rotated->rotated->rotated; }

	[[nodiscard]] QuadEdge* lNext() const { return invRot()->oNext()->rot(); }

	[[nodiscard]] QuadEdge* oPrev() const {return rot()->oNext()->rot();  }

	[[nodiscard]] QuadEdge* rPrev() const { return sym()->oNext(); }

};

}  // namespace modelo::geometria
#endif
