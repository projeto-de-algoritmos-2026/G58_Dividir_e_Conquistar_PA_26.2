#ifndef MODELO_GEOMETRIA_POINT2_D_H
#define MODELO_GEOMETRIA_POINT2_D_H

#include <tuple>
#include <cmath>

namespace modelo::geometria {

struct Point2D {

	double x;

	double y;

	bool operator<(const Point2D& other) const { return std::tie(x, y) < std::tie(other.x, other.y); }

	bool operator==(const Point2D& other) const {return std::tie(x, y) == std::tie(other.x, other.y); }

	[[nodiscard]] double distanceTo(const Point2D& other) const { return std::hypot(x - other.x, y - other.y); }

};

}  // namespace modelo::geometria
#endif
