#include "CmuDictionary.hpp"

#include "../nucleo/WordNormalization.hpp"

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cctype>

static modelo::nucleo::Phoneme parsePhoneme(const std::string& token) {
	if (std::isdigit(static_cast<unsigned char>(token.back()))) {
		return {token.substr(0, token.size() -1), true, token.back() - '0'};
	} else {
		return {token, false, -1};
	}
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

		auto commentStart = line.find('#');

		if (commentStart != std::string::npos) line.erase(commentStart);

		std::istringstream fields(line);
		std::string word;
		if (!(fields >> word)) continue;

		auto variantStart = word.find('(');
		if (variantStart != std::string::npos) word.erase(variantStart);

		std::vector<modelo::nucleo::Phoneme> phonemes;
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

std::vector<modelo::nucleo::Phoneme> CmuDictionary::lookUp(const std::string& word) const {
	auto found = entryByWord.find(nucleo::normalizedWord(word));

	if (found == entryByWord.end()) {
		return {};
	} else {
		return allEntries[found->second].phonemes;
	}
}

const std::vector<modelo::nucleo::DictionaryEntry>& CmuDictionary::entries() const {
	return allEntries;
}
}  // namespace modelo::adaptadores
