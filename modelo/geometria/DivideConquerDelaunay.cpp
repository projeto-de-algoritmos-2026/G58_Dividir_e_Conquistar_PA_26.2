#include "DivideConquerDelaunay.hpp"
#include "predicates.h"

#include <numeric>
#include <algorithm>
#include <stdexcept>

namespace modelo::geometria{

DelaunayGraph DivideConquerDelaunay::triangulate(const std::vector<Point2D>& points) {
	exactinit();
	pool.clear();
	pts.clear();

	int n = static_cast<int>(points.size());

	if (n < 2) {
		return DelaunayGraph(n);
	}

	order.assign(n, 0);

	std::iota(order.begin(), order.end(), 0);

	std::sort(order.begin(), order.end(), [&](int i, int j) { return points[i] < points[j]; });

	for (int k = 0; k < n; k++) {
		pts.push_back(points[order[k]]);
	}

	for (int k = 1; k < n; k++) {
		if (pts[k] == pts[k-1]) {
			throw std::invalid_argument("Point already exists");
		}
	}

	divide(0, n);

	return toGraph();
}

EdgePair DivideConquerDelaunay::divide(int lo, int hi) {

	int n = hi - lo;

	if (n == 2) {

		QuadEdge* a = QuadEdge::makeEdge(pool);

		a->org = lo;
		a->sym()->org = lo + 1;
		return {a, a->sym()};
	}

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

bool DivideConquerDelaunay::ccw(int a, int b, int c) {

	double pa[2] = {pts[a].x, pts[a].y};
	double pb[2] = {pts[b].x, pts[b].y};
	double pc[2] = {pts[c].x, pts[c].y};

	return orient2d(pa, pb, pc) > 0.0;
}

bool DivideConquerDelaunay::inCircle(int a, int b, int c, int d) {

	double pa[2] = {pts[a].x, pts[a].y};
	double pb[2] = {pts[b].x, pts[b].y};
	double pc[2] = {pts[c].x, pts[c].y};
	double pd[2] = {pts[d].x, pts[d].y};

	return incircle(pa, pb, pc, pd) > 0.0;
}

bool DivideConquerDelaunay::rightOf(int p, QuadEdge* e) {
	return ccw(p, e->dest(), e->org);
}

bool DivideConquerDelaunay::leftOf(int p, QuadEdge* e) {
	return ccw(p, e->org, e->dest());
}

bool DivideConquerDelaunay::valid(QuadEdge* e, QuadEdge* basel) {
	return rightOf(e->dest(), basel);
}

DelaunayGraph DivideConquerDelaunay::toGraph() {

	DelaunayGraph graph(pts.size());

	for (int i = 0; i < static_cast<int>(pool.size()); i += 4) {

		QuadEdge& e = pool[i];

		if (e.org == -1) {
			continue;
		}
		graph.addEdge(order[e.org], order[e.dest()]);
	}

	return graph;
}
}  // namespace modelo::geometria
