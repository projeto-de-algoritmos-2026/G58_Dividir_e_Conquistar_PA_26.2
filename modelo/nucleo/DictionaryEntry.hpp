#ifndef MODELO_NUCLEO_DICTIONARY_ENTRY_H
#define MODELO_NUCLEO_DICTIONARY_ENTRY_H

#include <string>
#include <vector>

#include "modelo/nucleo/Phoneme.hpp"

namespace modelo
{
namespace nucleo
{
struct DictionaryEntry
{
public:
	std::string word;

	std::vector<Phoneme> phonemes;

};

}  // namespace nucleo
}  // namespace modelo
#endif
