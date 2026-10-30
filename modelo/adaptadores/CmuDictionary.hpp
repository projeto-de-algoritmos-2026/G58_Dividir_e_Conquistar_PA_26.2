#ifndef MODELO_ADAPTADORES_CMU_DICTIONARY_H
#define MODELO_ADAPTADORES_CMU_DICTIONARY_H

#include <string>
#include <unordered_map>
#include <vector>

#include "modelo/nucleo/IDictionaryLookUp.hpp"
#include "modelo/nucleo/DictionaryEntry.hpp"
#include "modelo/nucleo/Phoneme.hpp"

namespace modelo::adaptadores {
class CmuDictionary : public nucleo::IDictionaryLookUp {
private:
	std::vector<nucleo::DictionaryEntry> allEntries;

	std::unordered_map<std::string,int> entryByWord;

public:
	explicit CmuDictionary(const std::string& path);

	[[nodiscard]] std::vector<nucleo::Phoneme> lookUp(const std::string& word) const override;

	[[nodiscard]] const std::vector<nucleo::DictionaryEntry>& entries() const override { return allEntries; }

};

}  // namespace modelo::adaptadores
#endif
