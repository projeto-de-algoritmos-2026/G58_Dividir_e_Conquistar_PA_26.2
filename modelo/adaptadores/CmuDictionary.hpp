#ifndef MODELO_ADAPTADORES_CMU_DICTIONARY_H
#define MODELO_ADAPTADORES_CMU_DICTIONARY_H

#include <string>
#include <unordered_map>
#include <vector>

#include "modelo/nucleo/IDictionaryLookUp.hpp"
#include "modelo/nucleo/DictionaryEntry.hpp"
#include "modelo/nucleo/Phoneme.hpp"

namespace modelo::adaptadores {
class CmuDictionary : public modelo::nucleo::IDictionaryLookUp {
private:
	std::vector<modelo::nucleo::DictionaryEntry> entries_;

	std::unordered_map<std::string,int> byWord;

public:
	CmuDictionary(const std::string& path);

	std::vector<modelo::nucleo::Phoneme> lookUp(const std::string& word) const override;

	const std::vector<modelo::nucleo::DictionaryEntry>& entries() const override;

};

}  // namespace modelo::adaptadores
#endif
