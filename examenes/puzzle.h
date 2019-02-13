#ifndef PUZZLE_H
#define PUZZLE_H
#include <stdbool.h>
enum CONSTANTES
{
  ARRIBA_A = 1,
  ABAJO_A = 2,
  IZQUIERDA_A = 3,
  DERECHA_A = 4,
  ARRIBA_B = 5,
  ABAJO_B = 6,
  IZQUIERDA_B = 7,
  DERECHA_B = 8,
  ARRIBA_C = 9,
  ABAJO_C = 10,
  IZQUIERDA_C = 11,
  DERECHA_C = 12,
  OBSTACULO = -1,
  VACIO = 0,
  FICHA_A = 1,
  FICHA_B = 2,
  FICHA_C = 3,
  OPERADORES = 12,
  DIMENSION = 6,
};

struct tEstado
{
  int puzzle[DIMENSION][DIMENSION];
  int posiciones[2][DIMENSION + 1];
};

struct tEstado *crearEstado(int puzzle[DIMENSION][DIMENSION]);
struct tEstado *estadoObjetivo();
struct tEstado *estadoInicial();
struct tEstado *aplicaOperador(struct tEstado *e, int operador);

bool iguales(struct tEstado *e1, struct tEstado *e2);
bool esObjetivo(struct tEstado *e);
bool esValido(struct tEstado *e, int operador);

int coste(struct tEstado *e, int operador);
int heuristica(struct tEstado* e);

void dispEstado(struct tEstado *e);
void dispOperador(int operador);

#endif
