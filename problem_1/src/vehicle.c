#include "vehicle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool vehicle_equals(const Vehicle* lhs, const Vehicle* rhs) { return memcmp(lhs, rhs, sizeof(Vehicle)) == 0; }

int random_number(int min, int max) { return (rand() % (int)(((max) + 1) - (min))) + (min); }

Vehicle vehicle_random(int rows, int cols, Point down) {
  Vehicle v = {{0, 0}, {0, 0}};
  v.upper = (Point){.x = random_number(0, rows - 2), .y = random_number(0, cols - 2)};
  v.down = point_add(&v.upper, &down);
  return v;
}

void vehicle_display(FILE* stream, const Vehicle* vehicle) {
  fprintf(stream, "{ upper: ");
  point_display(stream, &vehicle->upper);
  fprintf(stream, ", down: ");
  point_display(stream, &vehicle->down);
  fprintf(stream, " }");
}

Vehicle vehicle_from_stdin(int rows, int cols, Point down) {
  Vehicle v = {{-1, -1}, {0, 0}};

  while (v.upper.x >= rows || v.upper.x < 0) {
    printf("Insert coodinate ( x ): ");
    scanf("%d", &v.upper.x);
  }

  while (v.upper.y >= cols || v.upper.y < 0) {
    printf("Insert coodinate ( y ): ");
    scanf("%d", &v.upper.y);
  }

  v.down = point_add(&v.upper, &down);
  return v;
}