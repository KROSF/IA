#ifndef NODO_H
#define NODO_H
#include "puzzle.h"
#include <glib.h>
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
GQueue *Expandir(tNodo *);
GQueue *g_queue_merge_sorted(GQueue *a, GQueue *s, GCompareDataFunc cmp);
gint estadoNodoIguales(gconstpointer e1, gconstpointer e2);
tNodo *nodoInicial();
void dispCamino(tNodo *);
void dispSolucion(tNodo *);
#endif
