#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "puzzle.h"

static int puzzleInicial[DIMENSION][DIMENSION] = {
    {-1, 0, 0, 3, 0, 0},
    {-1, 0, 0, 3, 0, 0},
    {0, 1, 0, 3, 0, 0},
    {1, 1, 1, -1, 2, 0},
    {0, 1, 0, 2, 2, 2},
    {0, 0, 0, 0, 0, 0}};

static int puzzleFinal[DIMENSION][DIMENSION] = {
    {-1, 0, 0, 0, 0, 0},
    {-1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 1, 0, -1, 0, 3},
    {1, 1, 1, 2, 0, 3},
    {0, 1, 2, 2, 2, 3}};

static int *esCentro(int ficha, int i, int j, int puzzle[DIMENSION][DIMENSION])
{
  int *posiciones = malloc(sizeof(int) * 2);
  posiciones[0] = -1;
  posiciones[1] = -1;
  switch (ficha)
  {
  case FICHA_A:
    if (i > 0 && i < DIMENSION - 1 && j > 0 && j < DIMENSION - 1)
    {
      if (puzzle[i][j - 1] == FICHA_A && puzzle[i][j + 1] == FICHA_A && puzzle[i - 1][j] == FICHA_A && puzzle[i + 1][j] == FICHA_A)
      {
        posiciones[0] = i;
        posiciones[1] = j;
      }
    }
    break;
  case FICHA_B:
    if (i > 0 && i < DIMENSION && j > 0 && j < DIMENSION - 1)
    {
      if (puzzle[i][j - 1] == FICHA_B && puzzle[i][j + 1] == FICHA_B && puzzle[i - 1][j] == FICHA_B)
      {
        posiciones[0] = i;
        posiciones[1] = j;
      }
    }
    break;
  case FICHA_C:
    if (i > 0 && i < DIMENSION - 1 && j >= 0 && j < DIMENSION)
    {
      if (puzzle[i - 1][j] == FICHA_C && puzzle[i + 1][j] == FICHA_C)
      {
        posiciones[0] = i;
        posiciones[1] = j;
      }
    }
    break;
  }
  return posiciones;
}

static void moverAverticalmente(struct tEstado *e, int fn, int fo, int col, int dir)
{
  e->puzzle[fn][col + 1] = FICHA_A;
  e->puzzle[fn][col - 1] = FICHA_A;
  e->puzzle[fn - (1 * dir)][col] = FICHA_A;
  e->puzzle[fo + (1 * dir)][col] = VACIO;
  e->puzzle[fo][col + 1] = VACIO;
  e->puzzle[fo][col - 1] = VACIO;
}

static void moverAhorizontalmente(struct tEstado *e, int cn, int co, int fil, int dir)
{
  e->puzzle[fil - 1][cn] = FICHA_A;
  e->puzzle[fil + 1][cn] = FICHA_A;
  e->puzzle[fil][cn - (1 * dir)] = FICHA_A;
  e->puzzle[fil][co + (1 * dir)] = VACIO;
  e->puzzle[fil - 1][co] = VACIO;
  e->puzzle[fil + 1][co] = VACIO;
}

static void moverBverticalmente(struct tEstado *e, int fn, int cn, int fo, int dir)
{
  e->puzzle[fn - 1 + dir][cn] = FICHA_B;
  e->puzzle[fn][cn + 1] = FICHA_B;
  e->puzzle[fn][cn - 1] = FICHA_B;
  e->puzzle[fo][cn + 1] = VACIO;
  e->puzzle[fo][cn - 1] = VACIO;
  e->puzzle[fo - dir][cn] = VACIO;
}

static void moverBhorizontalmente(struct tEstado *e, int fn, int cn, int co, int dir)
{
  e->puzzle[fn - 1][cn] = FICHA_B;
  e->puzzle[fn][cn - (1 * dir)] = FICHA_B;
  e->puzzle[fn][co + (1 * dir)] = VACIO;
  e->puzzle[fn - 1][co] = VACIO;
}

static void moverCverticalmente(struct tEstado *e, int fn, int fo, int col, int dir)
{
  e->puzzle[fn - (1 * dir)][col] = FICHA_C;
  e->puzzle[fo + (1 * dir)][col] = VACIO;
}

static void moverChorizontalmente(struct tEstado *e, int cn, int co, int fil)
{
  e->puzzle[fil - 1][cn] = FICHA_C;
  e->puzzle[fil][cn] = FICHA_C;
  e->puzzle[fil + 1][cn] = FICHA_C;
  e->puzzle[fil - 1][co] = VACIO;
  e->puzzle[fil][co] = VACIO;
  e->puzzle[fil + 1][co] = VACIO;
}

static void line(int *l, int size)
{
  printf("[");
  for (int i = 0; i < size - 1; ++i)
  {
    printf("%d ", l[i]);
  }
  printf("%d]", l[size - 1]);
}

