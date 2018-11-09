#include <stdlib.h>
#include <stdio.h>
#include "nodo.h"
#include "listaia.h"
Lista CrearLista (int TamMax) {
    Lista C;
    C = (Lista) malloc(sizeof(tLista));
    if (C == NULL) {
        ERROR("CrearLista: No hay memoria");
    } else {
        C->elementos = (tElemento *)malloc(TamMax*sizeof(tElemento));
        if (C->elementos == NULL) {
            ERROR("CrearLista: No hay memoria para los elementos");
        } else {
            C->Lmax = TamMax;
            C->Nelem = 0;
            C->inicio = 0;
            C->fin =0;
        }
    }
    return C;
}


int ListaVacia (Lista C) {
    return (C->Nelem == 0);
}


int ListaLlena (Lista C) {
    return (C->Nelem == C->Lmax);
}


//Pre: Lista C no est� vac�a
//Post:Devuelve el primer elemento de la lista C
tElemento* ExtraerPrimero(Lista C) {
    return (tElemento *) (C->elementos[C->inicio]);
}


//Pre: Lista C no est� vac�a, i: es un �ndice entre 0 y TamMax
//Post:Devuelve el elemento i-�simo de la lista C (no lo elimina de la lista)
tElemento *ExtraerElem(Lista C,int i) {
    return (tElemento *) (C->elementos[i]);
}

// Elimina el primer elemento de la lista
void EliminarPrimero(Lista C) {
    if (!ListaVacia(C)) {
        C->inicio = (C->inicio+1) % C->Lmax;
        C->Nelem = C->Nelem-1;
    }
}


//Pre: Lista C no est� llena
//Post:Devuelve el elemento primero de la lista
void InsertarUltimo(tElemento* e, Lista C) {
    (C->elementos[C->fin]) = (tElemento ) e;
    C->Nelem = C->Nelem + 1;
    if (C->fin == C->Lmax - 1)
        C->fin = 0;
    else
        C->fin = (C->fin + 1);
}

//Pre: Lista C no est� llena
//Post:Devuelve el elemento primero de la lista
void InsertarPrimero(tElemento* e, Lista C) {
    if (C->inicio>0)
        C->inicio = (C->inicio - 1); //inserta antes que el primero
    else
        C->inicio=C->Lmax - 1;
    (C->elementos[C->inicio]) = (tElemento ) e;
    C->Nelem = C->Nelem + 1;
}

//Pre: Lista L1 no est� vac�a
//Post: Devuelve L1+L2
Lista Concatenar(Lista L1, Lista L2) {
    tElemento* e = (tElemento*) malloc(sizeof(tElemento));
    while (!ListaVacia(L2) && (!ListaLlena(L1))) {
        e = (tElemento*) ExtraerPrimero(L2);
        InsertarUltimo(e,L1);
        EliminarPrimero(L2);
    }
    return L1;
}

void DestruirLista(Lista C) {
   free(C->elementos);
   free(C);
}

int cmp(const void* e1, const void* e2) {
    tNodo* el1 = (void*) e1;
    tNodo* el2 = (void*) e2;
    return (el2->valHeuristica + el2->costeCamino) - (el1->valHeuristica+el1->costeCamino);
}

Lista Ordenar(Lista L1, Lista L2) {
    L1 = Concatenar(L1,L2);
    qsort(L1->elementos + L1->inicio-L1->fin, L1->Nelem, sizeof(tElemento), cmp);
    return L1;
}

void dispList(Lista L1) {
    tNodo* Actual = (tNodo*) malloc(sizeof(tNodo));
    for (int i = L1->inicio; i < L1->Nelem; ++i) {
        Actual = (void *) L1->elementos[i];
        printf("%d ",Actual->valHeuristica + Actual->costeCamino);
    }
    printf("\n");
}
