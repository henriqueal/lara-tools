void DSP_blk_eswap64_c
(
    void *src,
    void *dst,
    int  n_dbls
)
{
    int i;
    char *_src, *_dst;
    if (dst)
    {
        _src = (char *)src;
        _dst = (char *)dst;
    } else
    {
        _src = (char *)src;
        _dst = (char *)src;
    }
    for (i = 0; i < n_dbls; i++)
    {
        char t0, t1, t2, t3, t4, t5, t6, t7;
        t0 = _src[i*8 + 7];
        t1 = _src[i*8 + 6];
        t2 = _src[i*8 + 5];
        t3 = _src[i*8 + 4];
        t4 = _src[i*8 + 3];
        t5 = _src[i*8 + 2];
        t6 = _src[i*8 + 1];
        t7 = _src[i*8 + 0];
        _dst[i*8 + 0] = t0;
        _dst[i*8 + 1] = t1;
        _dst[i*8 + 2] = t2;
        _dst[i*8 + 3] = t3;
        _dst[i*8 + 4] = t4;
        _dst[i*8 + 5] = t5;
        _dst[i*8 + 6] = t6;
        _dst[i*8 + 7] = t7;
    }
}

