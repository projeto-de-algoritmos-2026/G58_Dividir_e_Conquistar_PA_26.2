#ifndef MODELO_GEOMETRIA_UNION_FIND_H
#define MODELO_GEOMETRIA_UNION_FIND_H

#include <vector>

namespace modelo
{
namespace geometria
{
class UnionFind
{
private:
	std::vector<int> parent;

	std::vector<int> rank;

	int components;

public:
	UnionFind(int n);

	int find(int x);

	bool unite(int a, int b);

	int count();

};

}  // namespace geometria
}  // namespace modelo
#endif
