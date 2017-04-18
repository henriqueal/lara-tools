void IMG_conv_3x3_c(const unsigned char * inptr,
                 unsigned char       * outptr,
                 int                 x_dim,
                 const char          * mask,
                 int                 shift)
{
     const unsigned char     *IN1,*IN2,*IN3;
     unsigned char           *OUT;
     short    pix10,  pix20,  pix30;
     short    mask10, mask20, mask30;
     int      sum,    sum00,  sum11;
     int      i;
     int      sum22,  j;
     IN1      =   inptr;
     IN2      =   IN1 + x_dim;
     IN3      =   IN2 + x_dim;
     OUT      =   outptr;
     for (j = 0; j < x_dim ; j++)
     {
         sum = 0;
         for (i = 0; i < 3; i++)
         {
             pix10  =   IN1[i];
             pix20  =   IN2[i];
             pix30  =   IN3[i];
             mask10 =   mask[i];
             mask20 =   mask[i + 3];
             mask30 =   mask[i + 6];
             sum00  =   pix10 * mask10;
             sum11  =   pix20 * mask20;
             sum22  =   pix30 * mask30;
             sum   +=   sum00 + sum11+ sum22;
         }
         IN1++;
         IN2++;
         IN3++;
         sum = (sum >> shift);
         if ( sum <  0  )       sum = 0;
         if ( sum > 255 )       sum = 255;
         *OUT++   =       sum;
     }
}

