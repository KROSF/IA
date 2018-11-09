#ifndef NODO_H
#define NODO_H
#include "puzzle.h"
#include "dynarray.h"
typedef struct NodoBusqueda{
    tEstado *estado;
    struct NodoBusqueda *padre;
    unsigned operador;
    int costeCamino;
    int profundidad;
    int valHeuristica;
} tNodoBusqueda;
typedef tNodoBusqueda tNodo;
dynarray* Expandir(tNodo*);
tNodo* nodoInicial();
void dispCamino(tNodo*);
void dispSolucion(tNodo*);
unsigned int estadoNodoIguales(const void*, const void *);
#endif