static int manhattan(struct tEstado *e)
{
  struct tEstado *objetivo = estadoObjetivo();
  int sum = 0;
  for (int i = 1; i < DIMENSION; ++i)
  {
    sum += abs((e->posiciones[0][i] - objetivo->posiciones[0][i])) + abs((e->posiciones[1][i] - objetivo->posiciones[1][i]));
  }
  return sum;
}

struct tEstado *crearEstado(int puzzle[DIMENSION][DIMENSION])
{
  struct tEstado *nuevo = (struct tEstado *)malloc(sizeof(struct tEstado));
  int ficha = 0;
  int *centro = NULL;
  for (int i = 0; i < DIMENSION; ++i)
  {
    for (int j = 0; j < DIMENSION; ++j)
    {
      ficha = puzzle[i][j];
      nuevo->puzzle[i][j] = ficha;
      centro = esCentro(ficha, i, j, puzzle);
      if (centro[0] != -1 && centro[1] != -1)
      {
        nuevo->posiciones[0][ficha] = centro[0];
        nuevo->posiciones[1][ficha] = centro[1];
      }
    }
  }
  return nuevo;
}

struct tEstado *estadoInicial()
{
  return crearEstado(puzzleInicial);
}

struct tEstado *estadoObjetivo()
{
  return crearEstado(puzzleFinal);
}

bool iguales(struct tEstado *e1, struct tEstado *e2)
{
  for (int i = 0; i < 2; ++i)
  {
    for (int j = 0; j < DIMENSION; ++j)
    {
      if (e1->posiciones[i][j] != e2->posiciones[i][j])
      {
        return false;
      }
    }
  }
  return true;
}

bool esObjetivo(struct tEstado *e)
{
  return iguales(e, estadoObjetivo());
}

bool esValido(struct tEstado *e, int operador)
{
  bool valido = false;
  int fa = e->posiciones[0][FICHA_A];
  int fb = e->posiciones[0][FICHA_B];
  int fc = e->posiciones[0][FICHA_C];
  int ca = e->posiciones[1][FICHA_A];
  int cb = e->posiciones[1][FICHA_B];
  int cc = e->posiciones[1][FICHA_C];

  switch (operador)
  {
  case ARRIBA_A:
    valido = fa > 1 && e->puzzle[fa - 2][ca] == VACIO && e->puzzle[fa - 1][ca - 1] == VACIO && e->puzzle[fa - 1][ca + 1] == VACIO;
    break;
  case ABAJO_A:
    valido = fa < DIMENSION - 2 && e->puzzle[fa + 2][ca] == VACIO && e->puzzle[fa + 1][ca + 1] == VACIO && e->puzzle[fa + 1][ca - 1] == VACIO;
    break;
  case IZQUIERDA_A:
    valido = ca > 1 && e->puzzle[fa][ca - 2] == VACIO && e->puzzle[fa - 1][ca - 1] == VACIO && e->puzzle[fa + 1][ca - 1] == VACIO;
    break;
  case DERECHA_A:
    valido = ca < DIMENSION - 2 && e->puzzle[fa][ca + 2] == VACIO && e->puzzle[fa + 1][ca + 1] == VACIO && e->puzzle[fa - 1][ca + 1] == VACIO;
    break;
  case ARRIBA_B:
    valido = fb > 1 && e->puzzle[fb - 2][cb] == VACIO && e->puzzle[fb - 1][cb - 1] == VACIO && e->puzzle[fb - 1][cb + 1] == VACIO;
    break;
  case ABAJO_B:
    valido = fb < DIMENSION - 1 && e->puzzle[fb + 1][cb] == VACIO && e->puzzle[fb + 1][cb - 1] == VACIO && e->puzzle[fb + 1][cb + 1] == VACIO;
    break;
  case IZQUIERDA_B:
    valido = cb > 1 && e->puzzle[fb][cb - 2] == VACIO && e->puzzle[fb - 1][cb - 1] == VACIO;
    break;
  case DERECHA_B:
    valido = cb < DIMENSION - 2 && e->puzzle[fb][cb + 2] == VACIO && e->puzzle[fb - 1][cb + 1] == VACIO;
    break;
  case ARRIBA_C:
    valido = fc > 1 && e->puzzle[fc - 2][cc] == VACIO;
    break;
  case ABAJO_C:
    valido = fc < DIMENSION - 2 && e->puzzle[fc + 2][cc] == VACIO;
    break;
  case IZQUIERDA_C:
    valido = cc > 0 && e->puzzle[fc - 1][cc - 1] == VACIO && e->puzzle[fc][cc - 1] == VACIO && e->puzzle[fc + 1][cc - 1] == VACIO;
    break;
  case DERECHA_C:
    valido = cc < DIMENSION - 1 && e->puzzle[fc - 1][cc + 1] == VACIO && e->puzzle[fc][cc + 1] == VACIO && e->puzzle[fc + 1][cc + 1] == VACIO;
    break;
  }
  return valido;
}

