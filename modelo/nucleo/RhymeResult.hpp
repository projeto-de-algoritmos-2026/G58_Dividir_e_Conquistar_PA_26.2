#ifndef MODELO_NUCLEO_RHYME_RESULT_H
#define MODELO_NUCLEO_RHYME_RESULT_H

#include <string>
#include <vector>

namespace modelo::nucleo {
struct RhymeResult {

	std::string word;

	std::vector<std::string> perfect;

	std::vector<std::string> near;

	bool found = false;

};

}  // namespace modelo::nucleo
#endif
