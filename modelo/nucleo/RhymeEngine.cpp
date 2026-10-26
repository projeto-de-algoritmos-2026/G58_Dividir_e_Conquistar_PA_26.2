#include "RhymeEngine.hpp"

using modelo::nucleo::RhymeIndex;
using modelo::nucleo::Phoneme;

static int familiaDaPalavra(const modelo::nucleo::IDictionaryLookUp& dict, const RhymeIndex& index, const std::string& word) {

	std::vector<Phoneme> phonemes = dict.lookUp(word);
	if (phonemes.empty()) return -1;

	std::vector<Phoneme> rhymePartPhonemes = RhymeIndex::rhymePart(phonemes);
	if (rhymePartPhonemes.empty()) return -1;

	return index.findFamily(RhymeIndex::rhymeKey(rhymePartPhonemes));
}

namespace modelo::nucleo {

RhymeEngine::RhymeEngine(IDictionaryLookUp& dict, IPhoneticConverter& conv, modelo::geometria::ITriangulator& tri, modelo::geometria::IClusterer& clusterer)
	: dict(dict), conv(conv), tri(tri), clusterer(clusterer), graph(0)
{
}

void RhymeEngine::build(int k) {

	for (const DictionaryEntry& e : dict.entries()) {
		auto parte = RhymeIndex::rhymePart(e.phonemes);

		if (parte.empty()) {
			continue;
		}

		index.add(e.word, RhymeIndex::rhymeKey(parte), conv.toPoint(parte));
	}

	graph = tri.triangulate(index.points());

	labels = clusterer.cluster(index.points(), graph, k);

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

	int v = index.family(id).vertex;

	cluster.id = labels[v];

	for (int u = 0; u < static_cast<int>(index.points().size()); u++) {
		if (labels[u] != cluster.id) {
			continue;
		}

		for (int f: index.familiesAtVertex(u)) {
			const RhymeFamily& familia = index.family(f);
			cluster.keys.push_back(familia.key);

			for (const std::string& palavra : familia.words) {
				cluster.words.push_back(palavra);
			}
		}

	}
	return cluster;
}

std::vector<int> RhymeEngine::nearestVertices(int v, int k)
{
	return {};
}
}  // namespace modelo::nucleo
