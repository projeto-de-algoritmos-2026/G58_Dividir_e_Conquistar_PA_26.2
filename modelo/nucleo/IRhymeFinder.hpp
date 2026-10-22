#ifndef MODELO_NUCLEO_I_RHYME_FINDER_H
#define MODELO_NUCLEO_I_RHYME_FINDER_H

#include <string>

#include "modelo/nucleo/RhymeResult.hpp"
#include "modelo/nucleo/RhymeCluster.hpp"

namespace modelo
{
namespace nucleo
{
class IRhymeFinder
{
public:
	virtual ~IRhymeFinder() = default;

	virtual RhymeResult findRhymes(const std::string& word, int maxNear) = 0;

	virtual RhymeCluster clusterOf(const std::string& word) = 0;

};

}  // namespace nucleo
}  // namespace modelo
#endif
