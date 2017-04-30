void IMG_quantize_c
(
    short           * data,
    unsigned short  num_blks,
    unsigned short  blk_size,
    const short     * recip_tbl,
    int             q_pt
)
{
    short recip;
    int   quot;
    int   round;
    int   i, j, k;
    round = 1 << (q_pt - 1);
    if (!num_blks) return;
    for (i = 0; i < blk_size; i++)
    {
        recip   = recip_tbl[i];
        k       = i;
        for (j = 0; j < num_blks; j++)
        {
            quot    = data[k] * recip + round;
            data[k] = quot >> q_pt;
            k      += blk_size;
        }
    }
}

