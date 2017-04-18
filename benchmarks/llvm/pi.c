/*--- pi.c       PROGRAM RANPI
 *
 *   Program to compute PI by probability.
 *   By Mark Riordan  24-DEC-1986; 
 *   Original version apparently by Don Shull.
 *   To be used as a CPU benchmark.
 *  
 *  Translated to C from FORTRAN 20 Nov 1993
 */
#include <stdio.h>

void myadd(float *sum,float *addend) {
/*
c   Simple adding subroutine thrown in to allow subroutine
c   calls/returns to be factored in as part of the benchmark.
*/
      *sum = *sum + *addend;
}

