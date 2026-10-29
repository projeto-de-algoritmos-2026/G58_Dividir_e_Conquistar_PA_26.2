#include "UnionFind.hpp"

namespace modelo::geometria {


int UnionFind::find(int element) {
	if (parent[element] != element) {
		parent[element] = find(parent[element]);
	}
	return parent[element];
}

bool UnionFind::unite(int first, int second) {

	int firstRoot = find(first);
	int secondRoot = find(second);

	if (firstRoot == secondRoot) {
		return false;
	}

	// O nó com maior rank vira pai do nó com menor rank
	if (rank[firstRoot] > rank[secondRoot]) {
		parent[secondRoot] = firstRoot;
	} else if (rank[secondRoot] > rank[firstRoot]) {
		parent[firstRoot] = secondRoot;
	} else {
		parent[secondRoot] = firstRoot;
		rank[firstRoot]++;
	}

	components--;

	return true;

}

int UnionFind::componentCount() { return components; }

}  // namespace modelo:::geometria
