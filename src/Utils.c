#include <stdlib.h>
#include <time.h>

#include "Utils.h"

void initrandom(void)
{
  /* Set seed value based on time info for random generator */
  srand((unsigned int)time((time_t *)NULL));
}

int random2(int range)
{
  return (rand() % range) + 1;
}

