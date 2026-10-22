#ifndef MODELO_NUCLEO_I_DICTIONARY_LOOK_UP_H
#define MODELO_NUCLEO_I_DICTIONARY_LOOK_UP_H

#include <string>
#include <vector>

#include "modelo/nucleo/Phoneme.hpp"
#include "modelo/nucleo/DictionaryEntry.hpp"

namespace modelo
{
namespace nucleo
{
class IDictionaryLookUp
{
public:
	virtual ~IDictionaryLookUp() = default;

	virtual std::vector<Phoneme> lookUp(const std::string& word) const = 0;

	virtual const std::vector<DictionaryEntry>& entries() const = 0;

};

}  // namespace nucleo
}  // namespace modelo
#endif
