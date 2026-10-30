#ifndef MODELO_TERMINAL_TERMINAL_U_I_H
#define MODELO_TERMINAL_TERMINAL_U_I_H

#include "modelo/nucleo/IRhymeFinder.hpp"
#include "modelo/nucleo/RhymeResult.hpp"
#include "modelo/nucleo/RhymeCluster.hpp"

namespace modelo::terminal {
class TerminalUI {

	nucleo::IRhymeFinder& finder;

	static void printRhymes(const nucleo::RhymeResult& result);

	static void printCluster(const nucleo::RhymeCluster& cluster);

public:
	explicit TerminalUI(nucleo::IRhymeFinder& finder)
		: finder(finder) {
	}

	void run() const;

};

}  // namespace modelo::terminal
#endif
