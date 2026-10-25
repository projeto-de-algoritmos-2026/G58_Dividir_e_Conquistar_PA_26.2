#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "modelo/nucleo/Phoneme.hpp"
#include "modelo/nucleo/RhymeIndex.hpp"

using modelo::nucleo::Phoneme;
using modelo::nucleo::RhymeIndex;

// Monta uma vogal
static Phoneme vogal(const std::string& symbol, int stress) {
    return {symbol, true, stress};
}

// Monta uma consoante. Consoante não tem tônica, stress = -1.
static Phoneme consoante(const std::string& symbol) {
    return {symbol, false, -1};
}

// Devolve só os símbolos
static std::vector<std::string> simbolos(const std::vector<Phoneme>& fonemas) {
    std::vector<std::string> resultado;

    for (const Phoneme& fonema : fonemas) {
        resultado.push_back(fonema.symbol);
    }

    return resultado;
}

TEST(RhymeIndexTest, RhymeKeyVogalConsoante) {
    EXPECT_EQ(RhymeIndex::rhymeKey({vogal("AO", 1), consoante("G")}),
        "AO G");
}

TEST(RhymeIndexTest, RhymeKeyUmFonema) {
    EXPECT_EQ(RhymeIndex::rhymeKey({vogal("AO", 1)}),
        "AO");
}

TEST(RhymeIndexTest, RhymeKeyVetorVazio) {
    EXPECT_EQ(RhymeIndex::rhymeKey({}),
        "");
}
