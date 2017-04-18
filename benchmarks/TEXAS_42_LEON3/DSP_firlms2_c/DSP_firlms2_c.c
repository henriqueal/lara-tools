long DSP_firlms2_c
(
    short       * h,
    const short * x,
    short b,
    int   nh
)
{
    int  i;
    long r = 0;
    for (i = 0; i < nh; i++)
    {
        h[i] += (x[i    ] * b) >> 15;
        r    +=  x[i + 1] * h[i];
    }
    return r;
}

