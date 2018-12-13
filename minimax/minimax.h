#ifndef MINIMAX_H
#define MINIMAX_H
#include "tictactoe.h"
tNodo *jugadaAdversario(tNodo *t);
tNodo *PSEUDOminimax(tNodo *Nodo);
tNodo *minimax(tNodo *t,int);
int valorMin(tNodo *t);
int valorMax(tNodo *t);
#endif
