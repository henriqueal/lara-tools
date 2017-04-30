/* -*- mode: c -*-
 * $Id: random.c 36673 2007-05-03 16:55:46Z laurov $
 * http://www.bagley.org/~doug/shootout/
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define inline static

#define IM 139968
#define IA 3877
#define IC 29573

inline double gen_random(double max) {
  static long last = 42;
    
  last = (last * IA + IC) % IM;
  return( max * last / IM );
}

