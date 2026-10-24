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

	} else if (n == 3) {

		QuadEdge* a = QuadEdge::makeEdge(pool);
		QuadEdge* b = QuadEdge::makeEdge(pool);

		QuadEdge::splice(a->sym(), b);

		a->org = lo;
		a->sym()->org = lo + 1;

		b->org = lo + 1;
		b->sym()->org = lo + 2;

		if (ccw(lo, lo + 1, lo + 2)) {
			QuadEdge::connect(b, a, pool);
			return {a, b->sym()};
		} else if (ccw(lo, lo+2, lo+1)) {
			QuadEdge* c = QuadEdge::connect(b ,a, pool);
			return {c->sym(), c};
		} else {
			return {a, b->sym()};
		}

	} else {

		int mid = (lo + hi) / 2;

		return merge(divide(lo, mid), divide(mid, hi));

	}
}

EdgePair DivideConquerDelaunay::merge(EdgePair left, EdgePair right) {

	QuadEdge* ldo = left.first;
	QuadEdge* ldi = left.second;
	QuadEdge* rdi = right.first;
	QuadEdge* rdo = right.second;

	QuadEdge* basel = lowerTangent(ldi, rdi);

	if (basel->dest() == ldo->org) {
		ldo = basel->sym();
	} else if (basel->org == rdo->org) {
		rdo = basel;
	}

	while (true) {

		QuadEdge* lcand = basel->sym()->onext();

		if (valid(lcand, basel)) {
			while (true) {
				if (!(inCircle(basel->dest(), basel->org, lcand->dest(), lcand->onext()->dest()))) {
				break;
				}
				QuadEdge* t = lcand->onext();
				QuadEdge::deleteEdge(lcand);
				lcand = t;
			}
		}

		QuadEdge* rcand = basel->oprev();

		if (valid(rcand, basel)) {
			while (true) {
				if (!(inCircle(basel->dest(), basel->org, rcand->dest(), rcand->oprev()->dest()))) {
					break;
				}
				QuadEdge* t = rcand->oprev();
				QuadEdge::deleteEdge(rcand);
				rcand = t;
			}
		}

		bool lv = valid(lcand, basel);
		bool rv = valid(rcand, basel);

		if (!lv && !rv) {
			break;
		}

		if (!lv || (rv && inCircle(lcand->dest(), lcand->org, rcand->org, rcand->dest()))) {
			basel = QuadEdge::connect(rcand, basel->sym(), pool);
		} else {
			basel = QuadEdge::connect(basel->sym(), lcand->sym(), pool);
		}

	}

	return {ldo, rdo};
}

QuadEdge* DivideConquerDelaunay::lowerTangent(QuadEdge* ldi, QuadEdge* rdi) {

	while (true) {

		if (leftOf(rdi->org, ldi)) {
			ldi = ldi->lnext();
		} else if (rightOf(ldi->org, rdi)) {
			rdi = rdi->rprev();
		} else {
			break;
		}
	}

	return QuadEdge::connect(rdi->sym(), ldi, pool);
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
