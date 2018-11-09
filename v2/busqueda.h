#ifndef BUSQUEDA_H
#define BUSQUEDA_H

typedef int (*FuncionEvaluacion)(const void*, const void*);

int vorax(const void*, const void*);
int AEstrella(const void*, const void*);
int busquedaInformada(FuncionEvaluacion f);

#endif
