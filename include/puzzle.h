#ifndef IA_PUZZLE_H
#define IA_PUZZLE_H

#define ARRIBA 1
#define ABAJO 2
#define IZQUIERDA 3
#define DERECHA 4
#define NUM_OPERADORES 4
#define DIMENSION 3

typedef struct _tEstado {
  int celdas[DIMENSION][DIMENSION];
  int filas[DIMENSION * DIMENSION];
  int cols[DIMENSION * DIMENSION];
} tEstado;

int coste(tEstado *e, unsigned);
int esObjetivo(tEstado *e);
int esValido(tEstado *e, unsigned);
int heuristica(tEstado *e);
int iguales(tEstado *e, tEstado *ee);
tEstado *aplicaOperador(tEstado *e, unsigned);
tEstado *crearEstado(int celdas[DIMENSION][DIMENSION]);
tEstado *estadoInicial();
tEstado *estadoObjetivo();
void dispEstado(tEstado *e);
void dispOperador(unsigned);
#endif