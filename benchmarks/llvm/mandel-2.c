#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

int max_i = 65536;

double sqr(double x) { return x*x; }

double cnorm2(complex z) { return sqr(creal(z)) + sqr(cimag(z)); }

int loop(complex c) {
    complex z=c;
    int i=1;
    while (cnorm2(z) <= 4.0 && i++ < max_i)
        z = z*z + c;
    return i;
}


