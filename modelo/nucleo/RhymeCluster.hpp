#ifndef MODELO_NUCLEO_RHYME_CLUSTER_H
#define MODELO_NUCLEO_RHYME_CLUSTER_H

#include <string>
#include <vector>

namespace modelo::nucleo {
struct RhymeCluster {
public:
	int id;

	std::vector<std::string> keys;

	std::vector<std::string> words;

};

}  // namespace modelo::nucleo
#endif
