void IMG_median_3x3_c
(
    const unsigned char * i_data,
    int n,
    unsigned char       * o_data
)
{
    unsigned char c0h, c1h, c2h, h_min;
    unsigned char c0m, c1m, c2m, m_mid;
    unsigned char c0l, c1l, c2l, l_max;
    unsigned char m_h, m_l, tmp, out;
    int i;
    c1h = c2h = c1m = c2m = c1l = c2l = 127;
    for (i = 0; i < n; i++)
    {
        c0h = c1h;    c1h = c2h;
        c0m = c1m;    c1m = c2m;
        c0l = c1l;    c1l = c2l;
        c2h = i_data[i      ];
        c2m = i_data[i +   n];
        c2l = i_data[i + 2*n];
        if (c2l > c2h) { tmp = c2l; c2l = c2h; c2h = tmp; }
        if (c2l > c2m) { tmp = c2l; c2l = c2m; c2m = tmp; }
        if (c2m > c2h) { tmp = c2m; c2m = c2h; c2h = tmp; }
        h_min = c2h;
        if (c1h < h_min) { h_min = c1h; }
        if (c0h < h_min) { h_min = c0h; }
        m_l   = c0m;
        m_mid = c1m;
        m_h   = c2m;
        if (m_l   > m_h  ) { tmp = m_l; m_l = m_h; m_h = tmp; }
        if (m_l   > m_mid) { m_mid = m_l; }
        if (m_mid > m_h  ) { m_mid = m_h; }
        l_max = c2l;
        if (c1l > l_max) { l_max = c1l; }
        if (c0l > l_max) { l_max = c0l; }
        out = m_mid;
        if (h_min > l_max) { tmp   = h_min; h_min = l_max; l_max = tmp; }
        if (h_min > out  ) { out   = h_min; }
        if (out   > l_max) { out   = l_max; }
        o_data[i] = out;
    }
}

