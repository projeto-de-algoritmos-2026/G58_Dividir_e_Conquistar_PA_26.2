#include "TerminalUI.hpp"

namespace modelo
{
namespace terminal
{

TerminalUI::TerminalUI(modelo::nucleo::IRhymeFinder& finder)
	: finder(finder)
{
}

void TerminalUI::run()
{
}

void TerminalUI::printRhymes(const modelo::nucleo::RhymeResult& result)
{
}

void TerminalUI::printCluster(const modelo::nucleo::RhymeCluster& cluster)
{
}
}  // namespace terminal
}  // namespace modelo
