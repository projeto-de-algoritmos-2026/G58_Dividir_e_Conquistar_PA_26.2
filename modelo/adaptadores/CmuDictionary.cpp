#include "CmuDictionary.hpp"

#include "../nucleo/WordNormalization.hpp"

#include <stdexcept>
#include <fstream>
#include <sstream>

static modelo::nucleo::Phoneme parsePhoneme(const std::string& token) {
	if (std::isdigit(static_cast<unsigned char>(token.back()))) {
		return {token.substr(0, token.size() -1), true, token.back() - '0'};
	}
	return {token, false, -1};
}

namespace modelo::adaptadores {

CmuDictionary::CmuDictionary(const std::string& path) {
	std::ifstream file(path);
	if (!file) {
		throw std::runtime_error("Não foi possível abrir o dicionário: " + path);
	}

	std::string line;

	while (std::getline(file, line)) {

		if (line.empty() || line.substr(0, 3) == ";;;") continue;

		if (auto commentStart = line.find('#'); commentStart != std::string::npos) line.erase(commentStart);

		std::istringstream fields(line);
		std::string word;
		if (!(fields >> word)) continue;

		if (auto variantStart = word.find('('); variantStart != std::string::npos) word.erase(variantStart);

		std::vector<nucleo::Phoneme> phonemes;
		std::string token;

		while (fields >> token) {
			phonemes.push_back(parsePhoneme(token));
		}

		std::string normalizedWord = nucleo::normalizedWord(word);

		int entryIndex = static_cast<int>(allEntries.size());
		allEntries.push_back({normalizedWord, phonemes});
		entryByWord.insert({normalizedWord, entryIndex});

	}

}

std::vector<nucleo::Phoneme> CmuDictionary::lookUp(const std::string& word) const {
	if (const auto found = entryByWord.find(nucleo::normalizedWord(word)); found == entryByWord.end()) {
		return {};
	} else {
		return allEntries[found->second].phonemes;
	}
}

}  // namespace modelo::adaptadores
