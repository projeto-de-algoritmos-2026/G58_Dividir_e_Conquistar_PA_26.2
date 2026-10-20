#ifndef MODELO_CMU_DICTIONARY_H
#define MODELO_CMU_DICTIONARY_H

#include <string>
#include <vector>
#include <list>
#include <assert.h>

#include "modelo/IDictionaryLookUp.hpp"
#include "modelo/Phoneme.hpp"
#include "std/vector.hpp"

namespace include
{
class CmuDictionary : public IDictionaryLookUp
{
public:
	std::vector<Phoneme> lookUp(string word);

};

}  // namespace modelo
#endif
