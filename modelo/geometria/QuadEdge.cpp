#include "QuadEdge.hpp"

namespace modelo::geometria {
    QuadEdge* QuadEdge::makeEdge(std::deque<QuadEdge>& pool) {
        QuadEdge* e[4];

        for (int i = 0; i < 4; i++) {
            pool.emplace_back();
            e[i] = &pool.back();
        }

        for (int i = 0; i < 4; i++) {
            e[i]->r = e[(i + 1 )% 4];
        }

        e[0]->next = e[0];
        e[1]->next = e[3];
        e[2]->next = e[2];
        e[3]->next = e[1];

    return e[0];
    }

    void QuadEdge::splice(QuadEdge* a, QuadEdge* b) {
        QuadEdge* alpha = a->onext()->rot();
        QuadEdge* beta = b->onext()->rot();

        QuadEdge* t1 = b->onext();
        QuadEdge* t2 = a->onext();
        QuadEdge* t3 = beta->onext();
        QuadEdge* t4 = alpha->onext();

        a->next = t1;
        b->next = t2;
        alpha->next = t3;
        beta->next = t4;
    }

    QuadEdge* QuadEdge::connect(QuadEdge* a, QuadEdge* b, std::deque<QuadEdge>& pool) {
        QuadEdge* e = makeEdge(pool);
        e->org = a->dest();
        e->sym()->org = b->org;
        splice(e, a->lnext());
        splice(e->sym(), b);
        return e;
    }

    void QuadEdge::deleteEdge(QuadEdge* e) {
        splice(e, e->oprev());
        splice(e->sym(), e->sym()->oprev());
        e->org = -1;
        e->sym()->org = -1;
    }

}