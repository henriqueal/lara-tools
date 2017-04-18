void IMG_pix_expand_c
(
    int n,
    const unsigned char * in_data,
    short               * out_data
)
{
    int i;
    for (i = 0; i < n; i++)
        out_data[i] =  in_data[i];
}

