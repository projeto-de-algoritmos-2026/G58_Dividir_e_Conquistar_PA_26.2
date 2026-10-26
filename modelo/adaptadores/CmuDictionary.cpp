#include "CmuDictionary.hpp"

#include <stdexcept>
#include <fstream>

namespace modelo::adaptadores {

CmuDictionary::CmuDictionary(const std::string& path) {
	std::ifstream arquivo(path);
	if (!arquivo) {
		throw std::runtime_error("Não foi possível abrir o dicionário: " + path);
	}
}

std::vector<modelo::nucleo::Phoneme> CmuDictionary::lookUp(const std::string& word) const
{
	return {};
}

const std::vector<modelo::nucleo::DictionaryEntry>& CmuDictionary::entries() const
{
	return entries_;
}
}  // namespace modelo::adaptadores
