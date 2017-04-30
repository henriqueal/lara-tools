void IMG_sobel_c
(
    const unsigned char * in,
    unsigned char       * out,
    short cols, short rows
)
{
    int H, O, V, i;
    int i00, i01, i02;
    int i10,      i12;
    int i20, i21, i22;
    int w = cols;
    for (i = 0; i < cols*(rows-2) - 2; i++)
    {
        i00=in[i    ]; i01=in[i    +1]; i02=in[i    +2];
        i10=in[i+  w];                  i12=in[i+  w+2];
        i20=in[i+2*w]; i21=in[i+2*w+1]; i22=in[i+2*w+2];
        H = -   i00 - 2*i01 -   i02 +
            +   i20 + 2*i21 +   i22;
        V = -   i00         +   i02
            - 2*i10         + 2*i12
            -   i20         +   i22;
        O = abs(H) + abs(V);
        if (O > 255) O = 255;
        out[i + 1] = O;
    }
}

