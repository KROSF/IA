#ifndef BUSQUEDA_H
#define BUSQUEDA_H
#include <glib.h>

gint vorax(gconstpointer e1, gconstpointer e2, gpointer nil);
gint AEstrella(gconstpointer e1, gconstpointer e2, gpointer nil);
int busquedaInformada(GCompareDataFunc f);
#endif