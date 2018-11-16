#ifndef _tNodo_
#define _tNodo_
#include "puzle.h"
typedef struct NodoBusqueda
{
  tEstado *estado;
  struct NodoBusqueda *padre;
  unsigned operador;
  int costeCamino;
  int profundidad;
  int valHeuristica;
} tNodoBusqueda;
typedef tNodoBusqueda tNodo;
#endif
