#ifndef BENCH_H
#define BENCH_H 1

#include <time.h>

/**
 * Get the current wall time.
 */
float wall(void);

/**
 * Get the current cpu time.
 */
float cpu(void);

float wall(void) { return (float)clock() / CLOCKS_PER_SEC; }

float cpu(void) { return (float)clock() / CLOCKS_PER_SEC; }

#endif
