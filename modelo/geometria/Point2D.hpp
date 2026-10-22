#ifndef MODELO_GEOMETRIA_POINT2_D_H
#define MODELO_GEOMETRIA_POINT2_D_H

namespace modelo
{
namespace geometria
{
struct Point2D
{
public:
	double x;

	double y;

public:
	bool operator<(const Point2D& other) const;

	bool operator==(const Point2D& other) const;

};

}  // namespace geometria
}  // namespace modelo
#endif
