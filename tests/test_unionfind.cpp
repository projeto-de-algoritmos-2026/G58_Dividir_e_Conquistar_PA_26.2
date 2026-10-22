#include <gtest/gtest.h>
#include "modelo/geometria/UnionFind.hpp"

using modelo::geometria::UnionFind;

// Cada TEST é um caso de teste, como um método @Test no JUnit.
// TEST(NomeDoGrupo, NomeDoCaso): o grupo faz o papel da classe de teste do Java.
TEST(UnionFindTest, NovoComecaComCadaElementoSozinho)
{
    // Preparar: cria o objeto. Sem "new": ele vive na pilha e some no fim do teste.
    UnionFind uf(5);

    // Verificar: cada elemento é o representante do próprio grupo...
    for (int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(uf.find(i), i) << "o elemento " << i << " deveria ser o próprio representante";
    }

    // ...e começam existindo 5 grupos.
    EXPECT_EQ(uf.count(), 5);
}

TEST(UnionFindTest, TestaFuncaoUnite) {

    UnionFind uf(5);

    EXPECT_EQ(uf.unite(0, 1), true);
    EXPECT_EQ(uf.find(0), uf.find(1));

    EXPECT_EQ(uf.unite(1, 0), false);
    EXPECT_TRUE(uf.unite(1,2));

    EXPECT_EQ(uf.find(0), uf.find(2));
    EXPECT_NE(uf.find(3), uf.find(0));

}

TEST(UnionFindTest, TestaContagemDeNos) {

    UnionFind uf(5);

    EXPECT_EQ(uf.count(), 5);

    uf.unite(0, 1);
    EXPECT_EQ(uf.count(), 4);

    uf.unite(0,1);
    EXPECT_EQ(uf.count(), 4);

    uf.unite(2, 3);
    EXPECT_EQ(uf.count(), 3);

    uf.unite(0, 3);
    EXPECT_EQ(uf.count(), 2);

    uf.unite(4, 0);
    EXPECT_EQ(uf.count(), 1);

}
