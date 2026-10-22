#ifndef MODELO_GEOMETRIA_UNION_FIND_H
#define MODELO_GEOMETRIA_UNION_FIND_H

#include <vector>
#include <numeric>

namespace modelo::geometria {
class UnionFind {
private:
	std::vector<int> parent;

	std::vector<int> rank;

	int components;

public:
	UnionFind(int components)
		: parent(components), rank(components, 0), components(components) {
		std::iota(parent.begin(), parent.end(), 0);
	}

	int find(int x);

	bool unite(int a, int b);

	int count();

};

}  // namespace modelo::geometria
#endif
