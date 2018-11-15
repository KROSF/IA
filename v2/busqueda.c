#include <stdlib.h>
#include <stdio.h>
#include "busqueda.h"
#include "nodo.h"
#include "sortedarray.h"

int vorax(const void* e1, const void* e2) {
    tNodo* el1 = (tNodo*) e1;
    tNodo* el2 = (tNodo*) e2;
    return el1->valHeuristica - el2->valHeuristica;
}

int AEstrella(const void* e1, const void* e2) {
    tNodo* el1 = (tNodo*) e1;
    tNodo* el2 = (tNodo*) e2;
    return (el1->valHeuristica + el1->costeCamino) - (el2->valHeuristica + el2->costeCamino);
}

void dispH(void* e) {
    tNodo* ee = (tNodo*) e;
    printf("%d ",ee->costeCamino + ee->valHeuristica);
}

int busquedaInformada(FuncionEvaluacion f) {
    int objetivo = 0, repetido = 0;
    sortedarray*  abiertos = sortedarray_create((sortedarray_cmpfn)f);
    sortedarray_add(abiertos, (void*) nodoInicial());
    dynarray* cerrados = dynarray_create(0);
    tNodo* actual = (tNodo*) malloc(sizeof(tNodo));
    while (!objetivo && sortedarray_get_count(abiertos) != 0) {
        actual = (void*) sortedarray_get(abiertos, 0);
        sortedarray_remove_at(abiertos, 0);
        objetivo = esObjetivo(actual->estado);
        repetido = dynarray_elto_belongs(cerrados, (void*)actual, estadoNodoIguales);
        if (!objetivo && !repetido) {
            sortedarray_add_dynarray(abiertos, Expandir(actual));
            dynarray_add_tail(cerrados, actual);
        }
    }
    if (objetivo) {
        dispSolucion(actual);
    }
    sortedarray_delete(abiertos);
    dynarray_delete(cerrados);
    free(actual);
    return objetivo;
}
