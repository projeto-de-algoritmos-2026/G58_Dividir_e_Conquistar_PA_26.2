#ifndef MODELO_GEOMETRIA_QUAD_EDGE_H
#define MODELO_GEOMETRIA_QUAD_EDGE_H

namespace modelo
{
namespace geometria
{
struct QuadEdge
{
public:
	int org;

public:
	QuadEdge* rot();

	QuadEdge* sym();

	QuadEdge* onext();

	int dest();

	static QuadEdge* makeEdge();

	static void splice(QuadEdge* a, QuadEdge* b);

	static QuadEdge* connect(QuadEdge* a, QuadEdge* b);

	static void deleteEdge(QuadEdge* e);

	QuadEdge* invRot();

	QuadEdge* lnext();

	QuadEdge* oprev();

	QuadEdge* rprev();

};

}  // namespace geometria
}  // namespace modelo
#endif
