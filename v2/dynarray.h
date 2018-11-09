#ifndef DYNARRAY_H
#define DYNARRAY_H
 
struct dynarray {
    void ** buffer;
    unsigned int size;
    unsigned int count;
};
 
typedef struct dynarray dynarray;
 
typedef void (*dynarray_forfn)(void *);

typedef unsigned int (*dynarray_equal_cmp)(const void*, const void*);
 
dynarray * dynarray_create(unsigned int startsize);
void dynarray_empty(dynarray * array);
void dynarray_delete(dynarray * array);
void dynarray_add_tail(dynarray * array, void * data);
void dynarray_add_head(dynarray * array, void * data);
void * dynarray_remove_tail(dynarray * array);
void * dynarray_remove_head(dynarray * array);
void dynarray_insert(dynarray *array, unsigned int pos, void *data);
void * dynarray_remove(dynarray *array, unsigned int pos);
void * dynarray_get(const dynarray * array, unsigned int pos);
void * dynarray_set(dynarray * array, unsigned int pos, void * data);
void dynarray_for_each(const dynarray * array, dynarray_forfn fun);
unsigned int dynarray_get_count(const dynarray * array);
void dynarray_set_size(dynarray * array, unsigned int size);
unsigned int dynarray_elto_belongs(dynarray * array, void* data, dynarray_equal_cmp);
 
#endif /* DYNARRAY_H */
