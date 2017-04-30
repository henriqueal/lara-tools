void DSP_mat_mul_c
(
    const short * x, int r1, int c1,
    const short * y,         int c2,
    short       * r,
    int                   qs
)
{
    int i, j, k;
    int sum;
    for (i = 0; i < r1; i++)
        for (j = 0; j < c2; j++)
        {
            sum = 0;
            for (k = 0; k < c1; k++)
                sum += x[k + i*c1] * y[j + k*c2];
            r[j + i*c2] = sum >> qs;
        }
}

