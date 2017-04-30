int DSP_vecsumsq_c
(
    const short *x,
    int  count
)
{
    int i;
    int prod, sum = 0;
    for (i = 0; i < count; i++)
    {
        prod = x[i] * x[i];
        sum += prod;
    }
    return sum;
}

