#ifndef INCLUDE_I_PHONETIC_CONVERTER_H
#define INCLUDE_I_PHONETIC_CONVERTER_H

#include <string>
#include <vector>
#include <list>
#include <assert.h>

#include "PhoneticPoint.hpp"
#include "phoneme.hpp"

namespace include {

class IPhoneticConverter {

public:
	virtual PhoneticPoint convert(std::vector<Phoneme> phonemes)=0;

};

}  // namespace modelo
#endif
