#include <stdlib.h>
 
#include "sortedarray.h"
 
sortedarray * sortedarray_create(sortedarray_cmpfn compare)
{
    sortedarray *array = malloc(sizeof(sortedarray));
    if (array) {
        array->array = dynarray_create(0);
        array->compare = compare;
    }
    return array;
}
 
void sortedarray_delete(sortedarray * array)
{
    if (array) {
        dynarray_delete(array->array);
        free(array);
    }
}
 
typedef struct {
    void * data;
    unsigned int pos;
} search_result;
 
static search_result sortedarray_search(const sortedarray *array, const void *data)
{
    search_result sr;
    unsigned int elements = array->array->count;
    unsigned int offset = 0;
    unsigned int middle = 0;
     
    sr.data = NULL;
    while (elements > 0 && !sr.data) {
        int result;
        middle = elements / 2;
        result = array->compare(data, dynarray_get(array->array, offset + middle));
        if (result > 0) {
            offset = offset + middle + 1;
            elements = elements - (middle + 1);
        }
        else if (result < 0) {
            elements = middle;
        }
        else {
            sr.data = dynarray_get(array->array, offset + middle);
            offset += middle;
        }
    }
    sr.pos = offset;
 
    return sr;
}
 
void * sortedarray_add(sortedarray * array, void * data)
{
    search_result result = sortedarray_search(array, data);
    void *existing = result.data;
    if (existing) {
        /* Replace */
        dynarray_set(array->array, result.pos, data);
    }
    else {
        /* Add new */
        dynarray_insert(array->array, result.pos, data);
    }
    return existing;
}
 
void * sortedarray_remove(sortedarray * array, const void * data)
{
    search_result result = sortedarray_search(array, data);
    if (result.data) {
        dynarray_remove(array->array, result.pos);
    }
    return result.data;
}
 
void * sortedarray_find(const sortedarray * array, const void * data)
{
    search_result result = sortedarray_search(array, data);
    return result.data;
}
 
void sortedarray_for_each(const sortedarray * array, sortedarray_forfn forfn)
{
    dynarray_for_each(array->array, forfn);
}
 
unsigned int sortedarray_get_count(const sortedarray *array)
{
    return array->array->count;
}
 
void * sortedarray_get(const sortedarray *array, unsigned int pos)
{
    return dynarray_get(array->array, pos);
}
 
void * sortedarray_remove_at(sortedarray * array, unsigned int pos)
{
    return dynarray_remove(array->array, pos);
}
 
int sortedarray_find_index(const sortedarray *array, const void *data)
{
    int index = -1;
    search_result result = sortedarray_search(array, data);
    if (result.data) {
        index = result.pos;
    }
    return index;
}

void * sortedarray_add_dynarray(sortedarray * array, dynarray * darray) {
    void* existing = NULL;
    for (int i = 0; i < darray->count; i++) {
        existing = sortedarray_add(array, dynarray_get(darray, i));
    }
    return existing;
}
