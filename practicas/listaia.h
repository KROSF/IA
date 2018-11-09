#define MAXI 3000

#ifndef _tElemento_
#define _tElemento_
   typedef void *tElemento;
#endif

#define ERROR(s) printf("%s\n", s);

#ifndef _LISTAIA_H_
#define _LISTAIA_H_
    typedef struct {
        tElemento* elementos;
        int Lmax;  //longitud m�xima de la lista
        int Nelem; //n�mero de elmentos
        int inicio, fin;
    }tLista;

    typedef tLista *Lista;

    Lista CrearLista(int TamMax);
    int ListaVacia (Lista C);
    int ListaLlena(Lista C);

    //Pre: Lista C no est� llena
    //Post:Devuelve el elemento primero de la lista
    void InsertarPrimero(tElemento *x, Lista C);

    //Pre: Lista C no est� llena
    //Post:Devuelve el ultimo elemento de la lista
    void InsertarUltimo(tElemento *x, Lista C);

    //Pre: Lista C no est� vac�a, i: es un �ndice entre 0 y TamMax
    //Post:Devuelve el elemento i-�simo de la lista C
    tElemento *ExtraerElem(Lista C,int i);

    //Pre: Lista C no est� vac�a
    //Post:Devuelve el primer elemento de la lista C
    tElemento *ExtraerPrimero(Lista C);

    //Pre: Lista L1 no est� vac�a
    //Post: Devuelve L1=L1+L2
    Lista Concatenar(Lista L1,Lista L2);
    Lista Ordenar(Lista L1, Lista L2);

    void EliminarPrimero(Lista C);

    void DestruirLista(Lista C);

    int buscarRepe(tEstado* e, Lista C);
    
    void dispList(Lista L1);

#endif
