#include "search.h"

#include "bench.h"
#include "colors.h"
#include "node.h"

typedef struct performance_t {
  int created;
  int visited;
  int iterations;
  int solutions;
} Performance;

static void performance_display(FILE* stream, const Performance* p) {
  fprintf(stream,
          "{ \n      %screated:%s %d,\n      %svisited:%s %d,\n      %siterations:%s %d,\n      %ssolutions:%s %d\n  }",
          YELLOW, NORMAL, p->created, YELLOW, NORMAL, p->visited, YELLOW, NORMAL, p->iterations, YELLOW, NORMAL,
          p->solutions);
}

static void time_display(FILE* stream, float cpu_time, float wall_time) {
  fprintf(stream, "{ %scpu_time:%s %f, %swall_time:%s %f }", YELLOW, NORMAL, cpu_time, YELLOW, NORMAL, wall_time);
}

static void info_display(FILE* stream, const Performance* p, float cpu_time, float wall_time) {
  fprintf(stream, "\n{ \n%s  statistics: %s", YELLOW, NORMAL);
  performance_display(stream, p);
  fprintf(stream, ",\n%s  time: %s", YELLOW, NORMAL);
  time_display(stream, cpu_time, wall_time);
  fprintf(stream, "\n}\n");
}

static void path_display(FILE* stream, const Node* node) {
  if (node->prev == NULL) {
    state_display(stream, node->state);
    printf("\n");
  } else {
    path_display(stream, node->prev);
    state_display(stream, node->state);
    printf("\n");
  }
}

static int without_heuristic(const State* state) { return 0; }

static int manhattan_heuristic(const State* state) {
  return abs(state->vehicles[0].down.x - state->exit.down.x) + abs(state->vehicles[0].down.y - state->exit.down.y);
}

static int beam_search_heuristic(const State* state) {
  int value = 0;
  for (size_t i = 0; i < 4; ++i) {
    if (i != 0) {
      int distance = abs(state->vehicles[0].down.x - state->vehicles[i].down.x) +
                     abs(state->vehicles[0].down.y - state->vehicles[i].down.y);
      value -= distance;
    } else {
      int distance =
          abs(state->exit.down.x - state->vehicles[i].down.x) + abs(state->exit.down.y - state->vehicles[i].down.y);
      if (distance == 1) {
        return -100;
      }
      value += distance;
    }
  }
  return value;
}

static void blind_search(State* initial_state, bool is_fifo) {
  list_t* open = list_new();
  open->free = free;

  list_t* closed = list_new();
  closed->match = node_equals;
  closed->free = free;

  bool is_target = false;
  list_t* succesors = NULL;
  list_node_t* found = NULL;
  Node* current = NULL;

  Performance performance = {1, 0, 0, 0};
  float start_cpu = 0.0;
  float start_wall = 0.0;
  float end_cpu = 0.0;
  float end_wall = 0.0;

  // Add first node to start searching
  list_rpush(open, list_node_new(node_initial(initial_state, without_heuristic)));
  start_cpu = cpu();
  start_wall = wall();

  while (!is_target && open->len > 0) {
    performance.iterations += 1;
    current = (Node*)list_lpop(open)->val;
    is_target = state_is_target(current->state);
    found = list_find(closed, current);
    if (!is_target && found == NULL) {
      succesors = node_expand(current, without_heuristic);
      performance.visited += 1;
      performance.created += succesors->len;
      open = is_fifo ? list_merge(open, succesors) : list_merge(succesors, open);
      list_rpush(closed, list_node_new(current));
    }
  }

  end_cpu = cpu();
  end_wall = wall();

  if (is_target) {
    path_display(stdout, current);
    performance.solutions += 1;
  }

  info_display(stdout, &performance, end_cpu - start_cpu, end_wall - start_wall);

  list_destroy(open);
  list_destroy(closed);
}

void breadth_first_search(State* initial) { blind_search(initial, true); }
void depth_first_search(State* initial) { blind_search(initial, false); }

static void search(State* initial_state, Heuristic heuristic, list_cmp_t cmp) {
  list_t* open = list_new();
  open->cmp = cmp;
  open->free = free;

  list_t* closed = list_new();
  closed->match = node_equals;
  closed->free = free;

  bool is_target = false;

  list_t* succesors = NULL;
  list_node_t* found = NULL;
  Node* current = NULL;

  Performance performance = {1, 0, 0, 0};
  float start_cpu = 0.0;
  float start_wall = 0.0;
  float end_cpu = 0.0;
  float end_wall = 0.0;

  // Add first node to start searching
  list_rpush(open, list_node_new(node_initial(initial_state, heuristic)));

  start_cpu = cpu();
  start_wall = wall();

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
      performance.created = performance.created + succesors->len;
      // merge into open all expand of current
      open = list_merge(open, succesors);
      // sort all open nodes based on a comparator
      list_sort(open);
      // save current beacuse is not a solution to avoid future exploration
      list_rpush(closed, list_node_new(current));
    }
  }

  end_cpu = cpu();
  end_wall = wall();

  if (is_target) {
    path_display(stdout, current);
    performance.solutions += 1;
  }

  info_display(stdout, &performance, end_cpu - start_cpu, end_wall - start_wall);

  list_destroy(open);
  list_destroy(closed);
}

void a_start_search(State* initial) { search(initial, manhattan_heuristic, node_a_start_comparator); }
void vorax_search(State* initial) { search(initial, manhattan_heuristic, node_vorax_comparator); }

static void local_search(State* initial_state, Heuristic heuristic, list_cmp_t cmp, int k) {
  list_t* open = list_new();
  open->free = free;

  list_t* closed = list_new();
  closed->match = node_equals;
  closed->free = free;

  Node* target = NULL;
  bool is_target = false;
  list_t* succesors = list_new();
  succesors->cmp = cmp;
  succesors->free = free;

  Performance performance = {1, 0, 0, 0};
  float start_cpu = 0.0;
  float start_wall = 0.0;
  float end_cpu = 0.0;
  float end_wall = 0.0;

  // Add first node to start searching
  list_rpush(open, list_node_new(node_initial(initial_state, heuristic)));

  start_cpu = cpu();
  start_wall = wall();

  // loop until we found the solution or explored all
  while (!is_target && open->len > 0) {
    performance.iterations += 1;

    for (list_node_t* node = open->head; node != NULL && !is_target; node = node->next) {
      is_target = state_is_target(((Node*)node->val)->state);
      target = is_target ? ((Node*)node) : NULL;
    }

    if (!is_target) {
      for (list_node_t* node = open->head; node != NULL; node = node->next) {
        succesors = list_merge(succesors, node_expand((Node*)node->val, heuristic));
      }

      performance.visited += open->len;
      performance.created += succesors->len;

      list_merge(closed, open);
      open = list_new();
      open->free = free;

      list_sort(succesors);
      list_slice(open, succesors, k);
    }
  }

  end_cpu = cpu();
  end_wall = wall();

  if (is_target) {
    path_display(stdout, target);
    performance.solutions += 1;
  }

  info_display(stdout, &performance, end_cpu - start_cpu, end_wall - start_wall);

  list_destroy(open);
  list_destroy(succesors);
}

void beam_search(State* initial, int k) { local_search(initial, beam_search_heuristic, node_a_start_comparator, k); }
