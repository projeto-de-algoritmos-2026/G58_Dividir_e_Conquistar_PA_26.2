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
	explicit UnionFind(int elementCount)
		: parent(elementCount), rank(elementCount, 0), components(elementCount) {
		std::iota(parent.begin(), parent.end(), 0);
	}

	int find(int element);

	bool unite(int first, int second);

	[[nodiscard]] int componentCount() const { return components; }

};

}  // namespace modelo::geometria
#endif
