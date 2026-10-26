#ifndef MODELO_NUCLEO_RHYME_ENGINE_H
#define MODELO_NUCLEO_RHYME_ENGINE_H

#include <string>
#include <vector>

#include "modelo/nucleo/IRhymeFinder.hpp"
#include "modelo/nucleo/IDictionaryLookUp.hpp"
#include "modelo/nucleo/IPhoneticConverter.hpp"
#include "modelo/nucleo/RhymeIndex.hpp"
#include "modelo/nucleo/RhymeResult.hpp"
#include "modelo/nucleo/RhymeCluster.hpp"
#include "modelo/geometria/ITriangulator.hpp"
#include "modelo/geometria/IClusterer.hpp"
#include "modelo/geometria/DelaunayGraph.hpp"

namespace modelo:: nucleo {
class RhymeEngine : public IRhymeFinder {
private:
	IDictionaryLookUp& dict;

	IPhoneticConverter& conv;

	modelo::geometria::ITriangulator& tri;

	modelo::geometria::IClusterer& clusterer;

	RhymeIndex index;

	modelo::geometria::DelaunayGraph graph;

	std::vector<int> labels;

private:
	std::vector<int> nearestVertices(int v, int k);

public:
	RhymeEngine(IDictionaryLookUp& dict, IPhoneticConverter& conv, modelo::geometria::ITriangulator& tri, modelo::geometria::IClusterer& clusterer);

	void build(int k);

	RhymeResult findRhymes(const std::string& word, int maxNear) override;

	RhymeCluster clusterOf(const std::string& word) override;

};

}  // namespace modelo::nucleo
#endif
