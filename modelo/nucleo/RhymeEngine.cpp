#include "RhymeEngine.hpp"

#include <queue>
#include <functional>
#include <cmath>

using modelo::nucleo::RhymeIndex;
using modelo::nucleo::Phoneme;

static int familyOfWord(const modelo::nucleo::IDictionaryLookUp& dictionary, const RhymeIndex& index, const std::string& word) {

	std::vector<Phoneme> phonemes = dictionary.lookUp(word);
	if (phonemes.empty()) return -1;

	std::vector<Phoneme> rhymePartPhonemes = RhymeIndex::rhymePart(phonemes);
	if (rhymePartPhonemes.empty()) return -1;

	return index.findFamily(RhymeIndex::rhymeKey(rhymePartPhonemes));
}

static std::string toLowerCase(std::string s) {
	for (char& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
	return s;
}

namespace modelo::nucleo {

RhymeEngine::RhymeEngine(IDictionaryLookUp& dictionary, IPhoneticConverter& converter, modelo::geometria::ITriangulator& triangulator, modelo::geometria::IClusterer& clusterer)
	: dictionary(dictionary), converter(converter), triangulator(triangulator), clusterer(clusterer), graph(0)
{
}

void RhymeEngine::build(int clusterCount) {

	for (const DictionaryEntry& entry : dictionary.entries()) {
		auto rhyme = RhymeIndex::rhymePart(entry.phonemes);

		if (rhyme.empty()) continue;

		index.add(entry.word, RhymeIndex::rhymeKey(rhyme), converter.toPoint(rhyme));
	}

	graph = triangulator.triangulate(index.points());

	clusterOfVertex = clusterer.cluster(index.points(), graph, clusterCount);

}

RhymeResult RhymeEngine::findRhymes(const std::string& word, int maxNear) {

	std::string normalizedWord = toLowerCase(word);

	RhymeResult result;
	result.word = normalizedWord;
	result.found = false;

	int familyId = familyOfWord(dictionary, index, normalizedWord);

	if (familyId == -1) return result;

	result.found = true;

	const RhymeFamily& family = index.family(familyId);

	for (const std::string& candidate : family.words) {
		if (candidate != normalizedWord) {
			result.perfect.push_back(candidate);
		}
	}

	auto contains = [](const std::vector<std::string>& lista, const std::string& words) {
		return std::find(lista.begin(), lista.end(), words) != lista.end();
	};

	auto addNearRhymesFrom = [&](int familyId) {
		for (const std::string& candidate : index.family(familyId).words) {
			if (static_cast<int>(result.near.size()) >= maxNear) return;

			if (candidate == normalizedWord) continue;
			if (contains(result.perfect, candidate)) continue;
			if (contains(result.near, candidate)) continue;

			result.near.push_back(candidate);
		}
	};

	for (int sameVertexFamily : index.familiesAtVertex(family.vertex)) {
		if (sameVertexFamily != familyId) addNearRhymesFrom(sameVertexFamily);
	}

	for (int nearbyVertex : nearestVertices(family.vertex, maxNear)) {
		for (int nearbyFamily : index.familiesAtVertex(nearbyVertex)) {
			addNearRhymesFrom(nearbyFamily);
		}
	}

	return result;
}

RhymeCluster RhymeEngine::clusterOf(const std::string& word) {

	RhymeCluster cluster;
	cluster.id = -1;

	int familyId = familyOfWord(dictionary, index, word);

	if (familyId == -1) return cluster;

	int vertex = index.family(familyId).vertex;

	cluster.id = clusterOfVertex[vertex];

	for (int otherVertex = 0; otherVertex < static_cast<int>(index.points().size()); otherVertex++) {

		if (clusterOfVertex[otherVertex] != cluster.id) continue;

		for (int otherFamilyId: index.familiesAtVertex(otherVertex)) {
			const RhymeFamily& family = index.family(otherFamilyId);
			cluster.keys.push_back(family.key);

			for (const std::string& member : family.words) {
				cluster.words.push_back(member);
			}
		}

	}
	return cluster;
}

std::vector<int> RhymeEngine::nearestVertices(int origin, int count) {

	const auto& points =index.points();
	std::vector<int> nearest;
	std::vector<bool> visited(points.size(), false);

	using Item = std::pair<double, int>;
	std::priority_queue<Item, std::vector<Item>, std::greater<Item>> heap;
	heap.push({0.0, origin});

	while (!heap.empty() && static_cast<int>(nearest.size()) < count) {
		Item candidate = heap.top();
		heap.pop();
		int current = candidate.second;

		if (visited[current]) continue;

		visited[current] = true;

		if (current != origin) nearest.push_back(current);

		for (int neighbor : graph.neighbors(current)) {
			if (!visited[neighbor]) {
				double distance = std::hypot(points[neighbor].x - points[origin].x, points[neighbor].y - points[origin].y);
				heap.push({distance, neighbor});
			}
		}
	}
	return nearest;
}
}  // namespace modelo::nucleo
