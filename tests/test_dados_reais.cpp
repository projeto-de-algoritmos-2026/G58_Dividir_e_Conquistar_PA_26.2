#include <gtest/gtest.h>

#include <fstream>
#include <queue>
#include <string>
#include <vector>

#include "modelo/adaptadores/AcousticTranslator.hpp"
#include "modelo/adaptadores/CmuDictionary.hpp"
#include "modelo/geometria/DelaunayGraph.hpp"
#include "modelo/geometria/DivideConquerDelaunay.hpp"
#include "modelo/nucleo/DictionaryEntry.hpp"
#include "modelo/nucleo/RhymeIndex.hpp"

using modelo::adaptadores::AcousticTranslator;
using modelo::adaptadores::CmuDictionary;
using modelo::geometria::DelaunayGraph;
using modelo::geometria::DivideConquerDelaunay;
using modelo::nucleo::DictionaryEntry;
using modelo::nucleo::Phoneme;
using modelo::nucleo::RhymeIndex;

static const std::string CMUDICT = std::string(DATA_DIR) + "/cmudict.dict";

TEST(DadosReais, TriangulacaoDoDicionarioInteiro) {
    if (!std::ifstream(CMUDICT)) {
        GTEST_SKIP() << "dicionário não encontrado em " << CMUDICT;
    }

    CmuDictionary dicionario(CMUDICT);
    AcousticTranslator tradutor(0.9);
    RhymeIndex index;
    for (const DictionaryEntry& e : dicionario.entries()) {
        std::vector<Phoneme> parte = RhymeIndex::rhymePart(e.phonemes);
        if (!parte.empty()) {
            index.add(e.word, RhymeIndex::rhymeKey(parte), tradutor.toPoint(parte));
        }
    }

    int n = static_cast<int>(index.points().size());
    ASSERT_GT(n, 10000);

    DivideConquerDelaunay dc;
    DelaunayGraph grafo = dc.triangulate(index.points());

    EXPECT_LE(static_cast<long>(grafo.edges().size()), 3L * n - 6);

    std::vector<bool> visitado(n, false);
    std::queue<int> fila;
    fila.push(0);
    visitado[0] = true;
    int alcancados = 1;
    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();
        for (int w : grafo.neighbors(u)) {
            if (!visitado[w]) {
                visitado[w] = true;
                alcancados++;
                fila.push(w);
            }
        }
    }
    EXPECT_EQ(alcancados, n);
}
