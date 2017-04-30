void DSP_q15tofl_c( const short * x, float *r, int nx )
{
  int i;
    for (i=0;i<nx;i++)
        r[i]=(float)x[i]/32768;
}

