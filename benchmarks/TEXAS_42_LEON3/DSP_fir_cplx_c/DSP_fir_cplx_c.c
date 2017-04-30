void DSP_fir_cplx_c
(
    const short * x,
    const short * h,
    short * r,
    int nh,
    int nr
)
{
    short i,j;
    int imag, real;
    for (i = 0; i < 2*nr; i += 2)
    {
        imag = 0;
        real = 0;
        for (j = 0; j < 2*nh; j += 2)
        {
            real += h[j] * x[i-j]   - h[j+1] * x[i+1-j];
            imag += h[j] * x[i+1-j] + h[j+1] * x[i-j];
        }
        r[i] = (real >> 15);
        r[i+1] = (imag >> 15);
    }
}

