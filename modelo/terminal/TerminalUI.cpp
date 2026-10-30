#include "TerminalUI.hpp"

#include <iostream>
#include <sstream>
#include <string>

static constexpr int MAX_WORDS_SHOWN = 20;

static void printWorsList(const std::vector<std::string>& words) {
	const int total = static_cast<int>(words.size());
	for (int i = 0; i < total && i < MAX_WORDS_SHOWN; i++) {
		std::cout << (i == 0 ? " " : ", ") << words[i];
	}
	if (total > MAX_WORDS_SHOWN) {
		std::cout << " ... (+ " << total - MAX_WORDS_SHOWN << ")";
	}
	std::cout <<'\n';
}

namespace modelo::terminal {

void TerminalUI::run() const {
	std::cout << "Digite 'ajuda' para ver os comandos.\n";
	std::string input;

	while (true) {
		std::cout << "> " << std::flush;
		if (!std::getline(std::cin, input)) break;

		std::istringstream tokens(input);
		std::string command;
		if (!(tokens >> command)) continue;

		if (command == "sair") break;

		if (command == "ajuda") {
			std::cout << "	rimas <palavra> [n]    rimas perfeitas e as n próximas (padrão 10)\n"
			          << "	cluster <palavra>      o grupo de rimas da palavra\n"
			          << "	ajuda                  esta lista\n"
			          << "	sair                   ecerra\n";
			continue;
		}

		if (command == "rimas") {
			std::string word;
			if (!(tokens >> word)) {
				std::cout << "Usp rimas <palavra> [n]\n";
				continue;
			}

			int nearCount = 10;
			if (std::string nearCountText; tokens >> nearCountText) {
				try {
					nearCount = std::stoi(nearCountText);
				} catch (const std::exception&) {
					std::cout << "n precisa ser um número\n";
					continue;
				}
			}

			printRhymes(finder.findRhymes(word, nearCount));
			continue;
		}

		if (command == "cluster" ) {
			std::string word;
			if (!(tokens >> word)) {
				std::cout << "Uso: cluster <palavra>\n";
				continue;
			}
			printCluster(finder.clusterOf(word));
			continue;
		}

		std::cout << "Comando desconhecido: " << command << ". Digite 'ajuda'.\n";
	}
}

void TerminalUI::printRhymes(const nucleo::RhymeResult& result) {
	if (!result.found) {
		std::cout << "Palavra não encontrada: " + result.word << '\n';
		return;
	}
	std::cout << "Rimas perfeitas (" << result.perfect.size() << "): \n";
	printWorsList(result.perfect);
	std::cout << "Rimas próximas (" << result.near.size() << "): \n";
	printWorsList(result.near);
}

void TerminalUI::printCluster(const nucleo::RhymeCluster& cluster) {
	if (cluster.id == -1) {
		std::cout << "Palavra não encontrada.\n";
		return;
	}
	std::cout << "Cluster " << cluster.id << ": " << cluster.keys.size() << "famílias, " << cluster.words.size() << " palavras\n";
	printWorsList(cluster.words);
}
}  // namespace modelo::terminal
