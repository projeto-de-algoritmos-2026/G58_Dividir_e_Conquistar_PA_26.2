#ifndef INCLUDE_PHONEME_H
#define INCLUDE_PHONEME_H

#include <string>
#include <vector>
#include <list>
#include <assert.h>

namespace include {

struct Phoneme {

public:
	std::string symbol;

	bool isVowel;

	int stress;

};

}  // namespace modelo
#endif
