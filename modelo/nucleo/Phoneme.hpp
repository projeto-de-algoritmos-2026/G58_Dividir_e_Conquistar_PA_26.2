#ifndef MODELO_NUCLEO_PHONEME_H
#define MODELO_NUCLEO_PHONEME_H

#include <string>

namespace modelo
{
namespace nucleo
{
struct Phoneme
{
public:
	std::string symbol;

	bool isVowel;

	int stress;

};

}  // namespace nucleo
}  // namespace modelo
#endif
