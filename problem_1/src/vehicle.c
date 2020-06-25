#include "vehicle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool vehicle_equals(const Vehicle* lhs, const Vehicle* rhs) { return memcmp(lhs, rhs, sizeof(Vehicle)) == 0; }

static int random_number(int min, int max) { return (arc4random() % (int)(((max) + 1) - (min))) + (min); }

Vehicle vehicle_random(int rows, int cols) {
  return (Vehicle){
      .upper = {.x = random_number(0, rows), .y = random_number(0, cols)},
      .down = {.x = random_number(0, rows), .y = random_number(0, cols)},
  };
}

void vehicle_display(FILE* stream, const Vehicle* vehicle) {
  fprintf(stream, "{ upper: ");
  point_display(stream, &vehicle->upper);
  fprintf(stream, ", down: ");
  point_display(stream, &vehicle->down);
  fprintf(stream, " }");
}

Vehicle vehicle_from_stdin(Point down) {
  Vehicle v = {{0, 0}, {0, 0}};
  printf("Insert coodinate ( x ): ");
  scanf("%d", &v.upper.x);
  printf("Insert coodinate ( y ): ");
  scanf("%d", &v.upper.y);
  v.down = point_add(&v.upper, &down);
  return v;
}