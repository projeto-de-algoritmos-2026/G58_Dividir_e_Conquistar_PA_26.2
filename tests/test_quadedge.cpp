#include <gtest/gtest.h>
#include <deque>

#include "modelo/geometria/QuadEdge.hpp"

using modelo::geometria::QuadEdge;

TEST(QuadEdgeTest, MakeEdgeTest) {

    std::deque<QuadEdge> pool;

    QuadEdge* e = QuadEdge::makeEdge(pool);

    EXPECT_EQ(e->sym()->sym(), e);
    EXPECT_EQ(e->rot()->rot()->rot()->rot(), e);
    EXPECT_EQ(e->invRot(), e->rot()->rot()->rot());
    EXPECT_EQ(e->onext(), e);
    EXPECT_EQ(e->sym()->onext(), e->sym());

    e->org = 0;
    e->sym()->org = 1;
    EXPECT_EQ(e->dest(), 1);

}

TEST(QuadEdgeTest, SpliceTest) {

    std::deque<QuadEdge> pool;

    QuadEdge* a = QuadEdge::makeEdge(pool);
    QuadEdge* b = QuadEdge::makeEdge(pool);

    QuadEdge::splice(a, b);

    EXPECT_EQ(a->onext(), b);
    EXPECT_EQ(b->onext(), a);

    QuadEdge::splice(a, b);

    EXPECT_EQ(a->onext(), a);
    EXPECT_EQ(b->onext(), b);

}


TEST(QuadEdgeTest, ConnectTest) {

    std::deque<QuadEdge> pool;

    QuadEdge* x = QuadEdge::makeEdge(pool);
    x->org = 0;
    x->sym()->org = 1;

    QuadEdge* y = QuadEdge::makeEdge(pool);
    y->org = 2;
    y->sym()->org = 3;

    QuadEdge* c = QuadEdge::connect(x, y, pool);

    EXPECT_EQ(c->org, 1);
    EXPECT_EQ(c->dest(), 2);
    EXPECT_EQ(x->lnext(), c);
    EXPECT_EQ(c->lnext(), y);

}

TEST(QuadEdgeTest, TriangleTest) {

    std::deque<QuadEdge> pool;

    QuadEdge* p = QuadEdge::makeEdge(pool);
    p->org = 0;
    p->sym()->org = 1;

    QuadEdge* q = QuadEdge::makeEdge(pool);
    q->org = 1;
    q->sym()->org = 2;

    QuadEdge::splice(p->sym(), q);

    QuadEdge* t = QuadEdge::connect(q, p, pool);

    EXPECT_EQ(t->org, 2);
    EXPECT_EQ(t->sym()->org, 0);

    EXPECT_EQ(p->lnext(), q);
    EXPECT_EQ(q->lnext(), t);
    EXPECT_EQ(t->lnext(), p);

}

TEST(QuadEdgeTest, DeleteTest) {

    std::deque<QuadEdge> pool;

    QuadEdge* x = QuadEdge::makeEdge(pool);
    x->org = 0;
    x->sym()->org = 1;

    QuadEdge* y = QuadEdge::makeEdge(pool);
    y->org = 2;
    y->sym()->org = 3;

    QuadEdge* c = QuadEdge::connect(x, y, pool);

    EXPECT_EQ(c->org, 1);
    EXPECT_EQ(c->dest(), 2);
    EXPECT_EQ(x->lnext(), c);
    EXPECT_EQ(c->lnext(), y);

    QuadEdge::deleteEdge(c);

    EXPECT_EQ(x->lnext(), x->sym());
    EXPECT_EQ(y->lnext(), y->sym());
    EXPECT_EQ(c->org, -1);

}

