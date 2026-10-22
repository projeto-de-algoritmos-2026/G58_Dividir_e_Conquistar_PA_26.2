#ifndef MODELO_TERMINAL_TERMINAL_U_I_H
#define MODELO_TERMINAL_TERMINAL_U_I_H

#include "modelo/nucleo/IRhymeFinder.hpp"
#include "modelo/nucleo/RhymeResult.hpp"
#include "modelo/nucleo/RhymeCluster.hpp"

namespace modelo
{
namespace terminal
{
class TerminalUI
{
private:
	modelo::nucleo::IRhymeFinder& finder;

private:
	void printRhymes(const modelo::nucleo::RhymeResult& result);

	void printCluster(const modelo::nucleo::RhymeCluster& cluster);

public:
	TerminalUI(modelo::nucleo::IRhymeFinder& finder);

	void run();

};

}  // namespace terminal
}  // namespace modelo
#endif
