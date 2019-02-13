#include <stdio.h>
#include "nodo.h"

static struct tNodo *sucesoresNodo(struct tNodo *n, unsigned op)
{
  struct tNodo *nuevo = (struct tNodo *)malloc(sizeof(struct tNodo));
  nuevo->estado = aplicaOperador(n->estado, op);
  nuevo->padre = n;
  nuevo->operador = op;
  nuevo->costeCamino = n->costeCamino + coste(n->estado, op);
  nuevo->profundidad = n->profundidad + 1;
  nuevo->valHeuristica = heuristica(nuevo->estado);
  return nuevo;
}

GQueue *Expandir(struct tNodo *n)
{
  GQueue *sucesores = g_queue_new();
  for (unsigned op = 1; op <= OPERADORES; ++op)
  {
    if (esValido(n->estado, op) == 1)
    {
      g_queue_push_tail(sucesores, (void *)sucesoresNodo(n, op));
    }
  }
  return sucesores;
}

struct tNodo *nodoInicial()
{
  struct tNodo *inicial = (struct tNodo *)malloc(sizeof(struct tNodo));
  inicial->estado = estadoInicial();
  inicial->padre = NULL;
  inicial->operador = 0;
  inicial->costeCamino = 0;
  inicial->profundidad = 0;
  inicial->valHeuristica = heuristica(inicial->estado);
  return inicial;
}

void dispCamino(struct tNodo *n)
{
  if (n->padre == NULL)
  {
    printf("INICIO\n\n");
    dispEstado(n->estado);
    printf("\n");
  }
  else
  {
    dispCamino(n->padre);
    dispOperador(n->operador);
    dispEstado(n->estado);
    printf("Heuristica: %d\n", n->valHeuristica);
    printf("\n");
  }
}

void dispSolucion(struct tNodo *n)
{
  dispCamino(n);
  printf("Profundidad = %d\n", n->profundidad);
  printf("Coste = %d\n", n->costeCamino);
}

gint estadoNodoIguales(gconstpointer e1, gconstpointer e2)
{
  struct tNodo *el1 = (struct tNodo *)e1;
  struct tNodo *el2 = (struct tNodo *)e2;
  return (gint)!iguales(el1->estado, el2->estado);
}

GQueue *g_queue_merge_sorted(GQueue *a, GQueue *s, GCompareDataFunc cmp)
{
  while (!g_queue_is_empty(s))
  {
    g_queue_insert_sorted(a, g_queue_pop_head(s), cmp, NULL);
  }
  return a;
}
