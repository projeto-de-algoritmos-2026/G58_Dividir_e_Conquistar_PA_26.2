#include <chrono>
#include <iostream>
#include <string>
#include <exception>

#include "modelo/adaptadores/CmuDictionary.hpp"
#include "modelo/adaptadores/AcousticTranslator.hpp"

#include "modelo/geometria/DivideConquerDelaunay.hpp"
#include "modelo/geometria/KruskalClusterer.hpp"

#include "modelo/nucleo/RhymeEngine.hpp"
#include "modelo/terminal/TerminalUI.hpp"

using modelo::adaptadores::CmuDictionary;
using modelo::adaptadores::AcousticTranslator;

using modelo::geometria::DivideConquerDelaunay;
using modelo::geometria::KruskalClusterer;

using modelo::nucleo::RhymeEngine;

using modelo::terminal::TerminalUI;

constexpr double VOWEL_WEIGHT = 0.9;
constexpr int DEFAULT_CLUSTER_COUNT = 15;

int main(int argc, char** argv) {
	try {

		std::string dictionaryPath = argc > 1 ? argv[1] : "data/cmudict.dict";

		int clusterCount = argc > 2 ? std::stoi(argv[2]) : DEFAULT_CLUSTER_COUNT;

		CmuDictionary dictionary(dictionaryPath);
		AcousticTranslator translator(VOWEL_WEIGHT);
		DivideConquerDelaunay triangulator;
		KruskalClusterer clusterer;
		RhymeEngine engine(dictionary, translator, triangulator, clusterer);

		auto start = std::chrono::steady_clock::now();

		engine.build(clusterCount);

		auto end = std::chrono::steady_clock::now();

		auto buildMilliseconds = std::chrono::duration<double, std::milli>(end - start).count();

		std::cout << "Índice pronto em " << buildMilliseconds << "ms (k = " << clusterCount << ")" << std::endl;

		TerminalUI ui(engine);
		ui.run();

	} catch (const std::exception& e) {
		std::cerr << "Erro: " << e.what() << '\n';
		return 1;
	}
	return 0;
}