struct tEstado *aplicaOperador(struct tEstado *e, int operador)
{
  struct tEstado *nuevo = (struct tEstado *)malloc(sizeof(struct tEstado));
  memcpy(nuevo, e, sizeof(struct tEstado));
  switch (operador)
  {
  case ARRIBA_A:
    nuevo->posiciones[0][FICHA_A]--;
    moverAverticalmente(nuevo, nuevo->posiciones[0][FICHA_A], e->posiciones[0][FICHA_A], e->posiciones[1][FICHA_A], 1);
    break;
  case ABAJO_A:
    nuevo->posiciones[0][FICHA_A]++;
    moverAverticalmente(nuevo, nuevo->posiciones[0][FICHA_A], e->posiciones[0][FICHA_A], e->posiciones[1][FICHA_A], -1);
    break;
  case IZQUIERDA_A:
    nuevo->posiciones[1][FICHA_A]--;
    moverAhorizontalmente(nuevo, nuevo->posiciones[1][FICHA_A], e->posiciones[1][FICHA_A], e->posiciones[0][FICHA_A], 1);
    break;
  case DERECHA_A:
    nuevo->posiciones[1][FICHA_A]++;
    moverAhorizontalmente(nuevo, nuevo->posiciones[1][FICHA_A], e->posiciones[1][FICHA_A], e->posiciones[0][FICHA_A], -1);
    break;
  case ARRIBA_B:
    nuevo->posiciones[0][FICHA_B]--;
    moverBverticalmente(nuevo, nuevo->posiciones[0][FICHA_B], nuevo->posiciones[1][FICHA_B], e->posiciones[0][FICHA_B], 0);
    break;
  case ABAJO_B:
    nuevo->posiciones[0][FICHA_B]++;
    moverBverticalmente(nuevo, nuevo->posiciones[0][FICHA_B], nuevo->posiciones[1][FICHA_B], e->posiciones[0][FICHA_B], 1);
    break;
  case IZQUIERDA_B:
    nuevo->posiciones[1][FICHA_B]--;
    moverBhorizontalmente(nuevo, nuevo->posiciones[0][FICHA_B], nuevo->posiciones[1][FICHA_B], e->posiciones[1][FICHA_B], 1);
    break;
  case DERECHA_B:
    nuevo->posiciones[1][FICHA_B]++;
    moverBhorizontalmente(nuevo, nuevo->posiciones[0][FICHA_B], nuevo->posiciones[1][FICHA_B], e->posiciones[1][FICHA_B], -1);
    break;
  case ARRIBA_C:
    nuevo->posiciones[0][FICHA_C]--;
    moverCverticalmente(nuevo, nuevo->posiciones[0][FICHA_C], e->posiciones[0][FICHA_C], nuevo->posiciones[1][FICHA_C], 1);
    break;
  case ABAJO_C:
    nuevo->posiciones[0][FICHA_C]++;
    moverCverticalmente(nuevo, nuevo->posiciones[0][FICHA_C], e->posiciones[0][FICHA_C], nuevo->posiciones[1][FICHA_C], -1);
  case IZQUIERDA_C:
    nuevo->posiciones[1][FICHA_C]--;
    moverChorizontalmente(nuevo, nuevo->posiciones[1][FICHA_C], e->posiciones[1][FICHA_C], nuevo->posiciones[0][FICHA_C]);
    break;
  case DERECHA_C:
    nuevo->posiciones[1][FICHA_C]++;
    moverChorizontalmente(nuevo, nuevo->posiciones[1][FICHA_C], e->posiciones[1][FICHA_C], nuevo->posiciones[0][FICHA_C]);
    break;
  }
  return nuevo;
}

int coste(struct tEstado *e, int operador)
{
  return 1;
}

void dispEstado(struct tEstado *e)
{
  printf("[");
  for (int i = 0; i < DIMENSION - 1; ++i)
  {
    if (i != 0)
    {
      printf(" ");
    }
    line(e->puzzle[i], DIMENSION);
    printf("\n");
  }
  printf(" ");
  line(e->puzzle[DIMENSION - 1], DIMENSION);
  printf("]\n");
}

void dispOperador(int operador)
{
  switch (operador)
  {
  case ARRIBA_A:
    printf("ARRIBA_A:\n");
    break;
  case ABAJO_A:
    printf("ABAJO_A:\n");
    break;
  case IZQUIERDA_A:
    printf("IZQUIERDA_A:\n");
    break;
  case DERECHA_A:
    printf("DERECHA_A:\n");
    break;
  case ARRIBA_B:
    printf("ARRIBA_B:\n");
    break;
  case ABAJO_B:
    printf("ABAJO_B:\n");
    break;
  case IZQUIERDA_B:
    printf("IZQUIERDA_B:\n");
    break;
  case DERECHA_B:
    printf("DERECHA_B:\n");
    break;
  case ARRIBA_C:
    printf("ARRIBA_C:\n");
    break;
  case ABAJO_C:
    printf("ABAJO_C:\n");
    break;
  case IZQUIERDA_C:
    printf("IZQUIERDA_C:\n");
    break;
  case DERECHA_C:
    printf("DERECHA_C:\n");
    break;
  }
}

int heuristica(struct tEstado *e)
{
  return manhattan(e);
}
