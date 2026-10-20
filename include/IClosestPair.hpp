#ifndef INCLUDE_I_CLOSEST_PAIR_H
#define INCLUDE_I_CLOSEST_PAIR_H

#include <string>
#include <vector>
#include <list>
#include <assert.h>

#include "RhymePair.hpp"
#include "PhoneticPoint.hpp"

namespace include {

class IClosestPair {

public:
	virtual RhymePair find(std::vector<PhoneticPoint> points)=0;

};

}  // namespace modelo
#endif
