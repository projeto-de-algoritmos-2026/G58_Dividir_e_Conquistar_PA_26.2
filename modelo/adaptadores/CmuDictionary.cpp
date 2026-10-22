#include "CmuDictionary.hpp"

namespace modelo
{
namespace adaptadores
{

CmuDictionary::CmuDictionary(const std::string& path)
{
}

std::vector<modelo::nucleo::Phoneme> CmuDictionary::lookUp(const std::string& word) const
{
	return {};
}

const std::vector<modelo::nucleo::DictionaryEntry>& CmuDictionary::entries() const
{
	return entries_;
}
}  // namespace adaptadores
}  // namespace modelo
