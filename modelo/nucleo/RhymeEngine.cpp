#include "RhymeEngine.hpp"

using modelo::nucleo::RhymeIndex;
using modelo::nucleo::Phoneme;

static int familiaDaPalavra(const modelo::nucleo::IDictionaryLookUp& dict, const RhymeIndex& index, const std::string& word) {

	std::vector<Phoneme> phonemes = dict.lookUp(word);
	if (phonemes.empty()) return -1;

	std::vector<Phoneme> rhymePartPhonemes;
	if (rhymePartPhonemes.empty()) return -1;

	return index.findFamily(RhymeIndex::rhymeKey(rhymePartPhonemes));
}

namespace modelo::nucleo {

RhymeEngine::RhymeEngine(IDictionaryLookUp& dict, IPhoneticConverter& conv, modelo::geometria::ITriangulator& tri, modelo::geometria::IClusterer& clusterer)
	: dict(dict), conv(conv), tri(tri), clusterer(clusterer), graph(0)
{
}

void RhymeEngine::build(int k) {
}

RhymeResult RhymeEngine::findRhymes(const std::string& word, int maxNear)
{
	return {};
}

RhymeCluster RhymeEngine::clusterOf(const std::string& word) {

	RhymeCluster cluster;
	cluster.id = -1;

	int id = familiaDaPalavra(dict, index, word);

	if (id == -1) {
		return cluster;
	}

	return cluster;
}

std::vector<int> RhymeEngine::nearestVertices(int v, int k)
{
	return {};
}
}  // namespace modelo::nucleo
