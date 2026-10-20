#ifndef INCLUDE_RHYME_PAIR_H
#define INCLUDE_RHYME_PAIR_H

#include <string>
#include <vector>
#include <list>
#include <assert.h>

#include "PhoneticPoint.hpp"

namespace include {

struct RhymePair {

public:
	PhoneticPoint a;

	PhoneticPoint b;

	double distance;

};

}  // namespace modelo
#endif
