int IMG_perimeter_c
(
    const unsigned char * in,
    int cols,
    unsigned char       * out
)
{
    int i, count = 0;
    unsigned char pix_lft, pix_rgt, pix_top, pix_bot, pix_mid;
    for(i = 0; i < cols; i++)
    {
        pix_lft = in[i - 1];
        pix_mid = in[i + 0];
        pix_rgt = in[i + 1];
        pix_top = in[i - cols];
        pix_bot = in[i + cols];
        if (((pix_lft == 0) || (pix_rgt == 0) ||
             (pix_top == 0) || (pix_bot == 0)) && (pix_mid > 0))
        {
            out[i] = pix_mid;
            count++;
        } else
        {
            out[i] = 0;
        }
    }
    if (out[cols-1]) count--;
    if (out[0])      count--;
    out[0] = out[cols-1] = 0;
    return count;
}

