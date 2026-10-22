#ifndef MODELO_NUCLEO_I_PHONETIC_CONVERTER_H
#define MODELO_NUCLEO_I_PHONETIC_CONVERTER_H

#include <vector>

#include "modelo/nucleo/Phoneme.hpp"
#include "modelo/geometria/Point2D.hpp"

namespace modelo
{
namespace nucleo
{
class IPhoneticConverter
{
public:
	virtual ~IPhoneticConverter() = default;

	virtual modelo::geometria::Point2D toPoint(const std::vector<Phoneme>& rhymePart) = 0;

};

}  // namespace nucleo
}  // namespace modelo
#endif
