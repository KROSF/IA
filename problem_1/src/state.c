#include "state.h"

#include <stdlib.h>
#include <string.h>

static int vehicle_index_from_operator(Operator op) {
  switch (op) {
    case UP_V0:
    case DOWN_V0:
    case LEFT_V0:
    case RIGHT_V0:
      return 0;
    case UP_V1:
    case DOWN_V1:
    case LEFT_V1:
    case RIGHT_V1:
      return 1;
    case UP_V2:
    case DOWN_V2:
    case LEFT_V2:
    case RIGHT_V2:
      return 2;
    case UP_V3:
    case DOWN_V3:
    case LEFT_V3:
    case RIGHT_V3:
      return 3;
  }
}

static bool vehicle_contains_point(const Vehicle *vehicle, const Point *point) {
  return point->x >= vehicle->upper.x && point->x <= vehicle->down.x && point->y >= vehicle->upper.y &&
         point->y <= vehicle->down.y;
}

static bool vehicle_contains_vehicle(const Vehicle *lhs, const Vehicle *rhs) {
  const Point upper_down = (Point){.x = rhs->upper.x, .y = rhs->down.y};
  const Point down_upper = (Point){.x = rhs->down.x, .y = rhs->upper.y};

  return vehicle_contains_point(lhs, &rhs->upper) || vehicle_contains_point(lhs, &rhs->down) ||
         vehicle_contains_point(lhs, &upper_down) || vehicle_contains_point(lhs, &down_upper);
}

static bool is_valid_movement(const Vehicle *vehicle, const State *state, Point direction) {
  Vehicle next = {.upper = point_add(&vehicle->upper, &direction), .down = point_add(&vehicle->down, &direction)};

  if (!(next.upper.x > 0) || !(next.down.x < state->rows) || !(next.upper.y > 0) || !(next.down.y < state->cols)) {
    return false;
  }

  for (size_t i = 0; i < 4; ++i) {
    if ((!vehicle_equals(vehicle, &state->vehicles[i])) && vehicle_contains_vehicle(vehicle, &state->vehicles[i])) {
      return false;
    }
  }

  return true;
}

State state_new(Vehicle vehicles[4], int rows, int cols, Vehicle exit) {
  return (State){.vehicles = vehicles, .rows = rows, .cols = cols, .exit = exit};
}

bool state_is_target(const State *state) { return point_equals(&state->vehicles[0].upper, &state->exit.upper); }

bool state_is_valid_operator(const State *state, Operator op) {
  const Vehicle *vehicle = &state->vehicles[vehicle_index_from_operator(op)];

  switch (op) {
    case UP_V0:
    case UP_V1:
    case UP_V2:
    case UP_V3:
      return is_valid_movement(vehicle, state, (Point){.x = -1, .y = 0});
    case DOWN_V0:
    case DOWN_V1:
    case DOWN_V2:
    case DOWN_V3:
      return is_valid_movement(vehicle, state, (Point){.x = 1, .y = 0});
    case LEFT_V0:
    case LEFT_V1:
    case LEFT_V2:
    case LEFT_V3:
      return is_valid_movement(vehicle, state, (Point){.x = 0, .y = -1});
    case RIGHT_V0:
    case RIGHT_V1:
    case RIGHT_V2:
    case RIGHT_V3:
      return is_valid_movement(vehicle, state, (Point){.x = 0, .y = 1});
    default:
      return false;
  }
}

bool state_equals(const State *rhs, const State *lhs) {
  if (rhs->cols != lhs->cols || lhs->rows != rhs->rows || !vehicle_equals(&rhs->exit, &lhs->exit)) {
    return false;
  }

  for (size_t i = 0; i < 4; ++i) {
    if (!vehicle_equals(&rhs->vehicles[i], &lhs->vehicles[i])) {
      return false;
    }
  }

  return true;
}

State *state_apply_operator(const State *current, Operator op) {
  State *next = (State *)malloc(sizeof(State));
  memcpy(next, current, sizeof(State));
  Vehicle *vehicle = &next->vehicles[vehicle_index_from_operator(op)];
  switch (op) {
    case UP_V0:
    case UP_V1:
    case UP_V2:
    case UP_V3:
      vehicle->upper.x -= 1;
      vehicle->down.x -= 1;
      break;
    case DOWN_V0:
    case DOWN_V1:
    case DOWN_V2:
    case DOWN_V3:
      vehicle->upper.x += 1;
      vehicle->down.x += 1;
      break;
    case LEFT_V0:
    case LEFT_V1:
    case LEFT_V2:
    case LEFT_V3:
      vehicle->upper.y -= 1;
      vehicle->down.y -= 1;
      break;
    case RIGHT_V0:
    case RIGHT_V1:
    case RIGHT_V2:
    case RIGHT_V3:
      vehicle->upper.y += 1;
      vehicle->down.y += 1;
      break;
  }
  return next;
}