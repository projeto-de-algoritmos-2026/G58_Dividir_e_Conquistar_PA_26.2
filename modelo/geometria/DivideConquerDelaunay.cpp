#include "DivideConquerDelaunay.hpp"
#include "predicates.h"

#include <numeric>
#include <algorithm>
#include <stdexcept>

namespace modelo::geometria{

DelaunayGraph DivideConquerDelaunay::triangulate(const std::vector<Point2D>& points) {
	exactinit();
	edgeArena.clear();
	sortedPoints.clear();

	const int pointCount = static_cast<int>(points.size());

	if (pointCount < 2) {
		return DelaunayGraph(pointCount);
	}

	originalIndex.assign(pointCount, 0);

	std::iota(originalIndex.begin(), originalIndex.end(), 0);

	std::sort(originalIndex.begin(), originalIndex.end(), [&](const int i, const int j) { return points[i] < points[j]; });

	for (int i = 0; i < pointCount; i++) {
		sortedPoints.push_back(points[originalIndex[i]]);
	}

	for (int i = 1; i < pointCount; i++) {
		if (sortedPoints[i] == sortedPoints[i-1]) {
			throw std::invalid_argument("Point already exists");
		}
	}

	divide(0, pointCount);

	return toGraph();
}

DivideConquerDelaunay::HullEdges DivideConquerDelaunay::divide(const int begin, const int end) {

	const int pointCount = end - begin;

	if (pointCount == 2) {

		QuadEdge* edge01 = QuadEdge::makeEdge(edgeArena);

		edge01->origin = begin;
		edge01->sym()->origin = begin + 1;
		return {edge01, edge01->sym()};

	}

	if (pointCount == 3) {

		QuadEdge* edge01 = QuadEdge::makeEdge(edgeArena);
		QuadEdge* edge12 = QuadEdge::makeEdge(edgeArena);

		QuadEdge::splice(edge01->sym(), edge12);

		edge01->origin = begin;
		edge01->sym()->origin = begin + 1;

		edge12->origin = begin + 1;
		edge12->sym()->origin = begin + 2;

		if (isCounterClockwise(begin, begin + 1, begin + 2)) {
			QuadEdge::connect(edge12, edge01, edgeArena);
			return {edge01, edge12->sym()};
		}

		if (isCounterClockwise(begin, begin+2, begin+1)) {
			QuadEdge* edge20 = QuadEdge::connect(edge12 ,edge01, edgeArena);
			return {edge20->sym(), edge20};
		}

		return {edge01, edge12->sym()};
	}

		const int middle = (begin + end) / 2;

		return merge(divide(begin, middle), divide(middle, end));
}

DivideConquerDelaunay::HullEdges DivideConquerDelaunay::merge(const HullEdges left, const HullEdges right) {

	QuadEdge* leftOuter = left.leftMost;
	QuadEdge* leftInner = left.rightMost;
	QuadEdge* rightInner = right.leftMost;
	QuadEdge* rightOuter = right.rightMost;

	QuadEdge* base = lowerTangent(leftInner, rightInner);

	if (base->dest() == leftOuter->origin) {
		leftOuter = base->sym();
	}

	if (base->origin == rightOuter->origin) {
		rightOuter = base;
	}

	while (true) {

		QuadEdge* leftCandidate = base->sym()->oNext();

		if (isAboveBase(leftCandidate, base)) {
			while (true) {
				if (!isInsideCircle(base->dest(), base->origin, leftCandidate->dest(), leftCandidate->oNext()->dest())) {
				break;
				}
				QuadEdge* nextCandidate = leftCandidate->oNext();
				QuadEdge::deleteEdge(leftCandidate);
				leftCandidate = nextCandidate;
			}
		}

		QuadEdge* rightCandidate = base->oPrev();

		if (isAboveBase(rightCandidate, base)) {
			while (true) {
				if (!isInsideCircle(base->dest(), base->origin, rightCandidate->dest(), rightCandidate->oPrev()->dest())) {
					break;
				}
				QuadEdge* nextCandidate = rightCandidate->oPrev();
				QuadEdge::deleteEdge(rightCandidate);
				rightCandidate = nextCandidate;
			}
		}

		const bool leftValid = isAboveBase(leftCandidate, base);
		const bool rightValid = isAboveBase(rightCandidate, base);

		if (!leftValid && !rightValid) break;

		if (!leftValid || (rightValid && isInsideCircle(leftCandidate->dest(), leftCandidate->origin, rightCandidate->origin, rightCandidate->dest()))) {
			base = QuadEdge::connect(rightCandidate, base->sym(), edgeArena);
		} else {
			base = QuadEdge::connect(base->sym(), leftCandidate->sym(), edgeArena);
		}

	}

	return {leftOuter, rightOuter};
}

QuadEdge* DivideConquerDelaunay::lowerTangent(QuadEdge* leftInner, QuadEdge* rightInner) {

	while (true) {

		if (isLeftOf(rightInner->origin, leftInner)) {
			leftInner = leftInner->lNext();
		} else if (isRightOf(leftInner->origin, rightInner)) {
			rightInner = rightInner->rPrev();
		} else {
			break;
		}
	}

	return QuadEdge::connect(rightInner->sym(), leftInner, edgeArena);
}

bool DivideConquerDelaunay::isCounterClockwise(const int first, const int second, const int third) const {

	double pa[2] = {sortedPoints[first].x, sortedPoints[first].y};
	double pb[2] = {sortedPoints[second].x, sortedPoints[second].y};
	double pc[2] = {sortedPoints[third].x, sortedPoints[third].y};

	return orient2d(pa, pb, pc) > 0.0;
}

bool DivideConquerDelaunay::isInsideCircle(const int first, const int second, const int third, const int point) const {

	double pa[2] = {sortedPoints[first].x, sortedPoints[first].y};
	double pb[2] = {sortedPoints[second].x, sortedPoints[second].y};
	double pc[2] = {sortedPoints[third].x, sortedPoints[third].y};
	double pd[2] = {sortedPoints[point].x, sortedPoints[point].y};

	return incircle(pa, pb, pc, pd) > 0.0;
}

DelaunayGraph DivideConquerDelaunay::toGraph() {

	DelaunayGraph graph(static_cast<int>(sortedPoints.size()));

	for (int i = 0; i < static_cast<int>(edgeArena.size()); i += 4) {

		QuadEdge& edge = edgeArena[i];

		if (edge.origin == -1) {
			continue;
		}
		graph.addEdge(originalIndex[edge.origin], originalIndex[edge.dest()]);
	}

	return graph;
}
}  // namespace modelo::geometria
