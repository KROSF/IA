#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "puzle.h"
#include "nodo.h"
#include "listaia.h"
#include "busquedaAlum.h"

void dispCamino(tNodo *nodo)
{
  if (nodo->padre == NULL)
  {
    printf("\n\nInicio:\n");
    dispEstado(nodo->estado);
  }
  else
  {
    dispCamino(nodo->padre);
    dispOperador(nodo->operador);
    dispEstado(nodo->estado);
    printf("\n");
  }
}

void dispSolucion(tNodo *nodo)
{
  dispCamino(nodo);
  printf("Profundidad=%d\n", nodo->profundidad);
  printf("Coste=%d\n", nodo->costeCamino);
}

/* Crea el nodo ra�z. */
tNodo *nodoInicial()
{
  tNodo *inicial = (tNodo *)malloc(sizeof(tNodo));
  inicial->estado = estadoInicial();
  inicial->padre = NULL;
  inicial->costeCamino = 0;
  inicial->profundidad = 0;
  inicial->valHeuristica = hManhattan(inicial->estado);
  return inicial;
}

/* Expande un nodo. */
Lista expandir(tNodo *nodo)
{
  Lista sucesores = CrearLista(MAXI);
  //printf("\nLista de Sucesores de Actual: \n");
  for (unsigned op = 1; op <= NUM_OPERADORES; ++op)
  {
    if (esValido(op, nodo->estado))
    {
      tNodo *nuevo = (tNodo *)malloc(sizeof(tNodo));
      tEstado *s = (tEstado *)malloc(sizeof(tEstado));
      s = aplicaOperador(op, nodo->estado);
      nuevo = (tNodo *)malloc(sizeof(tNodo));
      nuevo->estado = s;
      nuevo->padre = nodo;
      nuevo->operador = op;
      nuevo->valHeuristica = hManhattan(s);
      nuevo->costeCamino = nodo->costeCamino + coste(op, nodo->estado);
      nuevo->profundidad = nodo->profundidad + 1;
      if (!ListaLlena(sucesores))
      {
        InsertarUltimo((void *)nuevo, sucesores);
        //dispEstado(nuevo->estado);
      }
    }
  }
  //system("pause");
  return sucesores;
}

static int buscaRepe(tEstado *e, Lista C)
{
  int encontrado = 0;
  tNodo *Actual = (tNodo *)malloc(sizeof(tNodo));
  for (int i = 0; i < C->Nelem && !encontrado; ++i)
  {
    Actual = (void *)(C->elementos[i]);
    if (iguales(e, Actual->estado))
    {
      encontrado = 1;
    }
  }
  return encontrado;
}

int busqueda()
{
  int objetivo = 0;
  int visitados = 0;
  tNodo *Actual = (tNodo *)malloc(sizeof(tNodo));
  tNodo *Inicial = nodoInicial();
  //tEstado *Final=estadoObjetivo();

  Lista Abiertos = (Lista)CrearLista(MAXI);
  Lista Sucesores;

  InsertarUltimo((void *)Inicial, Abiertos);

  while (!ListaVacia(Abiertos) && !objetivo)
  {
    Actual = (void *)ExtraerPrimero(Abiertos);
    //printf("\n ACTUAL: \n");
    //dispEstado(Actual->estado);
    //system("pause");
    EliminarPrimero(Abiertos);
    objetivo = testObjetivo(Actual->estado);
    if (!objetivo)
    {
      Sucesores = expandir(Actual);
      Abiertos = Concatenar(Abiertos, Sucesores);
    }
    ++visitados;
  }
  dispSolucion(Actual);
  printf("Nodos visitados %d", visitados);
  return objetivo;
}

int busquedaAnchura()
{
  int objetivo = 0;
  int repetido = 0;
  tNodo *Actual = (tNodo *)malloc(sizeof(tNodo));
  tNodo *Inicial = nodoInicial();

  Lista Abiertos = (Lista)CrearLista(MAXI);
  Lista Cerrados = (Lista)CrearLista(MAXI);
  Lista Sucesores;

  InsertarUltimo((void *)Inicial, Abiertos);

  while (!ListaVacia(Abiertos) && !objetivo)
  {
    Actual = (void *)ExtraerPrimero(Abiertos);
    EliminarPrimero(Abiertos);
    repetido = buscaRepe(Actual->estado, Cerrados);
    objetivo = testObjetivo(Actual->estado);
    if (!objetivo && !repetido)
    {
      Sucesores = expandir(Actual);
      Abiertos = Concatenar(Abiertos, Sucesores);
    }
    if (!repetido)
    {
      InsertarUltimo((void *)Actual, Cerrados);
    }
  }
  dispSolucion(Actual);
  return objetivo;
}

