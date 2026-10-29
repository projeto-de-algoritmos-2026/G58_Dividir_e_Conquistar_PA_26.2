#include "QuadEdge.hpp"

namespace modelo::geometria {
    QuadEdge* QuadEdge::makeEdge(std::deque<QuadEdge>& arena) {
        QuadEdge* versions[4];

        for (int i = 0; i < 4; i++) {
            arena.emplace_back();
            versions[i] = &arena.back();
        }

        for (int i = 0; i < 4; i++) {
            versions[i]->rotated = versions[(i + 1 )% 4];
        }

        versions[0]->originNext = versions[0];
        versions[1]->originNext = versions[3];
        versions[2]->originNext = versions[2];
        versions[3]->originNext = versions[1];

    return versions[0];
    }

    void QuadEdge::splice(QuadEdge* first, QuadEdge* second) {
        QuadEdge* firstDual = first->onext()->rot();
        QuadEdge* secondDual = second->onext()->rot();

        QuadEdge* firstNext = second->onext();
        QuadEdge* secondNext = first->onext();
        QuadEdge* firstDualNext = secondDual->onext();
        QuadEdge* secondDualNext = firstDual->onext();

        first->originNext = firstNext;
        second->originNext = secondNext;
        firstDual->originNext = firstDualNext;
        secondDual->originNext = secondDualNext;
    }

    QuadEdge* QuadEdge::connect(QuadEdge* previous, QuadEdge* next, std::deque<QuadEdge>& arena) {
        QuadEdge* edge = makeEdge(arena);
        edge->origin = previous->dest();
        edge->sym()->origin = next->origin;
        splice(edge, previous->lnext());
        splice(edge->sym(), next);
        return edge;
    }

    void QuadEdge::deleteEdge(QuadEdge* edge) {
        splice(edge, edge->oprev());
        splice(edge->sym(), edge->sym()->oprev());
        edge->origin = -1;
        edge->sym()->origin = -1;
    }

}