#include <stdio.h>

#define CTEST_MAIN
#define CTEST_SEGFAULT
#define CTEST_COLOR_OK

#include "ctest.h"
#include "puzle.h"

CTEST(puzzleAlum, crear_estado) {
    tEstado* inicio = crearEstado(puzle_inicial);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            ASSERT_EQUAL(inicio->celdas[i][j], puzle_inicial[i][j]);
        }
    }
}

CTEST(puzzleAlum, estado_incial) {
    tEstado* inicio = estadoInicial();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            ASSERT_EQUAL(inicio->celdas[i][j], puzle_inicial[i][j]);
        }
    }
}

CTEST(puzzleAlum, estado_objetivo) {
    tEstado* inicio = estadoObjetivo();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            ASSERT_EQUAL(inicio->celdas[i][j], puzle_final[i][j]);
        }
    }
}

CTEST(puzzleAlum, coste) {
    ASSERT_EQUAL(1, coste(2, estadoInicial()));
}

CTEST(puzzleAlum, iguales) {
    tEstado* e1 = crearEstado(puzle_final);
    tEstado* e2 = estadoObjetivo();
    ASSERT_TRUE(iguales(e1,e2));
}

CTEST(puzzleAlum, test_objetivo) {
    ASSERT_TRUE(testObjetivo(estadoObjetivo()));
}

CTEST(puzzleAlum, es_valido) {
    tEstado* inicial = estadoInicial();
    ASSERT_TRUE(esValido(1, inicial));
    ASSERT_FALSE(esValido(2, inicial));
    ASSERT_TRUE(esValido(3, inicial));
    ASSERT_TRUE(esValido(4, inicial));
}

CTEST(puzzleAlum, aplica_operador) {
    tEstado* actual = estadoInicial();
    int izquierda[N][N] = {{1,2,3},{8,6,4},{0,7,5}};

    actual = aplicaOperador(1, actual);
    ASSERT_TRUE(iguales(actual, crearEstado(puzle_final)));
    actual = aplicaOperador(2, actual);
    ASSERT_TRUE(iguales(actual, crearEstado(puzle_inicial)));
    actual = aplicaOperador(3,actual);
    ASSERT_TRUE(iguales(actual, crearEstado(izquierda)));
    actual = aplicaOperador(4,actual);
    ASSERT_TRUE(iguales(actual, crearEstado(puzle_inicial)));
}

int main(int argc, const char *argv[]) {
    int result = ctest_main(argc, argv);
    //printf("\nNOTE: some tests will fail, just to show how ctest works! ;)\n");
    return result;
}

