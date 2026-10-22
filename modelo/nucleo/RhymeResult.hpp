#ifndef MODELO_NUCLEO_RHYME_RESULT_H
#define MODELO_NUCLEO_RHYME_RESULT_H

#include <string>
#include <vector>

namespace modelo
{
namespace nucleo
{
struct RhymeResult
{
public:
	std::string word;

	std::vector<std::string> perfect;

	std::vector<std::string> near;

	bool found;

};

}  // namespace nucleo
}  // namespace modelo
#endif
