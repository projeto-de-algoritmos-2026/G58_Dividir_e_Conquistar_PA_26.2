#ifndef MODELO_DIVIDE_CONQUER_FINDER_H
#define MODELO_DIVIDE_CONQUER_FINDER_H

#include <string>
#include <vector>
#include <list>
#include <assert.h>

#include "modelo/IClosestPair.hpp"
#include "modelo/RhymePair.hpp"
#include "modelo/PhoneticPoint.hpp"
#include "std/vector.hpp"

namespace include
{
class DivideConquerFinder : public IClosestPair
{
public:
	RhymePair find(std::vector<PhoneticPoint> points);

	RhymePair solve(std::vector<PhoneticPoint> px, std::vector<PhoneticPoint> py);

	RhymePair stripClosest(std::vector<PhoneticPoint> strip, double d);

};

}  // namespace modelo
#endif
