#include <gtest/gtest.h>

#include "modelo/nucleo/RhymeEngine.hpp"
#include "modelo/adaptadores/CmuDictionary.hpp"
#include "modelo/adaptadores/AcousticTranslator.hpp"
#include "modelo/geometria/DivideConquerDelaunay.hpp"
#include "modelo/geometria/KruskalClusterer.hpp"

using modelo::nucleo::RhymeEngine;
using modelo::adaptadores::AcousticTranslator;
using modelo::adaptadores::CmuDictionary;
using modelo::geometria::DivideConquerDelaunay;
using modelo::geometria::KruskalClusterer;

static const std::string MINI = std::string(FIXTURES_DIR) + "/mini.dict";

class RhymeEngineTest : public ::testing::Test {
protected:
    CmuDictionary dicionario{MINI};
    AcousticTranslator tradutor{0.9};
    DivideConquerDelaunay triangulador;
    KruskalClusterer clsuterizador;
    RhymeEngine engine{dicionario, tradutor, triangulador, clsuterizador};
};

TEST_F(RhymeEngineTest, ClusterPalavraDesconhecida) {
    engine.build(5);
    auto c = engine.clusterOf("xyzzy");
    EXPECT_EQ(c.id, -1);
    EXPECT_TRUE(c.keys.empty());
    EXPECT_TRUE(c.words.empty());
}