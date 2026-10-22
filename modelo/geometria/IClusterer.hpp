#ifndef MODELO_GEOMETRIA_I_CLUSTERER_H
#define MODELO_GEOMETRIA_I_CLUSTERER_H

#include <vector>

#include "modelo/geometria/Point2D.hpp"
#include "modelo/geometria/DelaunayGraph.hpp"

namespace modelo
{
namespace geometria
{
class IClusterer
{
public:
	virtual ~IClusterer() = default;

	virtual std::vector<int> cluster(const std::vector<Point2D>& points, const DelaunayGraph& graph, int k) = 0;

};

}  // namespace geometria
}  // namespace modelo
#endif
