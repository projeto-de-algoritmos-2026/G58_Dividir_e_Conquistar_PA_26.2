#include "UnionFind.hpp"

namespace modelo::geometria {


int UnionFind::find(int x) {
	if (parent[x] != x) {
		parent[x] = find(parent[x]);
	}
	return parent[x];
}

bool UnionFind::unite(int a, int b) {

	int ra = find(a);
	int rb = find(b);

	if (ra == rb) {
		return false;
	}

	// O nó com maior rank vira pai do nó com menor rank
	if (rank[ra] > rank[rb]) {
		parent[rb] = ra;
	} else if (rank[rb] < rank[ra]) {
		parent[ra] = rb;
	} else if (rank[ra] == rank[rb]) {
		parent[ra] = rb;
		rank[ra]++;
	}

	components--;

	return true;

}

int UnionFind::count() { return components; }

}  // namespace modelo:::geometria
