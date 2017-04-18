void DSP_mul32_c
(
    const int    *x,
    const int    *y,
    int * r,
    int           nx
)
{
    int i;
    for (i = 0; i < nx; i++)
    {
        short           a_hi, b_hi;
        unsigned short  a_lo, b_lo;
        int             hihi, lohi, hilo, hllh;
        a_hi = (short)(x[i] >> 16);
        b_hi = (short)(y[i] >> 16);
        a_lo = (unsigned short)x[i];
        b_lo = (unsigned short)y[i];
        hihi = a_hi * b_hi;
        hilo = a_hi * b_lo;
        lohi = a_lo * b_hi;
        hllh = (hilo + (long)lohi) >> 16;
        r[i] = hihi + hllh;
    }
}

