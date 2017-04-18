void IMG_pix_sat_c
(
    int                     n,
    const short   * in_data,
    unsigned char * out_data
)
{
    int i, pixel;
    for (i = 0; i < n; i++)
    {
        pixel = in_data[i];
        if (pixel > 0xFF)
        {
            out_data[i] = 0xFF;
        } else if (pixel < 0x00)
        {
            out_data[i] = 0x00;
        } else
        {
            out_data[i] = pixel;
        }
    }
}

