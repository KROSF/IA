#ifndef NODO_H
#define NODO_H
#include <glib.h>
#include "puzzle.h"
struct tNodo
{
  struct tEstado *estado;
  struct tNodo *padre;
  unsigned operador;
  int costeCamino;
  int profundidad;
  int valHeuristica;
};

GQueue *Expandir(struct tNodo *);
GQueue *g_queue_merge_sorted(GQueue *a, GQueue *s, GCompareDataFunc cmp);
gint estadoNodoIguales(gconstpointer e1, gconstpointer e2);
struct tNodo *nodoInicial();
void dispCamino(struct tNodo *);
void dispSolucion(struct tNodo *);
#endif
