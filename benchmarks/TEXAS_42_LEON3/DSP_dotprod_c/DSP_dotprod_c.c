int DSP_dotprod_c(const short *x, const short *y, int nx)
{
    int sum = 0, i;
    for (i = 0; i < nx; i++)
        sum += x[i] * y[i];
    return sum;
}

