#ifndef PUZLE_H
#define PUZLE_H

#define ARRIBA 1
#define ABAJO 2
#define IZQUIERDA 3
#define DERECHA 4
#define NUM_OPERADORES 4
#define N 3


#ifndef _tEstado_
#define _tEstado_
    typedef struct {
        int celdas[N][N];
        int fila[N * N];
        int col[N * N];
    } tEstado;
#endif


static int puzle_inicial[N][N] = {
    {8,1,3},
    {0,2,4},
    {7,6,5}
};
// static int puzle_inicial[N][N] = {{0, 1}, {3, 2}};
// static int puzle_final[N][N] = {{1, 2},{0, 3}};
static int puzle_final[N][N] = {
    {1,2,3},
    {8,0,4},
    {7,6,5}
};

/**
 * @brief  A partir de una configuracion de fichas
 *         construye un estado valido.
 * @param  celdas[N][N]: configuracion de fichas para generar estado.
 * @retval tEstado con la cofiguracion dada.
 */
tEstado* crearEstado(int celdas[N][N]);

/**
 * @brief  Genera el estado inicial.
 * @note   A partir de crearEstado y puzle_inicial
 * @retval Estado desde el cual se inicia.
 */
tEstado* estadoInicial();

/**
 * @brief  Calcula el coste de aplicar un operador.
 * @param  op: Operador a aplicar.
 * @param  estado: Estado al que se aplica el operador.
 * @retval Coste de aplicar el operador.
 */
int coste(unsigned op, tEstado* estado);

/**
 * @brief  Muestra el contenido del puzle.
 * @param  estado: A mostrar.
 */
void dispEstado(tEstado* estado);

/**
 * @brief  Muestra el nombre de cada operador
 * @note   Arriba, Abajo, Izquierda, Derecha.
 * @param  op: Operador del que se desea saber el nombre.
 */
void dispOperador(unsigned op);

/**
 * @brief  Genera el estado final.
 * @note   A partir de crearEstado y puzle_final.
 * @retval Estado donde acaba el problema.
 */
tEstado* estadoObjetivo();

/**
 * @brief  Comprueba si es posible aplicar un operador a 
 *         una configuracion determinada para el puzle.
 * @note   
 * @param  op: Operador a aplicar.
 * @param  estado: Sobre el que se intenta aplicar.
 * @retval 1: si el movimiento es valido.
 *         0: en otro caso.
 */
int esValido(unsigned op, tEstado* estado);

/**
 * @brief  Aplica un operador a una configuracion concreta del puzle.
 * @param  op: Operador a aplicar.
 * @param  estado: Sobre el que aplica op.
 * @retval nueva configuracion del tablero tras el movimiento.
 */
tEstado *aplicaOperador(unsigned op, tEstado* estado);

/**
 * @brief  Compara si dos estados son iguales.
 * @note   
 * @param  s: tEstado cualquiera a comparar.
 * @param  t: tEstado cualquiera a comparar.
 * @retval 1: si son iguales.
 *         0: en caso constrario.
 */
int iguales(tEstado* s, tEstado* t);

/**
 * @brief  Comprueba si un estado es el estado onjetivo.
 * @param  estado: Que se desea comprobar.
 * @retval 1: si estado es igual que estado Objetivo.
 *         0: en caso contrario.
 */
int testObjetivo(tEstado* estado);

/**
 * @brief  Heuristica de manhattan.
 * @param  act: Estado para el cual calculamos la heuristica.
 * @retval valor de la heuristica.
 */
int hManhattan(tEstado* act);

/**
 * @brief  Heuristica teniendo en cuenta las piezas mal colocadas.
 * @param  act: Estado para el cual calculamos la heuristica.
 * @retval valor de la heuristica.
 */
int hPiezasMalColocadas(tEstado* act);

#endif
