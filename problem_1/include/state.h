#ifndef STATE_T_H
#define STATE_TH
#include <stdbool.h>

#include "vehicle.h"

typedef struct state_t {
  Vehicle vehicles[4];
  int rows;
  int cols;
  Vehicle exit;
} State;

typedef enum operator_t {
  UP_V0,
  DOWN_V0,
  LEFT_V0,
  RIGHT_V0,
  UP_V1,
  DOWN_V1,
  LEFT_V1,
  RIGHT_V1,
  UP_V2,
  DOWN_V2,
  LEFT_V2,
  RIGHT_V2,
  UP_V3,
  DOWN_V3,
  LEFT_V3,
  RIGHT_V3,
  OPERATORS
} Operator;

bool state_is_target(const State *state);
void state_apply_operator(State *state, Operator op);
bool state_is_valid_operator(const State *state, Operator op);
bool state_equals(const State *state_a, const State *state_b);
State state_new(Vehicle vehicles[4], int rows, int cols, Vehicle exit);

#endif