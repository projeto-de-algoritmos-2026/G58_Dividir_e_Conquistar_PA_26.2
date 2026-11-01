#ifndef MODELO_GEOMETRIA_QUAD_EDGE_H
#define MODELO_GEOMETRIA_QUAD_EDGE_H

#include <deque>

// O CLion analisa um .cpp por vez: ele vê rotated e originNext começando como
// nullptr aqui, mas não vê o makeEdge (QuadEdge.cpp) ligar os ponteiros, e conclui
// que eles são sempre nulos. Toda QuadEdge nasce pelo makeEdge, então depois dele
// nenhum desses ponteiros é nulo. Por isso os //noinspection abaixo.

namespace modelo::geometria {
struct QuadEdge {

private:
	QuadEdge* originNext = nullptr;
	QuadEdge* rotated = nullptr;

public:
	int origin = -1;

	//noinspection CppDFAConstantFunctionResult
	[[nodiscard]] QuadEdge *rot() const { return rotated; }

	//noinspection CppDFANullDereference
	[[nodiscard]] QuadEdge* sym() const { return rotated->rotated; }

	//noinspection CppDFAConstantFunctionResult
	[[nodiscard]] QuadEdge* oNext() const { return originNext; }

	[[nodiscard]] int dest() const { return sym()->origin; }

	static QuadEdge* makeEdge(std::deque<QuadEdge>& arena);

	static void splice(QuadEdge* first, QuadEdge* second);

	static QuadEdge* connect(QuadEdge* previous, QuadEdge* next, std::deque<QuadEdge>& arena);

	static void deleteEdge(QuadEdge* edge);

	//noinspection CppDFANullDereference
	[[nodiscard]] QuadEdge* invRot() const { return rotated->rotated->rotated; }

	[[nodiscard]] QuadEdge* lNext() const { return invRot()->oNext()->rot(); }

	//noinspection CppDFAConstantFunctionResult
	[[nodiscard]] QuadEdge* oPrev() const {return rot()->oNext()->rot();  }

	[[nodiscard]] QuadEdge* rPrev() const { return sym()->oNext(); }

};

}  // namespace modelo::geometria
#endif
