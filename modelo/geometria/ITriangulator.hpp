#ifndef MODELO_GEOMETRIA_I_TRIANGULATOR_H
#define MODELO_GEOMETRIA_I_TRIANGULATOR_H

#include <vector>

#include "modelo/geometria/DelaunayGraph.hpp"
#include "modelo/geometria/Point2D.hpp"

namespace modelo
{
namespace geometria
{
class ITriangulator
{
public:
	virtual ~ITriangulator() = default;

	virtual DelaunayGraph triangulate(const std::vector<Point2D>& points) = 0;

};

}  // namespace geometria
}  // namespace modelo
#endif
