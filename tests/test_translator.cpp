#include <gtest/gtest.h>

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