#include "CmuDictionary.hpp"

#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cctype>

static modelo::nucleo::Phoneme lerFonema(const std::string& token) {
	if (std::isdigit(static_cast<unsigned char>(token.back()))) {
		return {token.substr(0, token.size() -1), true, token.back() - '0'};
	} else {
		return {token, false, -1};
	}
}

namespace modelo::adaptadores {

CmuDictionary::CmuDictionary(const std::string& path) {
	std::ifstream arquivo(path);
	if (!arquivo) {
		throw std::runtime_error("Não foi possível abrir o dicionário: " + path);
	}

	std::string linha;

	while (std::getline(arquivo, linha)) {

		if (linha.empty() || linha.substr(0, 3) == ";;;") {
			continue;
		}

		auto pos = linha.find('#');

		if (pos != std::string::npos) {
			linha.erase(pos);
		}

		std::istringstream partes(linha);
		std::string palavra;
		if (!(partes >> palavra)) continue;

		auto par = palavra.find('(');
		if (par != std::string::npos) palavra.erase(par);

		std::vector<modelo::nucleo::Phoneme> fonemas;
		std::string token;

		while (partes >> token) {
			fonemas.push_back(lerFonema(token));
		}

		int indice = static_cast<int>(entries_.size());
		entries_.push_back({palavra, fonemas});
		byWord.insert({palavra, indice});

	}

}

std::vector<modelo::nucleo::Phoneme> CmuDictionary::lookUp(const std::string& word) const {
	auto it = byWord.find(word);

	if (it == byWord.end()) {
		return {};
	} else {
		return entries_[it->second].phonemes;
	}
}

const std::vector<modelo::nucleo::DictionaryEntry>& CmuDictionary::entries() const {
	return entries_;
}
}  // namespace modelo::adaptadores
