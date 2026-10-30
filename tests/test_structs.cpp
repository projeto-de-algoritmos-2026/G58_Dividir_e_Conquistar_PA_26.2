#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

#include "modelo/geometria/Edge.hpp"
#include "modelo/geometria/Point2D.hpp"

using modelo::geometria::Edge;
using modelo::geometria::Point2D;

TEST(StructsTest, EdgeTest) {
    constexpr Edge eCurta{0, 1, 1.0};
    constexpr Edge eLonga{2, 3, 5.0};
    constexpr Edge eMuitoLonga{4, 5, 10.0};

    EXPECT_TRUE(eCurta < eLonga);
    EXPECT_FALSE(eLonga < eCurta);
    EXPECT_FALSE(eCurta < eCurta);

    std::vector<Edge> edges{eMuitoLonga, eLonga, eCurta};

    std::sort(edges.begin(), edges.end());

    EXPECT_DOUBLE_EQ(edges[0].length, 1.0);
    EXPECT_DOUBLE_EQ(edges[1].length, 5.0);
    EXPECT_DOUBLE_EQ(edges[2].length, 10.0);

}

TEST(StructsTest, Point2DTest) {
    constexpr Point2D p1{0.0,5.0};
    constexpr Point2D p2{1.0,0.0};
    constexpr Point2D p3{1.0, 5.0};

    EXPECT_TRUE(p1 < p2);
    EXPECT_TRUE(p2 < p3);
    EXPECT_FALSE(p1 < p1);
    EXPECT_FALSE(p3 < p2);
    EXPECT_FALSE(p2 == p3);
    EXPECT_TRUE(p1 == p1);
    EXPECT_FALSE(p1 == p2);

}

