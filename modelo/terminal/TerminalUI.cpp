#include "TerminalUI.hpp"

#include <iostream>
#include <sstream>
#include <string>

static const int MOSTRAR = 20;

static void listar(const std::vector<std::string>& palavras) {
	int total = static_cast<int>(palavras.size());
	for (int i = 0; i < total && i < MOSTRAR; i++) {
		std::cout << (i == 0 ? " " : ", ") << palavras[i];
	}
	if (total > MOSTRAR) {
		std::cout << " ... (+ " << total - MOSTRAR << ")";
	}
	std::cout <<'\n';
}

namespace modelo::terminal {

TerminalUI::TerminalUI(modelo::nucleo::IRhymeFinder& finder)
	: finder(finder) {
}

void TerminalUI::run() {
	std::cout << "Digite 'ajuda' para ver os comandos.\n";
	std::string texto;

	while (true) {
		std::cout << "> " << std::flush;
		if (!std::getline(std::cin, texto)) break;

		std::istringstream linha(texto);
		std::string comando;
		if (!(linha >> comando)) continue;

		if (comando == "sair") break;;

		if (comando == "ajuda") {
			std::cout << "	rimas <palavra> [n]    rimas perfeitas e as n próximas (padrão 10)\n"
			          << "	cluster <palavra>      o grupo de rimas da palavra\n"
			          << "	ajuda                  esta lista\n"
			          << "	sair                   ecerra\n";
			continue;
		}

		if (comando == "rimas") {
			std::string palavra;
			if (!(linha >> palavra)) {
				std::cout << "Usp rimas <palavra> [n]\n";
				continue;
			}

			int n = 10;
			std::string textoN;
			if (linha >> textoN) {
				try {
					n = std::stoi(textoN);
				} catch (const std::exception&) {
					std::cout << "n precisa ser um número\n";
					continue;
				}
			}

			printRhymes(finder.findRhymes(palavra, n));
			continue;
		}

		if (comando == "cluster" ) {
			std::string palavra;
			if (!(linha >> palavra)) {
				std::cout << "Uso: cluster <palavra>\n";
				continue;
			}
			printCluster(finder.clusterOf(palavra));
			continue;
		}

		std::cout << "Comando desconhecido: " << comando << ". Digite 'ajuda'.\n";
	}
}

void TerminalUI::printRhymes(const modelo::nucleo::RhymeResult& result) {
	if (!result.found) {
		std::cout << "Palavra não encontrada: " + result.word << '\n';
		return;
	} else {
		std::cout << "Rimas perfeitas (" << result.perfect.size() << "): \n";
		listar(result.perfect);
		std::cout << "Rimas próximas (" << result.near.size() << "): \n";
		listar(result.near);
	}
}

void TerminalUI::printCluster(const modelo::nucleo::RhymeCluster& cluster) {
	if (cluster.id == -1) {
		std::cout << "Palavra não encontrada.\n";
		return;
	}
	std::cout << "Cluster " << cluster.id << ": " << cluster.keys.size() << "famílias, " << cluster.words.size() << " palavras\n";
	listar(cluster.words);
}
}  // namespace modelo::terminal
