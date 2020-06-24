#include "vehicle.h"

#include <string.h>

bool vehicle_equals(const Vehicle *lhs, const Vehicle *rhs) {
  return memcmp(lhs, rhs, sizeof(Vehicle)) == 0;
}