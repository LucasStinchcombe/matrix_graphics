#include "conway.h"

#define BELOW_POS(pos) ((pos + (MATRIX_SIZE - 1)) % MATRIX_SIZE)
#define ABOVE_POS(pos) ((pos + 1) % MATRIX_SIZE)

static uint16_t next[MATRIX_SIZE];

void next_iter()
{
  int i, j, count;

  for (i = 0; i != MATRIX_SIZE; ++i)
  {
    for (j = 0; j != MATRIX_SIZE; ++j)
    {
      count = 0;

      if (matrix[i] & 1 << BELOW_POS(j))
      {
        ++count;
      }
      if (matrix[i] & 1 << ABOVE_POS(j))
      {
        ++count;
      }
      if (matrix[BELOW_POS(i)] & 1 << j)
      {
        ++count;
      }
      if (matrix[ABOVE_POS(i)] & 1 << j)
      {
        ++count;
      }
      if (matrix[BELOW_POS(i)] & 1 << BELOW_POS(j))
      {
        ++count;
      }
      if (matrix[BELOW_POS(i)] & 1 << ABOVE_POS(j))
      {
        ++count;
      }
      if (matrix[ABOVE_POS(i)] & 1 << BELOW_POS(j))
      {
        ++count;
      }
      if (matrix[ABOVE_POS(i)] & 1 << ABOVE_POS(j))
      {
        ++count;
      }

      // if alive
      if (matrix[i] & 1 << j)
      {
        if (count < 2 || count > 3)
        {
          next[i] &= ~(1 << j);
        }
        else
        {
          next[i] |= 1 << j;
        }
      }
      else if (count == 3)
      {
        next[i] |= 1 << j;
      }
      else
      {
        next[i] &= ~(1 << j);
      }
    }
  }

  // copy new matrix
  for (i = 0; i != MATRIX_SIZE; ++i)
  {
    matrix[i] = next[i];
  }
}
