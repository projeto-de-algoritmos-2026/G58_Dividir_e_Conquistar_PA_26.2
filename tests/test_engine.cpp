#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

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

TEST_F(RhymeEngineTest, ClusterDeUmaFamilia) {
    engine.build(5);
    EXPECT_EQ(engine.clusterOf("dog").keys,
        std::vector<std::string>({ "AO G"}));
    EXPECT_EQ(engine.clusterOf("dog").words,
        std::vector<std::string>({"dog", "log"}));
}

TEST_F(RhymeEngineTest, ClusterComKDois) {
    engine.build(2);

    auto dog = engine.clusterOf("dog");
    auto dartagnan = engine.clusterOf("d'artagnan");

    EXPECT_EQ(dog.keys.size(), 4u);
    EXPECT_NE(std::find(dog.keys.begin(), dog.keys.end(), "AO G"), dog.keys.end());

    EXPECT_EQ(dartagnan.keys, (std::vector<std::string>{"AE NG Y AH N"}));
    EXPECT_NE(dog.id, dartagnan.id);
}
