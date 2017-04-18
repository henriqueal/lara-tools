void IMG_fdct_8x8_c(short *dct_data, unsigned num_fdcts)
{
    const unsigned short c1 = 0x1F62, c3 = 0x1A9B;       
    const unsigned short c5 = 0x11C7, c7 = 0x063E;       
    const unsigned short c2 = 0x29CF, c6 = 0x1151;       
    const unsigned short C1 = 0xFB15, C3 = 0xD4DB;       
    const unsigned short C5 = 0x8E3A, C7 = 0x31F1;       
    const unsigned short C2 = 0xA73D, C6 = 0x4546;       
    const unsigned short C4 = 0xB505;                    
    short f0, f1, f2, f3, f4, f5, f6, f7;    
    short g0, g1, h0, h1, p0, p1;            
    short r0, r1, r0_,r1_;                   
    short P0, P1, R0, R1;                    
    short g2, g3, h2, h3;                    
    short q1a,s1a,q0, q1, s0, s1;            
    short Q0, Q1, S0, S1;                    
    short F0, F1, F2, F3, F4, F5, F6, F7;    
    unsigned i, j;
    short (*dct)[8][8] = (short (*)[8][8])dct_data;
    if (!num_fdcts) return;
    for (i = 0; i < num_fdcts; i++)
    {
        for (j = 0; j < 8; j++)
        {
            f0 = dct[i][0][j];
            f1 = dct[i][1][j];
            f2 = dct[i][2][j];
            f3 = dct[i][3][j];
            f4 = dct[i][4][j];
            f5 = dct[i][5][j];
            f6 = dct[i][6][j];
            f7 = dct[i][7][j];
            g0 = f0 + f7;               g1 = f1 + f6;    
            h1 = f2 + f5;               h0 = f3 + f4;    
            g3 = f2 - f5;               g2 = f3 - f4;    
            h2 = f0 - f7;               h3 = f1 - f6;    
            p0 = g0 + h0;               r0 = g0 - h0;    
            p1 = g1 + h1;               r1 = g1 - h1;    
            q1a = g2 + g2;                               
            s1a = h2 + h2;                               
            q1  = (q1a * C4 + 0x8000) >> 16;             
            s1  = (s1a * C4 + 0x8000) >> 16;             
            s0 = h3 + g3;                                
            q0 = h3 - g3;                                
            P0 = p0 + p1;                                
            P1 = p0 - p1;                                
            r0_= r0 + r0;                                
            r1_= r1 + r1;                                
            R1 = (C6 * r1_+ C2 * r0_+ 0x8000) >> 16;     
            R0 = (C6 * r0_- C2 * r1_+ 0x8000) >> 16;     
            Q1 = q1 + q0;               Q0 = q1 - q0;
            S1 = s1 + s0;               S0 = s1 - s0;
            F0 = P0;                    F4 = P1;
            F2 = R1;                    F6 = R0;
            F1 = (C7 * Q1 + C1 * S1 + 0x8000) >> 16;     
            F7 = (C7 * S1 - C1 * Q1 + 0x8000) >> 16;     
            F5 = (C3 * Q0 + C5 * S0 + 0x8000) >> 16;     
            F3 = (C3 * S0 - C5 * Q0 + 0x8000) >> 16;     
            dct[i][0][j] = F0;
            dct[i][1][j] = F1;
            dct[i][2][j] = F2;
            dct[i][3][j] = F3;
            dct[i][4][j] = F4;
            dct[i][5][j] = F5;
            dct[i][6][j] = F6;
            dct[i][7][j] = F7;
        }
    }
    for (i = 0; i < num_fdcts; i++)
    {
        for (j = 0; j < 8; j++)
        {
            f0 = dct[i][j][0];
            f1 = dct[i][j][1];
            f2 = dct[i][j][2];
            f3 = dct[i][j][3];
            f4 = dct[i][j][4];
            f5 = dct[i][j][5];
            f6 = dct[i][j][6];
            f7 = dct[i][j][7];
            g0 = f0 + f7;               g1 = f1 + f6;    
            h1 = f2 + f5;               h0 = f3 + f4;    
            h2 = f0 - f7;               h3 = f1 - f6;    
            g3 = f2 - f5;               g2 = f3 - f4;    
            p0 = g0 + h0 + 4;           p1 = g1 + h1;    
            r0 = g0 - h0;               r1 = g1 - h1;    
            q1a= (g2 * C4 + 0x8000) >> 16;               
            s1a= (h2 * C4 + 0x8000) >> 16;               
            q1 = q1a + q1a;                              
            s1 = s1a + s1a;                              
            s0 = h3 + g3;                                
            q0 = h3 - g3;                                
            P0 = ((short)(p0 + p1)) >> 3;                
            P1 = ((short)(p0 - p1)) >> 3;                
            R1 = (c6 * r1 + c2 * r0 + 0x8000) >> 16;     
            R0 = (c6 * r0 - c2 * r1 + 0x8000) >> 16;     
            Q1 = q1 + q0;               Q0 = q1 - q0;    
            S1 = s1 + s0;               S0 = s1 - s0;    
            F0 = P0;                    F4 = P1;
            F2 = R1;                    F6 = R0;
            F1 = (c7 * Q1 + c1 * S1 + 0x8000) >> 16;     
            F7 = (c7 * S1 - c1 * Q1 + 0x8000) >> 16;     
            F5 = (c3 * Q0 + c5 * S0 + 0x8000) >> 16;     
            F3 = (c3 * S0 - c5 * Q0 + 0x8000) >> 16;     
            dct[i][j][0] = F0;
            dct[i][j][1] = F1;
            dct[i][j][2] = F2;
            dct[i][j][3] = F3;
            dct[i][j][4] = F4;
            dct[i][j][5] = F5;
            dct[i][j][6] = F6;
            dct[i][j][7] = F7;
        }
    }
    return;
}

