#ifndef NODE_H
#define NODE_H
#include "list.h"
#include "state.h"

typedef struct node_t {
  State* state;
  struct node_t* prev;
  Operator op;
  int cost;
  int depth;
  int value;
} Node;

list_t* node_expand(Node* node, Heuristic heuristic);
Node* node_initial(State* initial_state, Heuristic heuristic);
int node_equals(void* rhs, void* lhs);
int node_vorax_comparator(void* rhs, void* lhs);
int node_blind_comparator(void* rhs, void* lhs);
int node_a_start_comparator(void* rhs, void* lhs);

#endif