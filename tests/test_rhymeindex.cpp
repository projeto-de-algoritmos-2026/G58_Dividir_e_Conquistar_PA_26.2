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

TEST(RhymeIndexTest, RhymePartDog) {
    EXPECT_EQ(simbolos(RhymeIndex::rhymePart({consoante("D"), vogal("AO", 1), consoante("G")})),
        (std::vector<std::string>{"AO", "G"}));
}

TEST(RhymeIndexTest, RhymePartUltimaTonica) {
    EXPECT_EQ(simbolos(RhymeIndex::rhymePart({consoante("B"), vogal("AH", 0), consoante("N"), vogal("AE", 1), consoante("N"), vogal("AH", 0)})),
        (std::vector<std::string>{"AE", "N", "AH"}));
}

TEST(RhymeIndexTest, RhymePartTonicaSecundaria) {
    EXPECT_EQ(simbolos(RhymeIndex::rhymePart({consoante("N"), vogal("OW", 1), consoante("T"), consoante("B"), vogal("UH", 2), consoante("K")})),
        (std::vector<std::string>{"UH", "K"}));
}

TEST(RhymeIndexTest, RhymePartSemTonica) {
    EXPECT_EQ(simbolos(RhymeIndex::rhymePart({consoante("DH"), vogal("AH", 0)})),
        (std::vector<std::string>{"AH"}));
}

TEST(RhymeIndexTest, RhymePartDuasVogausAtonas) {
    EXPECT_EQ(simbolos(RhymeIndex::rhymePart({consoante("B"), vogal("AH", 0), consoante("N"), vogal("AH", 0)})),
        (std::vector<std::string>{"AH"}));
}

TEST(RhymeIndexTest, RhymePartSemVogal) {
    EXPECT_TRUE(RhymeIndex::rhymePart({consoante("HM"), consoante("M")}).empty());
}

TEST(RhymeIndexTest, ChaveDesconhecida) {
    RhymeIndex index;
    EXPECT_EQ(index.findFamily("AO G"), -1);
}

TEST(RhymeIndexTest, PrimeiraPalavra) {
    RhymeIndex index;
    index.add("dog", "AO G", {0.89, 0.375});
    int id = index.findFamily("AO G");
    ASSERT_NE(id, -1);
    EXPECT_EQ(index.family(id).key, "AO G");
    EXPECT_EQ(index.family(id).words, std::vector<std::string>{"dog"});
    EXPECT_EQ(index.points().size(), 1);
    EXPECT_EQ(index.family(id).vertex, 0);
    EXPECT_EQ(index.familiesAtVertex(0), std::vector{id});
}