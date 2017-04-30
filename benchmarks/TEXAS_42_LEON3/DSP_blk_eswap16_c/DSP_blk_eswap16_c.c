void DSP_blk_eswap16_c
(
    void * src,
    void * dst,
    int  n_hwords
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
    for (i = 0; i < n_hwords; i++)
    {
        char t0, t1;
        t0 = _src[i*2 + 1];
        t1 = _src[i*2 + 0];
        _dst[i*2 + 0] = t0;
        _dst[i*2 + 1] = t1;
    }
}

