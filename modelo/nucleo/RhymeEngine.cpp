#include "RhymeEngine.hpp"

#include "WordNormalization.hpp"

#include <queue>
#include <functional>
#include <cmath>

using modelo::nucleo::RhymeIndex;
using modelo::nucleo::Phoneme;

static int familyOfWord(const modelo::nucleo::IDictionaryLookUp& dictionary, const RhymeIndex& index, const std::string& word) {

	const std::vector<Phoneme> phonemes = dictionary.lookUp(word);
	if (phonemes.empty()) return -1;

	const std::vector<Phoneme> rhymePartPhonemes = RhymeIndex::rhymePart(phonemes);
	if (rhymePartPhonemes.empty()) return -1;

	return index.findFamily(RhymeIndex::rhymeKey(rhymePartPhonemes));
}

namespace modelo::nucleo {

RhymeEngine::RhymeEngine(IDictionaryLookUp& dictionary, IPhoneticConverter& converter, geometria::ITriangulator& triangulator, geometria::IClusterer& clusterer)
	: dictionary(dictionary), converter(converter), triangulator(triangulator), clusterer(clusterer), graph(0)
{
}

void RhymeEngine::build(const int clusterCount) {

	for (const DictionaryEntry& entry : dictionary.entries()) {
		auto rhyme = RhymeIndex::rhymePart(entry.phonemes);

		if (rhyme.empty()) continue;

		index.add(entry.word, RhymeIndex::rhymeKey(rhyme), converter.toPoint(rhyme));
	}

	graph = triangulator.triangulate(index.points());

	clusterOfVertex = clusterer.cluster(index.points(), graph, clusterCount);

}

RhymeResult RhymeEngine::findRhymes(const std::string& word, const int maxNear) {

	const std::string normalizedWord = nucleo::normalizedWord(word);

	RhymeResult result;
	result.word = normalizedWord;

	const int familyId = familyOfWord(dictionary, index, normalizedWord);

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

	auto addNearRhymesFrom = [&](const int otherFamilyId) {
		for (const std::string& candidate : index.family(otherFamilyId).words) {
			if (static_cast<int>(result.near.size()) >= maxNear) return;

			if (candidate == normalizedWord) continue;
			if (contains(result.perfect, candidate)) continue;
			if (contains(result.near, candidate)) continue;

			result.near.push_back(candidate);
		}
	};

	for (const int sameVertexFamily : index.familiesAtVertex(family.vertex)) {
		if (sameVertexFamily != familyId) addNearRhymesFrom(sameVertexFamily);
	}

	for (const int nearbyVertex : nearestVertices(family.vertex, maxNear)) {
		for (const int nearbyFamily : index.familiesAtVertex(nearbyVertex)) {
			addNearRhymesFrom(nearbyFamily);
		}
	}

	return result;
}

RhymeCluster RhymeEngine::clusterOf(const std::string& word) {

	RhymeCluster cluster;

	const int familyId = familyOfWord(dictionary, index, word);

	if (familyId == -1) return cluster;

	const int vertex = index.family(familyId).vertex;

	cluster.id = clusterOfVertex[vertex];

	for (int otherVertex = 0; otherVertex < static_cast<int>(index.points().size()); otherVertex++) {

		if (clusterOfVertex[otherVertex] != cluster.id) continue;

		for (const int otherFamilyId: index.familiesAtVertex(otherVertex)) {
			const RhymeFamily& family = index.family(otherFamilyId);
			cluster.keys.push_back(family.key);

			for (const std::string& member : family.words) {
				cluster.words.push_back(member);
			}
		}

	}
	return cluster;
}

std::vector<int> RhymeEngine::nearestVertices(int origin, const int count) const {

	const auto& points =index.points();
	std::vector<int> nearest;
	std::vector<bool> visited(points.size(), false);

	using Candidate = std::pair<double, int>;
	std::priority_queue<Candidate, std::vector<Candidate>, std::greater<>> heap;
	heap.emplace(0.0, origin);

	while (!heap.empty() && static_cast<int>(nearest.size()) < count) {
		auto [currentDistance, current] = heap.top();
		heap.pop();

		if (visited[current]) continue;

		visited[current] = true;

		if (current != origin) nearest.push_back(current);

		for (int neighbor : graph.neighbors(current)) {
			if (!visited[neighbor]) {
				const double distance = points[neighbor].distanceTo(points[origin]);
				heap.emplace(distance, neighbor);
			}
		}
	}
	return nearest;
}
}  // namespace modelo::nucleo
