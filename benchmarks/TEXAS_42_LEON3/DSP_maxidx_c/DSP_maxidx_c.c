int DSP_maxidx_c(const  short *x, int nx)
{
    int i, idx = 0;
    short max = -32768;
    for (i = 0; i < nx; i++)
        if (x[i] > max)
        {
            max = x[i];
            idx = i;
        }
    return idx;
}

