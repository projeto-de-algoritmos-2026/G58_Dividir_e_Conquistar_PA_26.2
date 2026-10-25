#include "RhymeIndex.hpp"

namespace modelo::nucleo {

void RhymeIndex::add(const std::string& word, const std::string& key, const modelo::geometria::Point2D& point)
{
}

int RhymeIndex::findFamily(const std::string& key) const {
	auto it = byKey.find(key);
	return it == byKey.end() ? -1 : it->second;
}

const std::vector<modelo::geometria::Point2D>& RhymeIndex::points() const
{
	return points_;
}

std::string RhymeIndex::rhymeKey(const std::vector<Phoneme>& rhymePart) {

	std::string resultado;

	for (size_t i = 0; i < rhymePart.size(); i++) {
		if (i > 0) {
			resultado += ' ';
		}
		resultado += rhymePart[i].symbol;
	}

	return resultado;
}

const RhymeFamily& RhymeIndex::family(int id) const
{
	return families.at(id);
}

const std::vector<int>& RhymeIndex::familiesAtVertex(int v) const
{
	return familiesAt.at(v);
}

std::vector<Phoneme> RhymeIndex::rhymePart(const std::vector<Phoneme>& phonemes) {

	int pos = -1;

	for (int i = static_cast<int>(phonemes.size()) - 1; i >= 0; i--) {
		if (phonemes[i].isVowel && phonemes[i].stress >= 1) {
			pos = i;
			break;
		}
	}

	if (pos == -1) {
		for (int i = static_cast<int>(phonemes.size()) - 1; i >= 0; i--) {
			if (phonemes[i].isVowel) {
				pos = i;
				break;
			}
		}
	}

	if (pos == -1) {
		return {};
	}

	return std::vector<Phoneme>(phonemes.begin() + pos, phonemes.end());
}
}  // namespace modelo::nucleo
