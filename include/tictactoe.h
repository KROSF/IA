#define N 9

typedef struct _tNodo {
  int celdas[N];
  int vacias;
} tNodo;

static int tablero_inicial[N] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

tNodo *crearNodo(int celda[N]);
tNodo *NodoInicial();
tNodo *aplicaJugada(tNodo *act, int jugador, int jugada);
int esValida(tNodo *act, int jugada);
int terminal(tNodo *act, int jugador);
void dispNodo(tNodo *n);
int opuesto(int jugador);
int lleno(tNodo *s);