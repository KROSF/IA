#ifndef IA_PUZZLE_H
#define IA_PUZZLE_H

#define ARRIBA 1
#define ABAJO 2
#define IZQUIERDA 3
#define DERECHA 4
#define NUM_OPERADORES 4
#define DIMENSION 3

typedef struct {
  int celdas[DIMENSION][DIMENSION];
  int filas[DIMENSION * DIMENSION];
  int cols[DIMENSION * DIMENSION];
} tEstado;

int coste(tEstado *, unsigned);
int esObjetivo(tEstado *);
int esValido(tEstado *, unsigned);
int heuristica(tEstado *);
int iguales(tEstado *, tEstado *);
tEstado *aplicaOperador(tEstado *, unsigned);
tEstado *crearEstado(int _[DIMENSION][DIMENSION]);
tEstado *estadoInicial();
tEstado *estadoObjetivo();
void dispEstado(tEstado *);
void dispOperador(unsigned);
#endif