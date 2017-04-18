#include <stdio.h>
#include <stdlib.h>

double loop(float *x, float *y, long length) {
  long i;
  double accumulator = 0.0;
  for (i=0; i<length; ++i) {
    accumulator += (double)x[i] * (double)y[i];
  }
  return accumulator;
}

#ifdef SMALL_PROBLEM_SIZE
#define COUNT 100000
#else
#define COUNT 500000
#endif


