#ifndef INCLUDE_RHYME_ENGINE_H
#define INCLUDE_RHYME_ENGINE_H

#include <string>
#include <vector>
#include <list>
#include <assert.h>

#include "RhymePair.hpp"
#include "IDictionaryLookUp.hpp"
#include "IPhoneticConverter.hpp"
#include "IClosestPair.hpp"

namespace include {

class RhymeEngine {

public:
	RhymePair getClosestRhyme(std::string word);

	RhymeEngine(IDictionaryLookUp* dict, IPhoneticConverter* conv, IClosestPair* finder);

};

}  // namespace modelo
#endif
