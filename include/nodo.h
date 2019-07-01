#ifndef IA_NODO_H
#define IA_NODO_H

#include <glib.h>
#include "puzzle.h"

typedef struct _tNodo {
  tEstado *estado;
  struct _tNodo *padre;
  unsigned operador;
  int costeCamino;
  int profundidad;
  int valHeuristica;
} tNodo;

GQueue *Expandir(tNodo *);
GQueue *g_queue_merge_sorted(GQueue *a, GQueue *s, GCompareDataFunc cmp);
gint estadoNodoIguales(gconstpointer e1, gconstpointer e2);
tNodo *nodoInicial();
void dispCamino(tNodo *);
void dispSolucion(tNodo *);
#endif