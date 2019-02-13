#include <stdio.h>
#include "busqueda.h"
#include "nodo.h"

gint vorax(gconstpointer e1, gconstpointer e2, gpointer nil)
{
  struct tNodo *el1 = (struct tNodo *)e1;
  struct tNodo *el2 = (struct tNodo *)e2;
  return el1->valHeuristica - el2->valHeuristica;
}

gint AEstrella(gconstpointer e1, gconstpointer e2, gpointer nil)
{
  struct tNodo *el1 = (struct tNodo *)e1;
  struct tNodo *el2 = (struct tNodo *)e2;
  return (el1->valHeuristica + el1->costeCamino) -
         (el2->valHeuristica + el2->costeCamino);
}

void dispH(gpointer e, gpointer n)
{
  struct tNodo *ee = (struct tNodo *)e;
  printf("%d ", ee->costeCamino + ee->valHeuristica);
}

int busquedaInformada(GCompareDataFunc fcmp)
{
  int objetivo = 0;
  GList *repetido = NULL;
  GQueue *abiertos = g_queue_new();
  GQueue *cerrados = g_queue_new();
  GQueue *sucesores = NULL;
  struct tNodo *actual = (struct tNodo *)malloc(sizeof(struct tNodo));
  g_queue_push_head(abiertos, (gpointer)nodoInicial());
  while (!objetivo && !g_queue_is_empty(abiertos))
  {
    actual = (struct tNodo *)g_queue_pop_head(abiertos);
    objetivo = esObjetivo(actual->estado);
    repetido =
        g_queue_find_custom(cerrados, (gconstpointer)actual, estadoNodoIguales);
    if (!objetivo && repetido == NULL)
    {
      sucesores = Expandir(actual);
      g_queue_merge_sorted(abiertos, sucesores, fcmp);
      g_queue_push_head(cerrados, (gpointer)actual);
    }
  }
  if (objetivo)
  {
    dispSolucion(actual);
  }
  g_queue_free(abiertos);
  g_queue_free(cerrados);
  return objetivo;
}
