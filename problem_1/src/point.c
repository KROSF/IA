#include "point.h"

#include <string.h>

bool point_equals(const Point* lhs, const Point* rhs) { return memcmp(lhs, rhs, sizeof(Point)) == 0; }

Point point_add(const Point* lhs, const Point* rhs) { return (Point){.x = lhs->x + rhs->x, .y = lhs->y + rhs->y}; }