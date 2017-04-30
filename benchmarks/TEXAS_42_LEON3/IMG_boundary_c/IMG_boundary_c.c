void IMG_boundary_c
(
    const unsigned char * i_data,
    int rows, int cols,
    int * o_coord,
    int * o_grey
)
{
    int x, y, p;
    for (y = 0; y < rows; y++)
        for (x = 0; x < cols; x++)
            if ((p = *i_data++) != 0)
            {
                *o_coord++ = ((y & 0xFFFF) << 16) | (x & 0xFFFF);
                *o_grey++  = p;
            }
}

