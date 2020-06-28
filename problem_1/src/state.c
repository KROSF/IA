#include "state.h"

#include <stdlib.h>
#include <string.h>

#include "colors.h"
#include "log.h"

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
    default:
      exit(1);
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
  if (next.upper.x < 0 || next.down.x > state->rows - 1 || next.upper.y < 0 || next.down.y > state->cols - 1) {
    return false;
  }

  for (size_t i = 0; i < 4; ++i) {
    if ((!vehicle_equals(vehicle, &state->vehicles[i])) && vehicle_contains_vehicle(&next, &state->vehicles[i])) {
      return false;
    }
  }

  return true;
}

State state_new(Vehicle vehicles[4], int rows, int cols, Vehicle exit) {
  return (State){
      .vehicles = {vehicles[0], vehicles[1], vehicles[2], vehicles[3]}, .rows = rows, .cols = cols, .exit = exit};
}

bool state_is_target(const State *state) { return point_equals(&state->vehicles[0].down, &state->exit.down); }

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
    default:
      exit(1);
  }
  return next;
}

State state_random();
State state_from_stdin() {
  int rows = 0;
  int cols = 0;
  int exit_col = 0;
  Vehicle vehicles[4] = {};
  printf("Insert number of rows: ");
  scanf("%d", &rows);
  printf("Insert number of cols: ");
  scanf("%d", &cols);
  printf("Insert col of exit: ");
  scanf("%d", &exit_col);
  printf("Insert coordinates for vehicle V0 [2x2] (the one who reaches the exit)\n");
  vehicles[0] = vehicle_from_stdin((Point){1, 1});
  printf("Insert coordinates for vehicle V1\n");
  vehicles[1] = vehicle_from_stdin((Point){1, 0});
  printf("Insert coordinates for vehicle V2\n");
  vehicles[2] = vehicle_from_stdin((Point){0, 1});
  printf("Insert coordinates for vehicle V3\n");
  vehicles[3] = vehicle_from_stdin((Point){0, 0});
  return state_new(vehicles, rows, cols,
                   (Vehicle){.upper = {.x = rows - 1, .y = exit_col}, .down = {.x = rows - 1, .y = exit_col + 1}});
}

static char *vehicle_symbol(size_t index) {
  switch (index) {
    case 0:
      return RED "█ " NORMAL;
    case 1:
      return MAGENTA "█ " NORMAL;
    case 2:
      return BLUE "█ " NORMAL;
    case 3:
      return CYAN "█ " NORMAL;

    default:
      return "█ ";
  }
}

void state_display(FILE *stream, const State *state) {
  char *color;
  const Vehicle *vehicle;
  char *grid[state->rows][state->cols];

  for (size_t i = 0; i < state->rows; ++i) {
    for (size_t j = 0; j < state->cols; ++j) {
      grid[i][j] = "█ ";
    }
  }

  for (size_t i = 0; i < 4; ++i) {
    vehicle = &state->vehicles[i];
    color = vehicle_symbol(i);
    grid[vehicle->upper.x][vehicle->down.y] = color;
    grid[vehicle->down.x][vehicle->upper.y] = color;
    grid[vehicle->upper.x][vehicle->upper.y] = color;
    grid[vehicle->down.x][vehicle->down.y] = color;
  }

  vehicle = &state->exit;
  grid[vehicle->upper.x][vehicle->down.y] = GREEN "█ " NORMAL;
  grid[vehicle->down.x][vehicle->upper.y] = GREEN "█ " NORMAL;
  grid[vehicle->upper.x][vehicle->upper.y] = GREEN "█ " NORMAL;
  grid[vehicle->down.x][vehicle->down.y] = GREEN "█ " NORMAL;

  fprintf(stream, "   ");
  for (size_t i = 0; i < state->cols; ++i) {
    fprintf(stream, "%zu ", i);
  }
  fprintf(stream, "\n");

  for (size_t i = 0; i < state->rows; ++i) {
    fprintf(stream, "%2zu ", i);
    for (size_t j = 0; j < state->cols; ++j) {
      fprintf(stream, "%s", grid[i][j]);
    }
    fprintf(stream, "\n");
  }
}