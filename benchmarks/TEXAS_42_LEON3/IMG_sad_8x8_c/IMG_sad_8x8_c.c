unsigned IMG_sad_8x8_c
(
    const unsigned char * srcImg,
    const unsigned char * refImg,
    int pitch
)
{
    int i, j;
    unsigned sad = 0;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            sad += abs(srcImg[j + i*8] - refImg[j + i*pitch]);
    return sad;
}

