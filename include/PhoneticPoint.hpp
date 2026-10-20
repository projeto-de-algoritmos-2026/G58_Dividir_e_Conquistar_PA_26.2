#ifndef INCLUDE_PHONETIC_POINT_H
#define INCLUDE_PHONETIC_POINT_H

#include <string>
#include <vector>
#include <list>
#include <assert.h>

namespace include {

struct PhoneticPoint {

public:
	std::string word;

	std::string coda;

	double x;

	double y;

};

}  // namespace modelo
#endif
