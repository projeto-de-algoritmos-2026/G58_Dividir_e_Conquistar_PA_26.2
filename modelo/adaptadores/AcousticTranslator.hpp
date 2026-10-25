#ifndef MODELO_ADAPTADORES_ACOUSTIC_TRANSLATOR_H
#define MODELO_ADAPTADORES_ACOUSTIC_TRANSLATOR_H

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "modelo/nucleo/IPhoneticConverter.hpp"
#include "modelo/nucleo/Phoneme.hpp"
#include "modelo/geometria/Point2D.hpp"

namespace modelo::adaptadores {
class AcousticTranslator : public modelo::nucleo::IPhoneticConverter {
private:
	std::unordered_map<std::string,std::pair<double,double>> phonemeMap;

	double vowelWeight;

private:
	void initializeMap();

public:
	modelo::geometria::Point2D toPoint(const std::vector<modelo::nucleo::Phoneme>& rhymePart) override;

	AcousticTranslator(double vowelWeight);

};

}  // namespace modelo::adaptadores
#endif
