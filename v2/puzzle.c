#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "puzzle.h"

static const char* operadores[] = {"ARRIBA","ABAJO","IZQUIERDA","DERECHA"};
typedef int (*Heuristicas) (const tEstado*);

tEstado* crearEstado(int tabla[DIMENSION][DIMENSION]) {
    tEstado* estado = (tEstado*) malloc(sizeof(tEstado));
    int ficha = 0;
    for (int i = 0 ; i < DIMENSION; ++i) {
        for (int j = 0; j < DIMENSION; ++j) {
            ficha = tabla[i][j];
            estado->celdas[i][j] = ficha;
            estado->filas[ficha] = i;
            estado->cols[ficha] = j;
        }
    }
    return estado;
}

static int puzle_inicial[DIMENSION][DIMENSION] = {
    {1,3,7},
    {2,8,5},
    {4,6,0}
};

static int puzle_final[DIMENSION][DIMENSION] = {
    {0,1,3},
    {4,2,7},
    {6,5,8}
};

tEstado* estadoInicial() {
   return crearEstado(puzle_inicial);
}


tEstado* estadoObjetivo() {
   return crearEstado(puzle_final);
}

int coste(tEstado* e, unsigned op) {
   return 1;
}

int manhattan(const tEstado* e) {
    tEstado* obj = estadoObjetivo();
    int sum = 0;
    for (int i = 0; i < DIMENSION * DIMENSION; ++i) {
        sum += (abs(e->filas[i] - obj->filas[i]) + abs(e->cols[i] - obj->cols[i]));
    }
    return sum;
}

int piezasmalcolocadas(const tEstado* e) {
    tEstado* obj = estadoObjetivo();
    int cont = 0;
    for (int i = 0; i < DIMENSION; ++i)
        for (int j = 0; j < DIMENSION; ++j)
            if (e->celdas[i][j] != obj->celdas[i][j])
                ++cont;
    return cont;
}

int Heuristica(const tEstado* e, Heuristicas h) {
    return h(e);
}

int heuristica(tEstado* e) {
    return Heuristica(e, piezasmalcolocadas);
}

void dispEstado(tEstado* estado) {
    for (int i = 0; i < DIMENSION; ++i) {
        printf("[");
        for (int j = 0; j < DIMENSION; ++j)
            printf("%d", estado->celdas[i][j]);
        printf("]\n");
    }
}

void dispOperador(unsigned op) {
    printf("%s\n\n", operadores[op-1]);
}

int iguales(tEstado* m, tEstado* n) {
    for (int i = 0; i < DIMENSION; ++i) {
        for (int j = 0; j < DIMENSION; ++j) {
            if (m->celdas[i][j] != n->celdas[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int esObjetivo(tEstado* estado) {
    return iguales(estado, estadoObjetivo());
}

int esValido(tEstado* estado, unsigned op) {
    int valido = 0;
    switch (op) {
        case ARRIBA:
            valido = (estado->filas[0] > 0);
        break;
        case ABAJO:
            valido = (estado->filas[0] < DIMENSION - 1);
        break;
        case IZQUIERDA: 
            valido = (estado->cols[0] > 0);
        break;
        case DERECHA:
            valido = (estado->cols[0] < DIMENSION - 1);
        break;
    }
    return valido;
}

static void intercambioEstado(tEstado* e, int fnew, int cnew,int fold, int cold) {
    int ficha = e->celdas[fnew][cnew];
    // intercambio
    e->celdas[fold][cold] = ficha;
    e->celdas[fnew][cnew] = 0;
    // intercambio indices vector filas y columnas.
    e->cols[ficha] = cold;
    e->filas[ficha] = fold;
}

tEstado* aplicaOperador(tEstado* estado, unsigned op) {
    tEstado* nuevo = (tEstado*) malloc(sizeof(tEstado));
    memcpy(nuevo, estado, sizeof(tEstado));
    switch (op) {
        case ARRIBA:    
            --nuevo->filas[0];
        break;
        case ABAJO:
            ++nuevo->filas[0];
        break;
        case IZQUIERDA:
            --nuevo->cols[0];
        break;
        case DERECHA:
            ++nuevo->cols[0];
        break;
    }
    intercambioEstado(
        nuevo,
        nuevo->filas[0],
        nuevo->cols[0],
        estado->filas[0],
        estado->cols[0]);
    return nuevo;
}
