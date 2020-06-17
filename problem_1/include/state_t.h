#ifndef STATE_T_H
#define STATE_TH
#include <stdbool.h>
#include "vehicle.h"

typedef struct _state_t
{
  vehicle *vehicles;
  int rows;
  int cols;
} state_t;

bool is_target(state_t *state);
bool is_valid(state_t *state, unsigned option);
bool equals(state_t *state_a, state_t *state_b);

state_t *new_state(vehicle *matrix, int rows, int cols);

#endif