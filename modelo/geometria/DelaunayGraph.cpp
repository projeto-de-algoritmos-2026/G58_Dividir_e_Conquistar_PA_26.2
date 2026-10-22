#include "DelaunayGraph.hpp"

namespace modelo
{
namespace geometria
{

const std::vector<int>& DelaunayGraph::neighbors(int v) const
{
	return adj.at(v);
}

std::vector<Edge> DelaunayGraph::edges() const
{
	return {};
}

int DelaunayGraph::size() const
{
	return 0;
}

DelaunayGraph::DelaunayGraph(int n)
{
}

void DelaunayGraph::addEdge(int u, int v)
{
}
}  // namespace geometria
}  // namespace modelo
