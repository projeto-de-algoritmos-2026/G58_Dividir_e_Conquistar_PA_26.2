#ifndef MODELO_GEOMETRIA_PREDICATES_H
#define MODELO_GEOMETRIA_PREDICATES_H

extern "C" {
    void exactinit(void);
    double orient2d(double* pa, double* pb, double* pc);
    double incircle(double* pa, double* pb, double* pc, double* pd);
}

#endif