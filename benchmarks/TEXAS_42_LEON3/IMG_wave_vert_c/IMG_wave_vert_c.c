#define COLS (32)
#define LINS (8)

void IMG_wave_vert_c
(
    const short * in_data,   /* Array of row pointers */
    const short * lp_filt,   /* Low pass QMF filter   */
    const short * hp_filt,   /* High pass QMF filter  */
    short       * out_ldata, /* Low pass output data  */
    short       * out_hdata, /* High pass output data */
    int cols                     /* Length of rows to process */
)
{
    int   i, j;

    /* -------------------------------------------------------------------- */
    /*  First, perform the low-pass filter on the eight input rows.         */
    /* -------------------------------------------------------------------- */
    for (i = 0; i < cols; i++)
    {
        int sum = 1 << 14;
        for (j = 0; j < LINS; j++)
            sum += in_data[j*LINS+i] * lp_filt[j];

        out_ldata[i] = sum >> 15;
    }

    /* -------------------------------------------------------------------- */
    /*  Next, perform the high-pass filter on the same eight input rows.    */
    /* -------------------------------------------------------------------- */
    for (i = 0; i < cols; i++)
    {
        int sum = 1 << 14;
        for (j = 0; j < LINS; j++)
            sum += in_data[j*LINS+i] * hp_filt[7 - j];

        out_hdata[i] = sum >> 15;
    }
}

