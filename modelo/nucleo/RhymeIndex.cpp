#include "RhymeIndex.hpp"

namespace modelo
{
namespace nucleo
{

void RhymeIndex::add(const std::string& word, const std::string& key, const modelo::geometria::Point2D& point)
{
}

int RhymeIndex::findFamily(const std::string& key) const
{
	return 0;
}

const std::vector<modelo::geometria::Point2D>& RhymeIndex::points() const
{
	return points_;
}

std::string RhymeIndex::rhymeKey(const std::vector<Phoneme>& rhymePart)
{
	return {};
}

const RhymeFamily& RhymeIndex::family(int id) const
{
	return families.at(id);
}

const std::vector<int>& RhymeIndex::familiesAtVertex(int v) const
{
	return familiesAt.at(v);
}

std::vector<Phoneme> RhymeIndex::rhymePart(const std::vector<Phoneme>& phonemes)
{
	return {};
}
}  // namespace nucleo
}  // namespace modelo
