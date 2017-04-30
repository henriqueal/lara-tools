void IMG_mad_8x8_c
(
    const unsigned char * refImg,
    const unsigned char * srcImg,
    int pitch, int sx, int sy,
    unsigned int * motvec
)
{
    int i, j, x, y, matx, maty;
    unsigned matpos, matval;
    matval = ~0;
    matx   = maty = 0;
    for (x = 0; x < sx; x++)
        for (y = 0; y < sy; y++)
        {
            unsigned acc = 0;
            for (i = 0; i < 8; i++)
                for (j = 0; j < 8; j++)
                    acc += abs(srcImg[i*8 + j] - refImg[(i+y)*pitch + x + j]);
            if (acc < matval)
            {
                matval = acc;
                matx   = x;
                maty   = y;
            }
        }
    matpos    = (0xffff0000 & (matx << 16)) | (0x0000ffff & maty);
    motvec[0] = matpos;
    motvec[1] = matval;
}

