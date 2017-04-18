unsigned IMG_sad_16x16_c
(
    const unsigned char * srcImg,
    const unsigned char * refImg,
    int pitch
)
{
    int i, j;
    unsigned sad = 0;
    for (i = 0; i < 16; i++)
        for (j = 0; j < 16; j++)
            sad += abs(srcImg[j + i*16] - refImg[j + i*pitch]);
    return sad;
}

