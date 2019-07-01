#include "tictactoe.h"

tNodo* estadoInicial() { return crearNodo(tablero_inicial); }

tNodo* crearNodo(int celdas[N]) {
  tNodo* n = (tNodo*)malloc(sizeof(tNodo));
  for (int i = 0, c; i < N; ++i) {
    c = celdas[i];
    n->celdas[i] = c;
    if (c == 0) {
      ++n->vacias;
    }
  }
  return n;
}

tNodo* aplicaJugada(tNodo* act, int jugador, int jugada) {
  tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
  memcpy(nuevo, act, sizeof(tNodo));
  nuevo->celdas[jugada] = jugador;
  --nuevo->vacias;
  return nuevo;
}

int esValida(tNodo* act, int jugada) {
  return (jugada >= 0 && jugada < 9 && act->celdas[jugada] == 0);
}

int opuesto(int jugador) { return jugador * -1; }

int lleno(tNodo* tablero) { return tablero->vacias != 0; }

int terminal(tNodo* nodo, int jugador) {
  static int op[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6},
                         {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
  int res = 0;
  for (int i = 0; res == 0 && i < 8; ++i) {
    if (nodo->celdas[op[i][0]] != 0 &&
        nodo->celdas[op[i][0]] == nodo->celdas[op[i][1]] &&
        nodo->celdas[op[i][0]] == nodo->celdas[op[i][2]]) {
      res = nodo->celdas[op[i][2]];
    }
  }
  return res * 100;
}

char marca(int i) {
  switch (i) {
    case 1:
      return 'X';
    case 0:
      return ' ';
    case -1:
      return 'O';
    default:
      return ' ';
  }
}

void dispNodo(tNodo* b) {
  printf(
      "---+---+---\n"
      " %c | %c | %c\n"
      " %c | %c | %c\n"
      " %c | %c | %c\n"
      "---+---+---\n\n",
      marca(b->celdas[0]), marca(b->celdas[1]), marca(b->celdas[2]),
      marca(b->celdas[3]), marca(b->celdas[4]), marca(b->celdas[5]),
      marca(b->celdas[6]), marca(b->celdas[7]), marca(b->celdas[8]));
}