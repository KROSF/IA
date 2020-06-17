#include "vehicle.h"

bool v_equals(vehicle *v, vehicle *w)
{
  return v->upper_i == w->upper_i && v->upper_j == w->upper_j && v->bottom_i == w->bottom_i && v->bottom_j == w->bottom_j;
}