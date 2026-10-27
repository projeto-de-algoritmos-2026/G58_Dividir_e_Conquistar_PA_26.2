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

int main(int argc, char** argv) {
	try {

		std::string caminho = argc > 1 ? argv[1] : "../data/cmudict.dict";

		int k = argc > 2 ? std::stoi(argv[2]) : 15;

		CmuDictionary dicionario(caminho);
		AcousticTranslator tradutor(0.9);
		DivideConquerDelaunay triangulador;
		KruskalClusterer clusterizador;
		RhymeEngine engine(dicionario, tradutor, triangulador, clusterizador);

		auto inicio = std::chrono::steady_clock::now();

		engine.build(k);

		auto fim = std::chrono::steady_clock::now();

		auto diff = std::chrono::duration<double, std::milli>(fim - inicio).count();

		std::cout << "Índice pronto em " << diff << "ms (k = " << k << ")" << std::endl;

		TerminalUI ui(engine);
		ui.run();

	} catch (const std::exception& e) {
		std::cerr << "Erro: " << e.what() << '\n';
		return 1;
	}
	return 0;
}
