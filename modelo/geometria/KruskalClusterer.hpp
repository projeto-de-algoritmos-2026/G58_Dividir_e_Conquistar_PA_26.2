#ifndef MODELO_GEOMETRIA_KRUSKAL_CLUSTERER_H
#define MODELO_GEOMETRIA_KRUSKAL_CLUSTERER_H

#include <vector>

#include "modelo/geometria/IClusterer.hpp"
#include "modelo/geometria/Edge.hpp"
#include "modelo/geometria/Point2D.hpp"
#include "modelo/geometria/DelaunayGraph.hpp"

namespace modelo::geometria {

class KruskalClusterer : public IClusterer {

private:
	std::vector<Edge> sortedEdges(const std::vector<Point2D>& points, const DelaunayGraph& graph);

public:
	std::vector<int> cluster(const std::vector<Point2D>& points, const DelaunayGraph& graph, int k) override;

};

}  // namespace modelo::geometria
#endif
