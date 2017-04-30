void IMG_wave_horz_c
(
    const short * i_data,
    const short * lp_filt,
    const short * hp_filt,
    short       * o_data,
    int                   x_dim
)
{
    int i, j;
    for (i = 0; i < x_dim; i += 2)
    {
        int lp_sum = 1 << 14;
        for (j = 0; j < 8; j++)
            lp_sum += i_data[(i + j) % x_dim] * lp_filt[j];
        o_data[i >> 1] = lp_sum >> 15;
    }
    for (i = 0; i < x_dim; i += 2)
    {
        int hp_sum = 1 << 14;
        for (j = 0; j < 8; j++)
            hp_sum += i_data[(i + x_dim - 6 + j) % x_dim] * hp_filt[7 - j];
        o_data[(i + x_dim) >> 1] = hp_sum >> 15;
    }
}

