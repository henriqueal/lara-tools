void DSP_w_vec_c
(
    const short * x,
    const short * y,
    short m,
    short * r,
    int nr
)
{
    int i;
    for (i = 0; i < nr; i++)
        r[i] = ((m * x[i]) >> 15) + y[i];
}

