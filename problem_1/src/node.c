#include "node.h"

Node* node_initial(State* initial_state, Heuristic heuristic) {
  Node* initial = (Node*)malloc(sizeof(Node));
  initial->state = initial_state;
  initial->cost = 0;
  initial->prev = NULL;
  initial->depth = 0;
  initial->value = heuristic(initial_state);
  return initial;
}

static Node* node_succesor(Node* node, Operator op, Heuristic heuristic) {
  Node* succesor = (Node*)malloc(sizeof(Node));
  succesor->state = state_apply_operator(node->state, op);
  succesor->prev = node;
  succesor->op = op;
  succesor->cost = node->cost + 1;
  succesor->depth = node->depth + 1;
  succesor->value = heuristic(succesor->state);
  return succesor;
}

list_t* node_expand(Node* node, Heuristic heuristic) {
  list_t* successors = list_new();
  for (Operator op = UP_V0; op < OPERATORS; ++op) {
    if (state_is_valid_operator(node->state, op)) {
      list_rpush(successors, list_node_new(node_succesor(node, op, heuristic)));
    }
  }

  return successors;
}

int node_equals(void* rhs, void* lhs) {
  Node* a = (Node*)rhs;
  Node* b = (Node*)lhs;
  return (int)state_equals(a->state, b->state);
}