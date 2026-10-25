#include "AcousticTranslator.hpp"

#include <stdexcept>

namespace modelo::adaptadores {

modelo::geometria::Point2D AcousticTranslator::toPoint(const std::vector<modelo::nucleo::Phoneme>& rhymePart) {
	if (rhymePart.empty()) {
		throw std::invalid_argument("rima vazia");
	}

	auto coordenada = [&](const std::string& s) {
		auto it = phonemeMap.find(s);
		if (it == phonemeMap.end()) {
			throw std::invalid_argument("fonema desconhecido: " + s);
		}
		return it->second;
	};

	auto vogal = coordenada(rhymePart[0].symbol);

	if (rhymePart.size() == 1) {
		return {vogal.first, vogal.second};
	}

	double somaX = 0.0;
	double somaY = 0.0;

	for (size_t i = 1; i < rhymePart.size(); i++) {
		auto c = coordenada(rhymePart[i].symbol);
		somaX += c.first;
		somaY += c.second;
	}

	double mediaX = somaX / static_cast<double>(rhymePart.size() - 1);
	double mediaY= somaY / static_cast<double>(rhymePart.size() - 1);

	return {vowelWeight * vogal.first + (1 - vowelWeight) * mediaX, vowelWeight * vogal.second + (1 - vowelWeight) * mediaY};
}

AcousticTranslator::AcousticTranslator(double vowelWeight)
	: vowelWeight(vowelWeight) {
	initializeMap();
}

void AcousticTranslator::initializeMap() {
	// Vogais
	phonemeMap["IY"] = {0.10, 0.90}; phonemeMap["IH"] = {0.20, 0.80};
	phonemeMap["EY"] = {0.20, 0.60}; phonemeMap["EH"] = {0.20, 0.40};
	phonemeMap["AE"] = {0.10, 0.10}; phonemeMap["AA"] = {0.90, 0.10};
	phonemeMap["AO"] = {0.90, 0.40}; phonemeMap["OW"] = {0.90, 0.60};
	phonemeMap["UH"] = {0.80, 0.80}; phonemeMap["UW"] = {0.90, 0.90};
	phonemeMap["AH"] = {0.50, 0.40}; phonemeMap["ER"] = {0.50, 0.50};
	phonemeMap["AY"] = {0.40, 0.30}; phonemeMap["AW"] = {0.70, 0.30};
	phonemeMap["OY"] = {0.60, 0.70};

	// Consoantes
	phonemeMap["P"]  = {0.10, 0.10}; phonemeMap["B"]  = {0.10, 0.15};
	phonemeMap["T"]  = {0.40, 0.10}; phonemeMap["D"]  = {0.40, 0.15};
	phonemeMap["K"]  = {0.80, 0.10}; phonemeMap["G"]  = {0.80, 0.15};
	phonemeMap["CH"] = {0.60, 0.30}; phonemeMap["JH"] = {0.60, 0.35};
	phonemeMap["F"]  = {0.20, 0.50}; phonemeMap["V"]  = {0.20, 0.55};
	phonemeMap["TH"] = {0.30, 0.50}; phonemeMap["DH"] = {0.30, 0.55};
	phonemeMap["S"]  = {0.40, 0.50}; phonemeMap["Z"]  = {0.40, 0.55};
	phonemeMap["SH"] = {0.60, 0.50}; phonemeMap["ZH"] = {0.60, 0.55};
	phonemeMap["HH"] = {0.90, 0.50};
	phonemeMap["M"]  = {0.10, 0.70}; phonemeMap["N"]  = {0.40, 0.70};
	phonemeMap["NG"] = {0.80, 0.70};
	phonemeMap["L"]  = {0.40, 0.80}; phonemeMap["R"]  = {0.50, 0.80};
	phonemeMap["W"]  = {0.10, 0.90}; phonemeMap["Y"]  = {0.70, 0.90};
}
}  // namespace modelo::adaptadores
