#ifndef MODELO_GEOMETRIA_DIVIDE_CONQUER_DELAUNAY_H
#define MODELO_GEOMETRIA_DIVIDE_CONQUER_DELAUNAY_H

#include <deque>
#include <utility>
#include <vector>

#include "modelo/geometria/ITriangulator.hpp"
#include "modelo/geometria/Point2D.hpp"
#include "modelo/geometria/QuadEdge.hpp"
#include "modelo/geometria/DelaunayGraph.hpp"

namespace modelo
{
namespace geometria
{
using EdgePair = std::pair<QuadEdge*, QuadEdge*>;

class DivideConquerDelaunay : public ITriangulator
{
private:
	std::vector<Point2D> pts;

	std::vector<int> order;

	std::deque<QuadEdge> pool;

private:
	EdgePair divide(int lo, int hi);

	EdgePair merge(EdgePair left, EdgePair right);

	QuadEdge* lowerTangent(QuadEdge* ldi, QuadEdge* rdi);

	bool ccw(int a, int b, int c);

	bool inCircle(int a, int b, int c, int d);

	bool rightOf(int p, QuadEdge* e);

	bool leftOf(int p, QuadEdge* e);

	bool valid(QuadEdge* e, QuadEdge* basel);

	DelaunayGraph toGraph();

public:
	DelaunayGraph triangulate(const std::vector<Point2D>& points) override;

};

}  // namespace geometria
}  // namespace modelo
#endif
