#include <gtest/gtest.h>

#include "modelo/geometria/predicates.h"

TEST(PredicatesTest, Orient2DTest) {
    exactinit();

    double a[2] = {0.0, 0.0};
    double b[2] = {1.0, 0.0};
    double c[2] = {0.0, 1.0};
    double d[2] = {1.0, 1.0};
    double e[2] = {2.0, 2.0};

    EXPECT_GT(orient2d(a, b, c), 0.0);
    EXPECT_LT(orient2d(b, a, c), 0.0);
    EXPECT_EQ(orient2d(a, d, e), 0.0);

}

TEST(PredicatesTest, InCircle) {
    exactinit();

    double a[2] = {0.0, 0.0};
    double b[2] = {1.0, 0.0};
    double c[2] = {1.0, 1.0};

    double d[2] = {0.0, 1.0};
    EXPECT_EQ(incircle(a, b, c, d), 0.0);

    double e[2] = {0.5, 0.5};
    EXPECT_GT(incircle(a, b, c, e), 0.0);

    double f[2] = {2.0, 2.0};
    EXPECT_LT(incircle(a, b, c, f), 0.0);

}




