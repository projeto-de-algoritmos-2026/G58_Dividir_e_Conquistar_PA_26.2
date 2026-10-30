#include "AcousticTranslator.hpp"

#include <stdexcept>

namespace modelo::adaptadores {

geometria::Point2D AcousticTranslator::toPoint(const std::vector<nucleo::Phoneme>& rhymePart) {
	if (rhymePart.empty()) {
		throw std::invalid_argument("rima vazia");
	}

	auto coordinatesOf = [&](const std::string& symbol) {
		const auto found = phonemeCoordinates.find(symbol);
		if (found == phonemeCoordinates.end()) {
			throw std::invalid_argument("fonema desconhecido: " + symbol);
		}
		return found->second;
	};

	auto [vowelX, vowelY] = coordinatesOf(rhymePart[0].symbol);

	if (rhymePart.size() == 1) return {vowelX, vowelY};

	double sumX = 0.0;
	double sumY = 0.0;

	for (size_t i = 1; i < rhymePart.size(); i++) {
		auto [coordinateX, coordinateY] = coordinatesOf(rhymePart[i].symbol);
		sumX += coordinateX;
		sumY += coordinateY;
	}

	const double meanX = sumX / static_cast<double>(rhymePart.size() - 1);
	const double meanY= sumY / static_cast<double>(rhymePart.size() - 1);

	return {vowelWeight * vowelX + (1 - vowelWeight) * meanX, vowelWeight * vowelY + (1 - vowelWeight) * meanY};
}

AcousticTranslator::AcousticTranslator(const double vowelWeight)
	: vowelWeight(vowelWeight) {
	initializePhonemeCoordinates();
}

void AcousticTranslator::initializePhonemeCoordinates() {
	// Vogais
	phonemeCoordinates["IY"] = {0.10, 0.90}; phonemeCoordinates["IH"] = {0.20, 0.80};
	phonemeCoordinates["EY"] = {0.20, 0.60}; phonemeCoordinates["EH"] = {0.20, 0.40};
	phonemeCoordinates["AE"] = {0.10, 0.10}; phonemeCoordinates["AA"] = {0.90, 0.10};
	phonemeCoordinates["AO"] = {0.90, 0.40}; phonemeCoordinates["OW"] = {0.90, 0.60};
	phonemeCoordinates["UH"] = {0.80, 0.80}; phonemeCoordinates["UW"] = {0.90, 0.90};
	phonemeCoordinates["AH"] = {0.50, 0.40}; phonemeCoordinates["ER"] = {0.50, 0.50};
	phonemeCoordinates["AY"] = {0.40, 0.30}; phonemeCoordinates["AW"] = {0.70, 0.30};
	phonemeCoordinates["OY"] = {0.60, 0.70};

	// Consoantes
	phonemeCoordinates["P"]  = {0.10, 0.10}; phonemeCoordinates["B"]  = {0.10, 0.15};
	phonemeCoordinates["T"]  = {0.40, 0.10}; phonemeCoordinates["D"]  = {0.40, 0.15};
	phonemeCoordinates["K"]  = {0.80, 0.10}; phonemeCoordinates["G"]  = {0.80, 0.15};
	phonemeCoordinates["CH"] = {0.60, 0.30}; phonemeCoordinates["JH"] = {0.60, 0.35};
	phonemeCoordinates["F"]  = {0.20, 0.50}; phonemeCoordinates["V"]  = {0.20, 0.55};
	phonemeCoordinates["TH"] = {0.30, 0.50}; phonemeCoordinates["DH"] = {0.30, 0.55};
	phonemeCoordinates["S"]  = {0.40, 0.50}; phonemeCoordinates["Z"]  = {0.40, 0.55};
	phonemeCoordinates["SH"] = {0.60, 0.50}; phonemeCoordinates["ZH"] = {0.60, 0.55};
	phonemeCoordinates["HH"] = {0.90, 0.50};
	phonemeCoordinates["M"]  = {0.10, 0.70}; phonemeCoordinates["N"]  = {0.40, 0.70};
	phonemeCoordinates["NG"] = {0.80, 0.70};
	phonemeCoordinates["L"]  = {0.40, 0.80}; phonemeCoordinates["R"]  = {0.50, 0.80};
	phonemeCoordinates["W"]  = {0.10, 0.90}; phonemeCoordinates["Y"]  = {0.70, 0.90};
}
}  // namespace modelo::adaptadores
