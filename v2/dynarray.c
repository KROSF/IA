#include <stdlib.h>
#include <string.h> /* For memcpy and memmove */
 
#include "dynarray.h"
 
#define START_SIZE 4 /* Initial buffer size if not specified */
 
dynarray * dynarray_create(unsigned int size)
{
    dynarray * array = malloc(sizeof(dynarray));
    if (array != NULL) {
        if (size) {
            array->buffer = malloc(size * sizeof(void*));
            if (array->buffer) {
                array->size = size;
            }
            else {
                free(array);
                array = NULL;
            }
        }
        else {
            array->buffer = NULL;
            array->size = 0;
        }
        array->count = 0;
    }
    return array;
}
 
void dynarray_empty(dynarray * array)
{
    array->count = 0;
}
 
void dynarray_delete(dynarray * array)
{
    if (array) {
        free(array->buffer);
        free(array);
    }
}
 
void dynarray_add_tail(dynarray * array, void * data)
{
    if (array->count == array->size) {
        /* No more space */
        if (array->buffer != NULL) {
            void **buffer = realloc(array->buffer, array->size * 2 * sizeof(void*));
            array->buffer = buffer;
            array->size *= 2;
        }
        else {
            array->buffer = malloc(START_SIZE * sizeof(void*));
            array->size = START_SIZE;
        }
    }
    if (array->buffer != NULL) {
        array->buffer[array->count] = data;
        array->count++;
    }
}
 
void dynarray_add_head(dynarray * array, void * data)
{
    if (array->count == array->size) {
        /* No more space */
        if (array->buffer != NULL) {
            void **temp = malloc(array->size * 2 * sizeof(void*));
            if (temp) {
                /* Copy the elements one space to the right */
                memcpy(temp + 1, array->buffer, array->count * sizeof(void*));
                free(array->buffer);
                array->buffer = temp;
                array->size *= 2;
            }
        }
        else {
            array->buffer = malloc(START_SIZE * sizeof(void*));
            if (array->buffer) {
                array->size = START_SIZE;
            }
        }
    }
    else {
        /* Move the elements one space to the right */
        memmove(array->buffer + 1, array->buffer, array->count * sizeof(void*));
    }
    if (array->buffer != NULL) {
        array->buffer[0] = data;
        array->count++;
    }
}
 
void * dynarray_remove_tail(dynarray * array)
{
    void * data = NULL;
    if (array->count > 0) {
        data = array->buffer[array->count - 1];
        array->count--;
    }
    return data;
}
 
void * dynarray_remove_head(dynarray * array)
{
    void * data = NULL;
    if (array->count > 0) {
        data = array->buffer[0];
        /* Move the elements one space to the left */
        memmove(array->buffer, array->buffer + 1, (array->count - 1) * sizeof(void*));
        array->count--;
    }
    return data;
}
 
void dynarray_insert(dynarray *array, unsigned int pos, void *data)
{
    if (pos == 0) {
        dynarray_add_head(array, data);
    }
    else if (pos == array->count) {
        dynarray_add_tail(array, data);
    }
    else if (pos < array->count) {
        //unsigned int i;
        if (array->count == array->size) {
            /* Reallocate the buffer and copy, leaving a space */
            void **temp = malloc(array->size * 2 * sizeof(void*));
            if (temp) {
                memcpy(temp, array->buffer, pos * sizeof(void*));
                memcpy(temp + pos + 1, array->buffer + pos, (array->count - pos) * sizeof(void*));
                free(array->buffer);
                array->buffer = temp;
                array->size *= 2;
            }
        }
        else {
            /* Move the elements after to the right */
            memmove(array->buffer + pos + 1, array->buffer + pos,
                    (array->count - pos) * sizeof(void*));
        }
        array->buffer[pos] = data;
        array->count++;
    }
}
 
void * dynarray_remove(dynarray *array, unsigned int pos)
{
    void *data;
    if (array->count < pos + 1) {
        data = NULL;
    }
    else if (pos == 0) {
        data = dynarray_remove_head(array);
    }
    else if (pos == array->count - 1) {
        data = dynarray_remove_tail(array);
    }
    else {
        //unsigned int i;
        data = array->buffer[pos];
        /* Move the following elements left */
        memmove(array->buffer + pos, array->buffer + pos + 1,
                (array->count - pos - 1) * sizeof(void*)); 
        array->count--;
    }
    return data;
}
 
void * dynarray_get(const dynarray * array, unsigned int pos)
{
    void * data = NULL;
    if (pos < array->count) {
        data = array->buffer[pos];
    }
    return data;
}
 
void * dynarray_set(dynarray * array, unsigned int pos, void * data)
{
    void * temp = NULL;
    if (pos == array->count) {
        dynarray_add_tail(array, data);
    }
    else if (pos < array->count) {
        temp = array->buffer[pos];
        array->buffer[pos] = data;
    }
    return temp;
}
 
void dynarray_set_size(dynarray * array, unsigned int size)
{
     
    array->buffer = realloc(array->buffer, size);
    if (array->buffer) {
        array->size = size;
        if (array->size < array->count) {
            array->count = array->size;
        }
    }
    else {
        array->size = 0;
        array->count = 0;
    }
}
 
void dynarray_for_each(const dynarray * array, dynarray_forfn fun)
{
    unsigned int i;
 
    for (i = 0; i < array->count; i++) {
        fun(array->buffer[i]);
    }
}
 
unsigned int dynarray_get_count(const dynarray * array)
{
    return array->count;
}

unsigned int dynarray_elto_belongs(dynarray * array,void* data, dynarray_equal_cmp cmp)
{
    unsigned int belongs = 0;
    for (unsigned int i = 0; i < array->count && !belongs; i++) {
        if (cmp((void*) data, (void*)array->buffer[i]) == 1) {
            belongs = 1;
        }
    }
    return belongs;
}
