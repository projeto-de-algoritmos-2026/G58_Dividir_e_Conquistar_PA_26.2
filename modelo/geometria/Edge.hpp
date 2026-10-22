#ifndef MODELO_GEOMETRIA_EDGE_H
#define MODELO_GEOMETRIA_EDGE_H

namespace modelo
{
namespace geometria
{
struct Edge
{
public:
	int u;

	int v;

	double length;

public:
	bool operator<(const Edge& other) const;

};

}  // namespace geometria
}  // namespace modelo
#endif
