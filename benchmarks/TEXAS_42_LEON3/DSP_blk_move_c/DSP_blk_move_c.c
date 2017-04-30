void DSP_blk_move_c(short   *x, short *r, int nx)
{
    int i;
    if (r < x)
    {
        for (i = 0; i < nx; i++)
            r[i] = x[i];
    } else
    {
        for (i = nx-1 ; i >= 0; i--)
            r[i] = x[i];
    }
}

