#ifndef MODELO_GEOMETRIA_DIVIDE_CONQUER_DELAUNAY_H
#define MODELO_GEOMETRIA_DIVIDE_CONQUER_DELAUNAY_H

#include <deque>
#include <vector>

#include "modelo/geometria/ITriangulator.hpp"
#include "modelo/geometria/Point2D.hpp"
#include "modelo/geometria/QuadEdge.hpp"
#include "modelo/geometria/DelaunayGraph.hpp"

namespace modelo::geometria {

class DivideConquerDelaunay : public ITriangulator {

	std::vector<Point2D> sortedPoints;

	std::vector<int> originalIndex;

	std::deque<QuadEdge> edgeArena;

	struct HullEdges {
		QuadEdge* leftMost;
		QuadEdge* rightMost;
	};

	HullEdges divide(int begin, int end);

	HullEdges merge(HullEdges left, HullEdges right);

	QuadEdge* lowerTangent(QuadEdge* leftInner, QuadEdge* rightInner);

	[[nodiscard]] bool isCounterClockwise(int first, int second, int third) const;

	[[nodiscard]] bool isInsideCircle(int first, int second, int third, int point) const;

	bool isRightOf(int point, QuadEdge* edge) const { return isCounterClockwise(point, edge->dest(), edge->origin);  }

	bool isLeftOf(int point, QuadEdge* edge) const { return isCounterClockwise(point, edge->origin, edge->dest()); }

	bool isAboveBase(QuadEdge* candidate, QuadEdge* base) const { return isRightOf(candidate->dest(), base); }

	DelaunayGraph toGraph();

public:
	DelaunayGraph triangulate(const std::vector<Point2D>& points) override;

};

}  // namespace modelo::geometria
#endif
