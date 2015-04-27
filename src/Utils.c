#include <stdlib.h>
#include <time.h>

#include "Utils.h"

void initRandom(void) {
  /* Set seed value based on time info for random generator */
  srand((unsigned int)time((time_t *)NULL));
}

int randomRange(int range) {
  return (rand() % range) + 1;
}

