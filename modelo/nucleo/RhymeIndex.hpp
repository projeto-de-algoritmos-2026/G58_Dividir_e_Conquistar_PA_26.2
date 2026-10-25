#ifndef MODELO_NUCLEO_RHYME_INDEX_H
#define MODELO_NUCLEO_RHYME_INDEX_H

#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "modelo/nucleo/RhymeFamily.hpp"
#include "modelo/nucleo/Phoneme.hpp"
#include "modelo/geometria/Point2D.hpp"

namespace modelo::nucleo {
class RhymeIndex {
private:
	std::vector<RhymeFamily> families;

	std::unordered_map<std::string,int> byKey;

	std::vector<modelo::geometria::Point2D> points_;

	std::vector<std::vector<int>> familiesAt;

	std::map<std::pair<double,double>,int> byPoint;

public:
	void add(const std::string& word, const std::string& key, const modelo::geometria::Point2D& point);

	int findFamily(const std::string& key) const;

	const std::vector<modelo::geometria::Point2D>& points() const;

	static std::string rhymeKey(const std::vector<Phoneme>& rhymePart);

	const RhymeFamily& family(int id) const;

	const std::vector<int>& familiesAtVertex(int v) const;

	static std::vector<Phoneme> rhymePart(const std::vector<Phoneme>& phonemes);

};

}  // namespace modelo::nucleo
#endif
