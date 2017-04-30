void IMG_erode_bin_c
(
    const unsigned char * in_data,
    unsigned char       * out_data,
    const char          * mask,
    int cols
)
{
    int i;
    unsigned long p0l, p3l, p6l;
    unsigned p0, p1, p2, p3, p4, p5, p6, p7, p8, r;
    for (i = 0; i < cols; i += 4)
    {
        p0l = ((unsigned)     in_data[i +          0]      ) |
              ((unsigned)     in_data[i +          1] << 8 ) |
              ((unsigned)     in_data[i +          2] << 16) |
              ((unsigned)     in_data[i +          3] << 24) |
              ((unsigned long)in_data[i +          4] << 32);
        p3l = ((unsigned)     in_data[i + cols   + 0]      ) |
              ((unsigned)     in_data[i + cols   + 1] << 8 ) |
              ((unsigned)     in_data[i + cols   + 2] << 16) |
              ((unsigned)     in_data[i + cols   + 3] << 24) |
              ((unsigned long)in_data[i + cols   + 4] << 32);
        p6l = ((unsigned)     in_data[i + cols*2 + 0]      ) |
              ((unsigned)     in_data[i + cols*2 + 1] << 8 ) |
              ((unsigned)     in_data[i + cols*2 + 2] << 16) |
              ((unsigned)     in_data[i + cols*2 + 3] << 24) |
              ((unsigned long)in_data[i + cols*2 + 4] << 32);
        p0 = p0l;   p1 = p0l >> 1;   p2 = p0l >> 2;
        p3 = p3l;   p4 = p3l >> 1;   p5 = p3l >> 2;
        p6 = p6l;   p7 = p6l >> 1;   p8 = p6l >> 2;
        r = ~0;
        if (mask[0] >= 0) r &= p0;
        if (mask[1] >= 0) r &= p1;
        if (mask[2] >= 0) r &= p2;
        if (mask[3] >= 0) r &= p3;
        if (mask[4] >= 0) r &= p4;
        if (mask[5] >= 0) r &= p5;
        if (mask[6] >= 0) r &= p6;
        if (mask[7] >= 0) r &= p7;
        if (mask[8] >= 0) r &= p8;
        out_data[i + 0] = (r >>  0) & 0xFF;
        out_data[i + 1] = (r >>  8) & 0xFF;
        out_data[i + 2] = (r >> 16) & 0xFF;
        out_data[i + 3] = (r >> 24) & 0xFF;
    }
}

