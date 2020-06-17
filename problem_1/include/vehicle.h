#ifndef VEHICLE_H
#define VEHICLE_H
#include <stdbool.h>

typedef struct vehicle_t
{
  int upper_i;
  int upper_j;
  int bottom_i;
  int bottom_j;
} vehicle;

bool v_equals(vehicle *v, vehicle *w);

#endif