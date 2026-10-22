#include "DivideConquerDelaunay.hpp"

namespace modelo
{
namespace geometria
{

DelaunayGraph DivideConquerDelaunay::triangulate(const std::vector<Point2D>& points)
{
	return DelaunayGraph(0);
}

EdgePair DivideConquerDelaunay::divide(int lo, int hi)
{
	return {};
}

EdgePair DivideConquerDelaunay::merge(EdgePair left, EdgePair right)
{
	return {};
}

QuadEdge* DivideConquerDelaunay::lowerTangent(QuadEdge* ldi, QuadEdge* rdi)
{
	return nullptr;
}

bool DivideConquerDelaunay::ccw(int a, int b, int c)
{
	return false;
}

bool DivideConquerDelaunay::inCircle(int a, int b, int c, int d)
{
	return false;
}

bool DivideConquerDelaunay::rightOf(int p, QuadEdge* e)
{
	return false;
}

bool DivideConquerDelaunay::leftOf(int p, QuadEdge* e)
{
	return false;
}

bool DivideConquerDelaunay::valid(QuadEdge* e, QuadEdge* basel)
{
	return false;
}

DelaunayGraph DivideConquerDelaunay::toGraph()
{
	return DelaunayGraph(0);
}
}  // namespace geometria
}  // namespace modelo
