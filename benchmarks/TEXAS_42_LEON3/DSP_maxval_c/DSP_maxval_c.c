short DSP_maxval_c(const short *x, int nx)
{
    int i;
    short max = -32768;
    for (i = 0; i < nx; i++)
        if (x[i] > max)
            max = x[i];
    return max;
}

