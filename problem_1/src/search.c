#include "search.h"

#include "node.h"

typedef struct performance_t {
  int created;
  int visited;
  int iterations;
  int solutions;
} Performance;

void search(State* initial_state, Heuristic heuristic) {
  bool is_target = false;
  list_t* open = list_new();
  list_t* closed = list_new();
  closed->match = node_equals;
  list_t* succesors = NULL;
  list_node_t* found = NULL;
  Node* current = NULL;
  Node* initial = node_initial(initial_state, heuristic);
  Performance performance = {
      .created = 1,
      .visited = 0,
      .iterations = 0,
      .solutions = 0,
  };

  // Add first node to start searching
  list_rpush(open, list_node_new(initial));

  // loop until we found the solution or explored all
  while (!is_target && open->len > 0) {
    performance.iterations += 1;
    // pick fisrt node from open list
    current = (Node*)list_lpop(open)->val;
    // check is current node is a valid final state
    is_target = state_is_target(current->state);
    // check if node was previously explored
    found = list_find(closed, current);
    // if node is not target a was not expored before, the explorer
    if (!is_target && found == NULL) {
      succesors = node_expand(current, heuristic);
      performance.visited += 1;
      performance.created += succesors->len;
      // merge into open all expand of current
      list_merge(open, succesors);
      // sort all open nodes based on a comparator
      list_sort(open);
      // save current beacuse is not a solution to avoid future exploration
      list_rpush(closed, current);
      list_destroy(succesors);
    }
  }

  if (is_target) {
    performance.solutions += 1;
  }

  list_destroy(open);
  list_destroy(closed);
}