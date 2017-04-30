void DSP_blk_eswap32_c
(
    void * src,
    void * dst,
    int  n_words
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
    for (i = 0; i < n_words; i++)
    {
        char t0, t1, t2, t3;
        t0 = _src[i*4 + 3];
        t1 = _src[i*4 + 2];
        t2 = _src[i*4 + 1];
        t3 = _src[i*4 + 0];
        _dst[i*4 + 0] = t0;
        _dst[i*4 + 1] = t1;
        _dst[i*4 + 2] = t2;
        _dst[i*4 + 3] = t3;
    }
}

