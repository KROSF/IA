# Problema 2

Para iniciar el juego con otro estado podemos pasarle la opcion -s o --state seguido del estado que queremos
debe contener el mismo numero de fichas de A y B.

> ./ab.out -s ABBABBAA

Si no se le pasa ninguna opcion se inicializa con un estado por defecto.

Para iniciar una jugado que implique algunos de los limites se debe utilizar el inidice -1;

Por Ejemplo:

* { begin: -1, end: 1 }: Para comer la ficha en la posicion 0 entre el limite izquierdo y el indice 1;
* { begin: 6, end: -1 }: Para comer la ficha en la posicion 7 entre el indice 6 y el limite derecho;

Los ficheros importantes son:

* src/main.c
* src/minimax.c -> contiene la implemetacion de los cuatro tipos de busquedas
* src/node.c
* src/move.c


Las funciones minimax y minimax_with_limit son iguales la primera llama 
a la segunda con el limite de int (2147483647) por lo tanto siempre evalua 
todo el arbol en este problema concreto.

Pasa lo mismo en el caso de minimax_alpha_beta y minimax_alpha_beta_with_limit.

Nota: El código solo se ha compilado en linux y mac os.
