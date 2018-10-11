#ifndef PUZLE_H
#define PUZLE_H
#define N 3

enum OPERADORES {ARRIBA, ABAJO, IZQUIERDA, DERECHA};

typedef struct {
    int celdas[N][N];
    int fila[N * N];
    int columna[N * N];
} tEstado;

int esValido(unsigned op, tEstado* estado);
int iguales(tEstado* m, tEstado* n);
int testObjetivo(tEstado* estado);
tEstado *aplicaOperador(unsigned op, tEstado* estado);
#endif