#include "puzle.h"

int esValido(unsigned op, tEstado* estado) {
    int valido = 0;
    switch (op) {
        case ARRIBA:
            valido = (estado->fila[0] > 0);
        break;
        case ABAJO:
            valido = (estado->fila[0] < N - 1);
        break;
        case IZQUIERDA: 
            valido = (estado->columna[0] > 0);
        break;
        case DERECHA:
            valido = (estado->columna[0] < N - 1);
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
    e->columna[ficha] = cold;
    e->fila[ficha] = fold;
}

tEstado* aplicaOperador(unsigned op, tEstado* estado) {
    tEstado* nuevo = (tEstado*) malloc(sizeof(tEstado));
    memcpy(nuevo, estado, sizeof(tEstado));
    switch (op) {
        case ARRIBA:    
            --nuevo->fila[0];
        break;
        case ABAJO:
            ++nuevo->fila[0];
        break;
        case IZQUIERDA:
            --nuevo->columna[0];
        break;
        case DERECHA:
            ++nuevo->columna[0];
        break;
    }

    intercambioEstado(
        nuevo,
        nuevo->fila[0],
        nuevo->columna[0],
        estado->fila[0],
        estado->columna[0]);
}

int iguales(tEstado* m, tEstado* n) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (m->celdas[i][j] != n->celdas[i][j])
                return 0;
    return 1;
}