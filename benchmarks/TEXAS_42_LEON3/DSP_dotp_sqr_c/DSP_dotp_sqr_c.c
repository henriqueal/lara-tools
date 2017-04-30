int DSP_dotp_sqr_c
(
    int G,
    const short  *x,
    const short  *y,
    int * r,
    int nx
)
{
    int i;
    for (i = 0; i < nx; i++)
    {
        *r += x[i] * y[i];
        G  += y[i] * y[i];
    }
    return G;
}

