#ifndef MODELO_GEOMETRIA_POINT2_D_H
#define MODELO_GEOMETRIA_POINT2_D_H

#include <tuple>

namespace modelo::geometria {

struct Point2D {

public:
	double x;

	double y;

public:
	bool operator<(const Point2D& other) const { return std::tie(x, y) < std::tie(other.x, other.y); }

	bool operator==(const Point2D& other) const {return std::tie(x, y) == std::tie(other.x, other.y); }

};

}  // namespace modelo::geometria
#endif
