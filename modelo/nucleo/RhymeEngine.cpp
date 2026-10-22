#include "RhymeEngine.hpp"

namespace modelo
{
namespace nucleo
{

RhymeEngine::RhymeEngine(IDictionaryLookUp& dict, IPhoneticConverter& conv, modelo::geometria::ITriangulator& tri, modelo::geometria::IClusterer& clusterer)
	: dict(dict), conv(conv), tri(tri), clusterer(clusterer), graph(0)
{
}

void RhymeEngine::build(int k)
{
}

RhymeResult RhymeEngine::findRhymes(const std::string& word, int maxNear)
{
	return {};
}

RhymeCluster RhymeEngine::clusterOf(const std::string& word)
{
	return {};
}

std::vector<int> RhymeEngine::nearestVertices(int v, int k)
{
	return {};
}
}  // namespace nucleo
}  // namespace modelo
