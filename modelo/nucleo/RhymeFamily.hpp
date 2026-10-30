#ifndef MODELO_NUCLEO_RHYME_FAMILY_H
#define MODELO_NUCLEO_RHYME_FAMILY_H

#include <string>
#include <vector>

namespace modelo::nucleo {
struct RhymeFamily {

	std::string key;

	std::vector<std::string> words;

	int vertex;

};

}  // namespace modelo::nucleo
#endif
