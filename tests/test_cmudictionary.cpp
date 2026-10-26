#include <gtest/gtest.h>
#include <stdexcept>
#include <algorithm>

#include "modelo/adaptadores/CmuDictionary.hpp"
#include "modelo/nucleo/IDictionaryLookUp.hpp"

using modelo::nucleo::Phoneme;
using modelo::adaptadores::CmuDictionary;
using modelo::nucleo::IDictionaryLookUp;
using modelo::nucleo::DictionaryEntry;

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

TEST(CmuDictionaryTest, TonicaEVogal) {
    CmuDictionary dicionario(MINI);
    IDictionaryLookUp& dic = dicionario;

    auto f = dic.lookUp("dog");
    ASSERT_EQ(f.size(), 3u);

    EXPECT_EQ(f[1].symbol, "AO");
    EXPECT_EQ(f[1].isVowel, true);
    EXPECT_EQ(f[1].stress, 1);

    EXPECT_EQ(f[0].isVowel, false);
    EXPECT_EQ(f[0].stress, -1);
}

TEST(CmuDictionaryTest, PalavraDesconhecida) {
    CmuDictionary dicionario(MINI);
    IDictionaryLookUp& dic = dicionario;
    EXPECT_TRUE(dic.lookUp("xyzzy").empty());
}

TEST(CmuDictionaryTest, IgnoraComentarios) {
    CmuDictionary dicionario(MINI);
    IDictionaryLookUp& dic = dicionario;
    EXPECT_EQ(dic.entries().size(), 7u);
}

TEST(CmuDictionaryTest, ComentarioNoFimDaLinha) {
    CmuDictionary dicionario(MINI);
    IDictionaryLookUp& dic = dicionario;
    EXPECT_EQ(simbolos(dic.lookUp("d'artagnan")), std::vector<std::string>({"D", "AH", "R", "T", "AE", "NG", "Y", "AH", "N"}));
}

TEST(CmuDictionaryTest, Variantes) {
    CmuDictionary dicionario(MINI);
    IDictionaryLookUp& dic = dicionario;
    EXPECT_EQ(simbolos(dic.lookUp("log")), std::vector<std::string>({"L", "AO", "G"}));
    EXPECT_EQ(simbolos(dic.lookUp("log(2)")), std::vector<std::string>({}));

    auto quantidade = std::count_if(dic.entries().begin(), dic.entries().end(),
    [](const DictionaryEntry& entrada) { return entrada.word == "log"; });

    EXPECT_EQ(quantidade, 2);
}

TEST(CmuDictionaryTest, MaiusculasEMinusculas) {
    CmuDictionary dicionario(MINI);
    IDictionaryLookUp& dic = dicionario;
    EXPECT_FALSE(dic.lookUp("hello").empty());
    EXPECT_FALSE(dic.lookUp("heLLo").empty());
    EXPECT_EQ(dic.lookUp("DOG").size(), 3u);

    EXPECT_TRUE(std::any_of(dic.entries().begin(), dic.entries().end(),
    [](const DictionaryEntry& entrada) { return entrada.word == "hello"; }));

    EXPECT_FALSE(std::any_of(dic.entries().begin(), dic.entries().end(),
[](const DictionaryEntry& entrada) { return entrada.word == "HELLO"; }));

}