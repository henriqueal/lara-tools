
void IMG_ycbcr422p_rgb565_c
(
    const short              coeff[5],    
    const unsigned char     *y_data,     
    const unsigned char     *cb_data,    
    const unsigned char     *cr_data,    
    unsigned short 			*rgb_data,   
    unsigned                 num_pixels   
)
{
    int     i;                       
    int     y0, y1;                  
    int     cb, cr;                  
    int     y0t,y1t;                 
    int     rt, gt, bt;              
    int     r0, g0, b0;              
    int     r1, g1, b1;              
    int     r0t,g0t,b0t;             
    int     r1t,g1t,b1t;             
    int     r0s,g0s,b0s;             
    int     r1s,g1s,b1s;             
    short   luma = coeff[0];         
    short   r_cr = coeff[1];         
    short   g_cb = coeff[2];         
    short   g_cr = coeff[3];         
    short   b_cb = coeff[4];         
    unsigned short  rgb0, rgb1;      
    i = num_pixels >> 1;
    while (i-->0)
    {
        y0 = *y_data++  - 16;
        y1 = *y_data++  - 16;
        cb = *cb_data++ - 128;
        cr = *cr_data++ - 128;
        rt  = r_cr * (short)cr;
        gt  = g_cb * (short)cb + g_cr * (short)cr;
        bt  = b_cb * (short)cb;
        y0t = luma * (short)y0;
        y1t = luma * (short)y1;
        r0  = y0t + rt; r1 = y1t + rt;
        g0  = y0t + gt; g1 = y1t + gt;
        b0  = y0t + bt; b1 = y1t + bt;
        r0t = r0 >> 16;
        g0t = g0 >> 15;
        b0t = b0 >> 16;
        r1t = r1 >> 16;
        g1t = g1 >> 15;
        b1t = b1 >> 16;
        r0s = r0t < 0 ? 0 : r0t > 31 ? 31 : r0t;
        g0s = g0t < 0 ? 0 : g0t > 63 ? 63 : g0t;
        b0s = b0t < 0 ? 0 : b0t > 31 ? 31 : b0t;
        r1s = r1t < 0 ? 0 : r1t > 31 ? 31 : r1t;
        g1s = g1t < 0 ? 0 : g1t > 63 ? 63 : g1t;
        b1s = b1t < 0 ? 0 : b1t > 31 ? 31 : b1t;
        rgb0 = (r0s << 11) + (g0s <<  5) + (b0s <<  0);
        rgb1 = (r1s << 11) + (g1s <<  5) + (b1s <<  0);
        *rgb_data++ = rgb0;
        *rgb_data++ = rgb1;
    }
    return;
}

