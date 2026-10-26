#include <gtest/gtest.h>
#include <stdexcept>

#include "modelo/adaptadores/CmuDictionary.hpp"
#include "modelo/nucleo/IDictionaryLookUp.hpp"

using modelo::nucleo::Phoneme;
using modelo::adaptadores::CmuDictionary;
using modelo::nucleo::IDictionaryLookUp;

static const std::string MINI = std::string(FIXTURES_DIR) + "/mini.dict";

// Devolve só os símbolos
static std::vector<std::string> simbolos(const std::vector<Phoneme>& fonemas) {
    std::vector<std::string> resultado;

    for (const Phoneme& fonema : fonemas) {
        resultado.push_back(fonema.symbol);
    }

    return resultado;
}

TEST(CmuDictionaryTest, ArquivoInexistente) {
    CmuDictionary dicionario(MINI);
    IDictionaryLookUp& dic = dicionario;

    EXPECT_THROW(CmuDictionary("nao/existe.dict"), std::runtime_error);
}

TEST(CmuDictionaryTest, LeUmaPalavra) {
    CmuDictionary dicionario(MINI);
    IDictionaryLookUp& dic = dicionario;

    EXPECT_EQ(simbolos(dic.lookUp("dog")), std::vector<std::string>({"D", "AO", "G"}));
}