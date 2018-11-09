#ifndef SORTEDARRAY_H
#define SORTEDARRAY_H
 
#include "dynarray.h"
 
typedef int (*sortedarray_cmpfn)(const void*, const void*);
typedef void (*sortedarray_forfn)(void*);
 
struct sortedarray {
    dynarray *array;
    sortedarray_cmpfn compare;
};
 
typedef struct sortedarray sortedarray;
 
sortedarray * sortedarray_create(sortedarray_cmpfn compare);
void sortedarray_delete(sortedarray * array);
void * sortedarray_add(sortedarray * array, void * data);
void * sortedarray_remove(sortedarray * array, const void * data);
void * sortedarray_find(const sortedarray * array, const void * data);
void sortedarray_for_each(const sortedarray * array, sortedarray_forfn forfn);
unsigned int sortedarray_get_count(const sortedarray *array);
void * sortedarray_get(const sortedarray *array, unsigned int pos);
void * sortedarray_remove_at(sortedarray *array, unsigned int pos);
int sortedarray_find_index(const sortedarray *array, const void * data);
void * sortedarray_add_dynarray(sortedarray * array,dynarray * darray);
 
#endif /* SORTEDARRAY_H */
