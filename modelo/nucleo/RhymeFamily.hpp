#ifndef MODELO_NUCLEO_RHYME_FAMILY_H
#define MODELO_NUCLEO_RHYME_FAMILY_H

#include <string>
#include <vector>

namespace modelo
{
namespace nucleo
{
struct RhymeFamily
{
public:
	std::string key;

	std::vector<std::string> words;

	int vertex;

};

}  // namespace nucleo
}  // namespace modelo
#endif
