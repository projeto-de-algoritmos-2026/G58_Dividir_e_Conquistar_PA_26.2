#include <gtest/gtest.h>
#include <stdexcept>

#include "modelo/geometria/Point2D.hpp"
#include "modelo/adaptadores/AcousticTranslator.hpp"
#include "modelo/nucleo/Phoneme.hpp"
#include "modelo/nucleo/IPhoneticConverter.hpp"

using modelo::geometria::Point2D;
using modelo::adaptadores::AcousticTranslator;
using modelo::nucleo::Phoneme;
using modelo::nucleo::IPhoneticConverter;

// Monta uma vogal
static Phoneme vogal(const std::string& symbol, int stress) {
    return {symbol, true, stress};
}

// Monta uma consoante. Consoante não tem tônica, stress = -1.
static Phoneme consoante(const std::string& symbol) {
    return {symbol, false, -1};
}

TEST(AcousticTranslatorTest, UmaVogal) {
    AcousticTranslator tradutor(0.9);
    IPhoneticConverter& conversor = tradutor;
    Point2D p = conversor.toPoint({vogal("AO", 1)});
    EXPECT_DOUBLE_EQ(p.x, 0.90);
    EXPECT_DOUBLE_EQ(p.y, 0.40);
}

TEST(AcousticTranslatorTest, VogalEConsoante) {
    AcousticTranslator tradutor(0.9);
    IPhoneticConverter& conversor = tradutor;
    Point2D p = conversor.toPoint({vogal("AO", 1), consoante("G")});
    EXPECT_NEAR(p.x, 0.89, 1e-12);
    EXPECT_NEAR(p.y, 0.375, 1e-12);
}

TEST(AcousticTranslatorTest, MediaDoResto) {
    AcousticTranslator tradutor(0.9);
    IPhoneticConverter& conversor = tradutor;
    Point2D p = conversor.toPoint({vogal("AE", 1), consoante("N"), vogal("AH", 0)});
    EXPECT_NEAR(p.x, 0.135, 1e-12);
    EXPECT_NEAR(p.y, 0.145, 1e-12);
}

TEST(AcousticTranslatorTest, PesoDiferente) {
    AcousticTranslator tradutor(0.5);
    IPhoneticConverter& conversor = tradutor;
    Point2D p = conversor.toPoint({vogal("AO", 1), consoante("G")});
    EXPECT_NEAR(p.x, 0.85, 1e-12);
    EXPECT_NEAR(p.y, 0.275, 1e-12);
}

TEST(AcousticTranslatorTest, SimboloDesconhecidoNaVogal) {
    AcousticTranslator tradutor(0.5);
    IPhoneticConverter& conversor = tradutor;
    EXPECT_THROW(conversor.toPoint({vogal("XX", 1)}),
        std::invalid_argument);
}

TEST(AcousticTranslatorTest, SimboloDesconhecidoNoResto) {
    AcousticTranslator tradutor(0.5);
    IPhoneticConverter& conversor = tradutor;
    EXPECT_THROW(conversor.toPoint({vogal("AO", 1), consoante("QQ")}),
        std::invalid_argument);
}

TEST(AcousticTranslatorTest, TodosOsFonemasDoCmu) {
    AcousticTranslator tradutor(0.5);
    IPhoneticConverter& conversor = tradutor;
    std::vector<std::string> simbolosCmu {"AA", "AE", "AH", "AO", "AW", "AY", "EH", "ER", "EY", "IH", "IY", "OW", "OY", "UH", "UW",
    "B", "CH", "D", "DH", "F", "G", "HH", "JH", "K", "L", "M", "N", "NG", "P", "R", "S", "SH", "T", "TH", "V", "W", "Y", "Z", "ZH"};

    EXPECT_EQ(simbolosCmu.size(), 39u);

    for (const std::string& s : simbolosCmu) {
        EXPECT_NO_THROW(conversor.toPoint({vogal(s, 1)})) << "símbolo: " << s;
    }

}

TEST(AcousticTranslatorTest, RimaVazia) {
    AcousticTranslator tradutor(0.5);
    IPhoneticConverter& conversor = tradutor;
    EXPECT_THROW(conversor.toPoint({}),
        std::invalid_argument);
}