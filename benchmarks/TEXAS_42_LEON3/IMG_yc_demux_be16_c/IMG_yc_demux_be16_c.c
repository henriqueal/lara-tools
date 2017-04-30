void IMG_yc_demux_be16_c
(
    int n,
    const unsigned char *yc,
    short * y,
    short * cr,
    short * cb
)
{
    int i;
    for (i = 0; i < (n >> 1); i++)
    {
        y[2*i+0] = yc[4*i + 3];
        y[2*i+1] = yc[4*i + 1];
        cr[i]    = yc[4*i + 2];
        cb[i]    = yc[4*i + 0];
    }
}

