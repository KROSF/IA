#include <stdlib.h>
#include "state_t.h"

state_t new_state(vehicle *vehicles, size_t rows, size_t cols)
{
  state_t state = {
      .rows = rows,
      .cols = cols,
      .matrix = malloc(rows * cols * sizeof(size_t)),
  };

  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      *(state.matrix + i * cols + j) = *(matrix + i * cols + j);
    }
  }

  return state;
}