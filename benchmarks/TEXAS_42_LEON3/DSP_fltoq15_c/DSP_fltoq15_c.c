void DSP_fltoq15_c
(
    const float * x,
    short       * r,
    int         nx
)
{
    int i, a;
    for(i = 0; i < nx; i++)
    {
        a = (int) (32768 * x[i]) / 1;
        if (a>32767)  a =  32767;
        if (a<-32768) a = -32768;
        r[i] = (short) a;
    }
}

