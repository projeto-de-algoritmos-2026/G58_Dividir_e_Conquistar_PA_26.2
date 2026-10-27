#include "RhymeEngine.hpp"

#include <queue>
#include <functional>
#include <cmath>

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

RhymeResult RhymeEngine::findRhymes(const std::string& word, int maxNear) {

	RhymeResult r;
	r.word = word;
	r.found = false;

	int id = familiaDaPalavra(dict, index, word);

	if (id == -1) {
		return r;
	}

	r.found = true;

	const RhymeFamily& fam = index.family(id);

	for (const std::string& w : fam.words) {
		if (w != word) {
			r.perfect.push_back(w);
		}
	}

	auto contem = [](const std::vector<std::string>& lista, const std::string& w) {
		return std::find(lista.begin(), lista.end(), w) != lista.end();
	};

	auto acrescentar = [&](int f) {
		for (const std::string& w : index.family(f).words) {
			if (static_cast<int>(r.near.size()) >= maxNear) return;

			if (w == word) continue;
			if (contem(r.perfect, w)) continue;
			if (contem(r.near, w)) continue;

			r.near.push_back(w);
		}
	};

	for (int f : index.familiesAtVertex(fam.vertex)) {
		if (f != id) acrescentar(f);
	}

	for (int u : nearestVertices(fam.vertex, maxNear)) {
		for (int f : index.familiesAtVertex(u)) {
			acrescentar(f);
		}
	}

	return r;
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

std::vector<int> RhymeEngine::nearestVertices(int v, int k) {

	const auto& p =index.points();
	std::vector<int> resultado;
	std::vector<bool> visitado(p.size(), false);

	using Item = std::pair<double, int>;
	std::priority_queue<Item, std::vector<Item>, std::greater<Item>> fila;
	fila.push({0.0, v});

	while (!fila.empty() && static_cast<int>(resultado.size()) < k) {
		Item atual = fila.top();
		fila.pop();
		int u = atual.second;

		if (visitado[u]) {
			continue;
		}
		visitado[u] = true;

		if (u != v) {
			resultado.push_back(u);
		}

		for (int w : graph.neighbors(u)) {
			if (!visitado[w]) {
				double d = std::hypot(p[w].x - p[v].x, p[w].y - p[v].y);
				fila.push({d, w});
			}
		}
	}
	return resultado;
}
}  // namespace modelo::nucleo
