void IMG_corr_gen_c
(
    const short * x,
    const short * h,
    short       * y,
    int                   m,
    int                   x_dim
)
{
    int i, j;
    for (j = 0; j < x_dim - m; j++)
    {
         for (i = 0; i < m; i++)
             y[j] += x[i + j] * h[i];
    }
}

