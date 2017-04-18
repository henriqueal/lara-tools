short DSP_minval_c(const short *x, int nx)
{
    int i;
    short DSP_minval_c = 32767;
    for (i = 0; i < nx; i++)
        if (x[i] < DSP_minval_c)
            DSP_minval_c = x[i];
    return DSP_minval_c;
}

