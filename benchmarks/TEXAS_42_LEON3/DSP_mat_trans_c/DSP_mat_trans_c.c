void DSP_mat_trans_c(const short * x, short rows, short columns,
                  short * r)
{
    int i, j;
    for (i = 0; i < columns; i++)
        for (j = 0; j < rows; j++)
            r[i*rows + j] = x[j*columns + i];
}

