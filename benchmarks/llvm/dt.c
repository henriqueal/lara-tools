#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum {
  ITERATIONS = 131072,
  size = 2048
};

static inline void
double_array_divs_variable(double * __restrict dvec1,
                           double * __restrict dvec2){
  long i, j;
  for(j = 0; j < ITERATIONS; j++)
    for(i = 0; i < size; i++)
      dvec1[i] /= dvec2[i];
  
// Can use loop interchange to turn this into:
//  for(i = 0; i < size; i++) {
//    double tmp1 = dvec1[i];
//    double tmp2 = dvec2[i];
//    for(j = 0; j < ITERATIONS; j++)
//      tmp1 /= tmp2;
//    dvec1[i] = tmp1;
//  }

// Can then hoist 1/tmp2 out of the loop if -ffast-math is enabled.
}


