#ifndef SEARCH_H
#define SEARCH_H
#include "list.h"
#include "state.h"

void breadth_first_search(State* initial);

void depth_first_search(State* initial);

void a_start_search(State* initial);

void vorax_search(State* initial);

void beam_search(State* initial, int k);

#endif