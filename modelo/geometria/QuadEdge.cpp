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
        QuadEdge* firstDual = first->oNext()->rot();
        QuadEdge* secondDual = second->oNext()->rot();

        QuadEdge* firstNext = second->oNext();
        QuadEdge* secondNext = first->oNext();
        QuadEdge* firstDualNext = secondDual->oNext();
        QuadEdge* secondDualNext = firstDual->oNext();

        first->originNext = firstNext;
        second->originNext = secondNext;
        firstDual->originNext = firstDualNext;
        secondDual->originNext = secondDualNext;
    }

    QuadEdge* QuadEdge::connect(QuadEdge* previous, QuadEdge* next, std::deque<QuadEdge>& arena) {
        QuadEdge* edge = makeEdge(arena);
        edge->origin = previous->dest();
        edge->sym()->origin = next->origin;
        splice(edge, previous->lNext());
        splice(edge->sym(), next);
        return edge;
    }

    void QuadEdge::deleteEdge(QuadEdge* edge) {
        splice(edge, edge->oPrev());
        splice(edge->sym(), edge->sym()->oPrev());
        edge->origin = -1;
        edge->sym()->origin = -1;
    }

}