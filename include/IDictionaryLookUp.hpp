#ifndef INCLUDE_I_DICTIONARY_LOOK_UP_H
#define INCLUDE_I_DICTIONARY_LOOK_UP_H

#include <string>
#include <vector>
#include <list>
#include <assert.h>

#include "Phoneme.hpp"

namespace include {

class IDictionaryLookUp {

public:
	virtual std::vector<Phoneme> lookUp(std::string word)=0;

};

}  // namespace modelo
#endif
