//  The Computer Language Shootout
//  http://shootout.alioth.debian.org/
//  contributed by Greg Buchholz
//
//  compile with:  -O3 -msse2 -lm

#include<math.h>
#include<stdio.h>

typedef double v2df __attribute__ ((vector_size (16)));

v2df make_vec(double a, double b)
{
    v2df v;
    double *tmp;
    tmp = (double *)&v; *(tmp) = a; *(tmp+1) = b;
    return v;
}

double sum_vec(v2df x)
{
    double *tmp = (double *)&x;
    return *(tmp) + *(tmp+1);
}


