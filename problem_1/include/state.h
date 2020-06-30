#ifndef STATE_H
#define STATE_H
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

typedef int (*Heuristic)(const State *state);

/**
 * @brief  Generate a raandom state.
 */
State state_random();
/**
 * @brief  Get state from stdin;
 */
State state_from_stdin();
/**
 * @brief  Check if current state is target.
 */
bool state_is_target(const State *state);
/**
 * @brief  display state to stream.
 */
void state_display(FILE *stream, const State *state);
/**
 * @brief check if to state are equals
 */
bool state_equals(const State *rhs, const State *lhs);
/**
 * @brief apply an operator to the state
 */
State *state_apply_operator(const State *state, Operator op);
/**
 * @brief check if given operator is valid with current state
 */
bool state_is_valid_operator(const State *state, Operator op);
/**
 * @brief create a new state with vehicles and grid dimensions.
 */
State state_new(Vehicle vehicles[4], int rows, int cols, Vehicle exit);

#endif