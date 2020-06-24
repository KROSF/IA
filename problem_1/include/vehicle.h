#ifndef VEHICLE_H
#define VEHICLE_H

#include <stdbool.h>

#include "point.h"

typedef struct vehicle_t {
  Point upper;
  Point down;
} Vehicle;

bool vehicle_equals(const Vehicle *lhs, const Vehicle *rhs);

#endif