int busquedaProfundidad()
{
  int objetivo = 0;
  int repetido = 0;
  tNodo *Actual = (tNodo *)malloc(sizeof(tNodo));
  tNodo *Inicial = nodoInicial();

  Lista Abiertos = (Lista)CrearLista(MAXI);
  Lista Cerrados = (Lista)CrearLista(MAXI);
  Lista Sucesores;

  InsertarUltimo((void *)Inicial, Abiertos);

  while (!ListaVacia(Abiertos) && !objetivo)
  {
    Actual = (void *)ExtraerPrimero(Abiertos);
    EliminarPrimero(Abiertos);
    repetido = buscaRepe(Actual->estado, Cerrados);
    objetivo = testObjetivo(Actual->estado);
    if (!objetivo && !repetido)
    {
      Sucesores = expandir(Actual);
      Abiertos = Concatenar(Sucesores, Abiertos);
    }
    if (!repetido)
    {
      InsertarUltimo((void *)Actual, Cerrados);
    }
  }
  dispSolucion(Actual);
  return objetivo;
}

int busquedaProfundidadLimitada(int limite)
{
  int objetivo = 0;
  int repetido = 0;
  tNodo *Actual = (tNodo *)malloc(sizeof(tNodo));
  tNodo *Inicial = nodoInicial();

  Lista Abiertos = (Lista)CrearLista(MAXI);
  Lista Cerrados = (Lista)CrearLista(MAXI);
  Lista Sucesores;

  InsertarUltimo((void *)Inicial, Abiertos);

  while (!ListaVacia(Abiertos) && !objetivo)
  {
    Actual = (void *)ExtraerPrimero(Abiertos);
    EliminarPrimero(Abiertos);
    repetido = buscaRepe(Actual->estado, Cerrados);
    objetivo = testObjetivo(Actual->estado);
    if (!objetivo && !repetido && Actual->profundidad < limite)
    {
      Sucesores = expandir(Actual);
      Abiertos = Concatenar(Sucesores, Abiertos);
    }
    if (!repetido)
    {
      InsertarUltimo((void *)Actual, Cerrados);
    }
  }
  if (objetivo)
    dispSolucion(Actual);
  else
    printf("No existe solucion en profundidad %d\n", limite);
  return objetivo;
}

int busquedaProfundidadIterativa()
{
  int limite = 1;
  int objetivo = 0;
  while (!objetivo)
  {
    objetivo = busquedaProfundidadLimitada(limite);
    ++limite;
  }
  return objetivo;
}

int busquedaA()
{
  int objetivo = 0;
  int repetido = 0;
  tNodo *Actual = (tNodo *)malloc(sizeof(tNodo));
  tNodo *Inicial = nodoInicial();

  Lista Abiertos = (Lista)CrearLista(MAXI);
  Lista Cerrados = (Lista)CrearLista(MAXI);
  Lista Sucesores;

  InsertarUltimo((void *)Inicial, Abiertos);

  while (!ListaVacia(Abiertos) && !objetivo)
  {
    Actual = (void *)ExtraerPrimero(Abiertos);
    EliminarPrimero(Abiertos);
    repetido = buscaRepe(Actual->estado, Cerrados);
    objetivo = testObjetivo(Actual->estado);
    if (!objetivo && !repetido)
    {
      Sucesores = expandir(Actual);
      printf("Sucesores: ");
      dispList(Sucesores);
      Abiertos = Ordenar(Abiertos, Sucesores);
      InsertarUltimo((void *)Actual, Cerrados);
      printf("Ordenados: ");
      dispList(Abiertos);
      getchar();
    }
  }
  dispSolucion(Actual);
  return objetivo;
}
