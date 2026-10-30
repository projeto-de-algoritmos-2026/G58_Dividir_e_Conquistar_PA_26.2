#include "RhymeIndex.hpp"

#include <algorithm>

namespace modelo::nucleo {

void RhymeIndex::add(const std::string& word, const std::string& key, const modelo::geometria::Point2D& point) {
	if (const auto existingFamily = familyByKey.find(key); existingFamily != familyByKey.end()) {
		std::vector<std::string>& words = families[existingFamily->second].words;

		if (std::find(words.begin(), words.end(), word) == words.end()) {
			words.push_back(word);
		}

		return;
	}

	int vertex;
	auto existingVertex = vertexByPoint.find({point.x, point.y});

	if (existingVertex != vertexByPoint.end()) {
		vertex = existingVertex->second;
	} else {
		vertex = static_cast<int>(vertexPoints.size());
		vertexPoints.push_back(point);
		familiesByVertex.push_back({});
		vertexByPoint[{point.x, point.y}] = vertex;
	}

	const int familyId = static_cast<int>(families.size());

	families.push_back({key, {word}, vertex});

	familyByKey[key] = familyId;

	familiesByVertex[vertex].push_back(familyId);

}

int RhymeIndex::findFamily(const std::string& key) const {
	const auto found = familyByKey.find(key);
	return found == familyByKey.end() ? -1 : found->second;
}

const std::vector<modelo::geometria::Point2D>& RhymeIndex::points() const {
	return vertexPoints;
}

std::string RhymeIndex::rhymeKey(const std::vector<Phoneme>& rhymePart) {

	std::string key;

	for (size_t i = 0; i < rhymePart.size(); i++) {
		if (i > 0) {
			key += ' ';
		}
		key += rhymePart[i].symbol;
	}

	return key;
}

const RhymeFamily& RhymeIndex::family(int familyId) const
{
	return families.at(familyId);
}

const std::vector<int>& RhymeIndex::familiesAtVertex(int vertex) const
{
	return familiesByVertex.at(vertex);
}

std::vector<Phoneme> RhymeIndex::rhymePart(const std::vector<Phoneme>& phonemes) {

	int rhymeStart = -1;

	for (int i = static_cast<int>(phonemes.size()) - 1; i >= 0; i--) {
		if (phonemes[i].isVowel && phonemes[i].stress >= 1) {
			rhymeStart = i;
			break;
		}
	}

	if (rhymeStart == -1) {
		for (int i = static_cast<int>(phonemes.size()) - 1; i >= 0; i--) {
			if (phonemes[i].isVowel) {
				rhymeStart = i;
				break;
			}
		}
	}

	if (rhymeStart == -1) {
		return {};
	}

	return std::vector<Phoneme>(phonemes.begin() + rhymeStart, phonemes.end());
}
}  // namespace modelo::nucleo
