#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tictactoe.h"

static int min(int a, int b) { return (a < b) ? a : b; }

static int max(int a, int b) { return (a > b) ? a : b; }

tNodo *PSEUDOminimax(tNodo *t) {
  int mejorJugada = -1;
  int puntos = -2;
  int i, temp;
  tNodo *intento = malloc(sizeof(tNodo));
  printf("\n Mi turno: \n");
  for (i = 0; i < 9; ++i) {
    if (esValida(t, i)) {
      intento = aplicaJugada(t, 1, i);  // Intenta jugada
      temp = terminal(intento, -1);     // Calcula el valor minimax
      if (temp > puntos) {
        puntos = temp;
        mejorJugada = i;
      }
    }
  }  // for
  t = aplicaJugada(t, 1, mejorJugada);
  return t;
}

tNodo *minimax(tNodo *t, int jugador) {
  int max = -100000, max_actual = 0, mejorJugada = 0;
  tNodo *intento = malloc(sizeof(tNodo));
  for (int jugada = 0; jugada < 9; ++jugada) {
    if (esValida(t, jugada)) {
      intento = aplicaJugada(t, jugador, jugada);
      max_actual = valorMin(intento);
      if (max_actual > max) {
        max = max_actual;
        mejorJugada = jugada;
      }
    }
  }
  t = aplicaJugada(t, 1, mejorJugada);
  return t;
}

int valorMin(tNodo *t) {
  int valor_min = 0, jugador = -1;
  if (terminal(t, jugador)) {
    valor_min = terminal(t, jugador);
  } else {
    valor_min = 100000;
    for (int jugada = 0; jugada < 9; ++jugada) {
      if (esValida(t, jugada)) {
        valor_min = min(valor_min, valorMax(aplicaJugada(t, jugador, jugada)));
      }
    }
  }
  return valor_min;
}

int valorMax(tNodo *t) {
  int valor_max = 0, jugador = 1;
  if (terminal(t, jugador)) {
    valor_max = terminal(t, jugador);
  } else {
    valor_max = -100000;
    for (int jugada = 0; jugada < 9; ++jugada) {
      if (esValida(t, jugada)) {
        valor_max = max(valor_max, valorMin(aplicaJugada(t, jugador, jugada)));
      }
    }
  }
  return valor_max;
}

tNodo *jugadaAdversario(tNodo *t) {
  int jugada = 0;
  printf("\nJugada ([0..8])?: ");
  scanf("%d", &jugada);
  while (!esValida(t, jugada)) {
    printf("\n Intenta otra posicion del tablero \n");
    printf("\n");
    printf("\nJugada ([0..8])?: ");
    scanf("%d", &jugada);
  }
  t = aplicaJugada(t, -1, jugada);
  return t;
}
