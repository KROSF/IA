#include <stdio.h>
#include "puzle.h"

int main(void) {
    tEstado* inicial = estadoInicial();
    tEstado* actual = inicial;
    dispEstado(inicial);
    int op = 0;
    while (testObjetivo(actual) == 0) {
        printf("Ingrese un movimiento [1-4]: ");
        scanf("%d",&op);
        if(esValido(op,actual) == 1)
            actual = aplicaOperador(op,actual);
        dispEstado(actual);
    }
    return 0;
}
