#ifndef BUSQUEDA_H
#define BUSQUEDA_H
typedef struct tEstado{};
typedef struct tNodo {
    tEstado* estado;
    tNodo* padre;
    int accion;
    int coste;
    int profundidad;
};
#endif
