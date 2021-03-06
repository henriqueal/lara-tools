#include <stdio.h>
#include <string.h>

void IMG_fdct_8x8_c(short *dct_data, unsigned num_fdcts);

/* ======================================================================== */   
/*  IMGLIB function-specific alignments. Refer to the                       */   
/*  TMS320C64x IMG Library Programmer's Reference for details.              */   
/* ======================================================================== */   
#pragma DATA_ALIGN(fdct_data_c, 8);   
   
/* ======================================================================== */   
/*  Constant dataset.                                                       */   
/* ======================================================================== */   
#define num_fdcts    (6)   
   
   
/* ======================================================================== */   
/*  Initialize arrays with random test data.                                */   
/* ======================================================================== */   
short  fdct_data_c[384] =    
{   
    -0x4BE7, -0x1234,  0x3530,  0x532F, -0x4670, -0x410D, -0x2194,  0x2C41,   
     0x2838, -0x0005,  0x40D6,  0x7177, -0x01EA, -0x41E7,  0x638B, -0x2B78,   
     0x1FA2, -0x2BF1,  0x58B6,  0x400A, -0x6D8B,  0x09CC,  0x2E51, -0x451C,   
    -0x3465, -0x5E0C,  0x117A, -0x1B10, -0x3129, -0x199D, -0x6FDE,  0x4D8B,   
     0x1967, -0x7458,  0x13D2, -0x600B, -0x32CF,  0x7280,  0x5B63,  0x0D7E,   
    -0x39B6,  0x6393,  0x5954, -0x452B,  0x35F9, -0x3FE5, -0x1770, -0x4A1B,   
    -0x5352, -0x5E2D, -0x7970, -0x6161, -0x066F, -0x0713, -0x4D22, -0x6389,   
     0x08D3, -0x5D8B,  0x09E1,  0x287A,  0x27FB,  0x68CC,  0x4342,  0x012D,   
    -0x4362,  0x6DE9,  0x37C6, -0x18DF, -0x28B1, -0x7ADD,  0x0E7C,  0x1B40,   
     0x12CC,  0x4C67,  0x21CD, -0x5740,  0x5007,  0x59BF, -0x7899, -0x7796,   
    -0x3247, -0x4D2D, -0x0629, -0x5513, -0x6E2A, -0x5788,  0x5210, -0x12F3,   
    -0x0C9E, -0x476E,  0x0FE6, -0x1213, -0x79BB,  0x5EAD, -0x6A23, -0x2EEE,   
     0x1B28,  0x6653, -0x143C,  0x2898,  0x44AE, -0x6670, -0x7745,  0x3D03,   
    -0x6700, -0x53DF, -0x1175, -0x7E63, -0x0884, -0x72D0,  0x4066,  0x2509,   
     0x7479, -0x48C7, -0x1A87, -0x78BD,  0x13E6,  0x22B8,  0x30AA, -0x7FA6,   
    -0x6611, -0x54E5,  0x7098, -0x40EA, -0x01A5,  0x07F9,  0x6338, -0x4936,   
     0x75DC, -0x7B1E, -0x569C, -0x3486,  0x39F3,  0x2F4D,  0x777F,  0x451E,   
    -0x5F0E, -0x0582, -0x77F9,  0x5A7B, -0x52DE,  0x7327,  0x7A25,  0x7A08,   
     0x19FE, -0x2B48, -0x683D,  0x27B5, -0x1C36,  0x3625,  0x5EE4, -0x4765,   
     0x2743, -0x0232,  0x24CD, -0x6A44,  0x6176,  0x584A,  0x66F8,  0x1F6E,   
    -0x3EFB,  0x1178, -0x2CC4,  0x11EE, -0x50B7, -0x48E1,  0x10E1,  0x2A9C,   
     0x277D, -0x2F61, -0x765E, -0x24CA,  0x0AA3, -0x1724,  0x36CA, -0x58C3,   
     0x185D,  0x0B75,  0x0795, -0x351B,  0x251B,  0x6953, -0x1909,  0x79FF,   
    -0x1DBB,  0x44E5,  0x1BB8,  0x725D, -0x136E, -0x2DA8,  0x1863, -0x66FB,   
    -0x75B4,  0x0725,  0x40C0,  0x400F, -0x6C4A, -0x036D, -0x21E9,  0x4F57,   
    -0x0829, -0x5D0A, -0x4B56,  0x5AED,  0x0534,  0x2820, -0x2D15, -0x2B54,   
     0x2B81,  0x5FB4, -0x7C82,  0x7D3F,  0x0727,  0x6A2D, -0x7D0A,  0x678F,   
     0x69B7, -0x2370, -0x41FD, -0x588A,  0x5A32,  0x7FE1,  0x6888,  0x6D7D,   
     0x3A14,  0x7C5F,  0x2148,  0x108F,  0x62B0,  0x4719,  0x7E5C,  0x64CF,   
     0x3A2A,  0x105F, -0x3DC7, -0x1DC1, -0x1CEA, -0x35CD, -0x3565,  0x3200,   
    -0x5757,  0x2BCE, -0x16B0,  0x171C, -0x3B71, -0x6EF1,  0x7362, -0x06EC,   
    -0x36BC,  0x7BC4,  0x2304,  0x37D8, -0x33BD, -0x6878, -0x4F35, -0x573E,   
     0x53B6, -0x6F35, -0x4A3A, -0x237B, -0x45A0, -0x26D1, -0x4C30,  0x4B3C,   
     0x23AB,  0x52DA,  0x2158, -0x6D2A,  0x4374, -0x4E34,  0x010E, -0x519E,   
    -0x2AF5,  0x3EE8, -0x045D,  0x3659, -0x0D1F, -0x16D3, -0x0203, -0x1D88,   
    -0x26B1,  0x1102,  0x7A7E, -0x2874,  0x1592,  0x5027,  0x6B4C,  0x1775,   
     0x132D,  0x460B,  0x57B7,  0x0DE0,  0x722D,  0x222D,  0x69E4, -0x68A1,   
     0x25C8,  0x376E,  0x2A01, -0x1A3D, -0x3DE7,  0x59D8,  0x0B68, -0x26D4,   
    -0x04E0,  0x21F0,  0x42C4, -0x3E2A,  0x7DA0,  0x41D3,  0x0E62,  0x4123,   
     0x6512, -0x768A,  0x2D78,  0x13C0, -0x239F,  0x5319,  0x3DB4, -0x4743,   
     0x09A6, -0x1CF5,  0x5EBD,  0x4E18, -0x540C,  0x4C19,  0x1DBA,  0x1C90,   
     0x32D6,  0x44AC,  0x4A65,  0x5120, -0x3C82,  0x166F,  0x0728,  0x7AFC,   
    -0x65E1,  0x1E63,  0x109F,  0x6960, -0x14AA, -0x3904,  0x7FDC,  0x2ADD,   
    -0x597F, -0x1B02,  0x359E,  0x1648,  0x2490,  0x5DF7, -0x4F22,  0x15B6,   
     0x117E,  0x4156,  0x5668, -0x0389,  0x5D7F, -0x7AE7,  0x2112,  0x0A86,   
    -0x7536,  0x675A, -0x59F2, -0x2D79, -0x334F, -0x4689,  0x6DAF,  0x5A9F,   
     0x5417, -0x7AAF,  0x0B13, -0x5570,  0x550E, -0x5847, -0x7AFE, -0x0361,   
    -0x7789,  0x289A,  0x24B8, -0x73E0, -0x591E, -0x72B4,  0x41E6,  0x17FE   
};   

short fdct_data_c_expected[384] = { -2006, 1551, 5026, -3030, 3041, 150, 2746, -1572, -143, 175, -5292, 1793, 1322, -1028, 715, 2203, 2389, 416, -2053, -1038, 2955, 1440, -3276, -2748, 2314, -1619, -2497, 520, 2339, -4085, -1962, 1095, -517, 3002, -2222, 1896, -3523, 3347, 955, -2817, 3005, -2334, 3332, 1863, -1327, -933, 2022, 3408, -3962, 714, 5262, 122, 2523, 3584, -683, -2484, 1700, -1530, 6756, -437, 1836, 4481, -1379, -1610, 1717, -3657, -5211, 2721, -2409, 1499, 2046, 1407, 2259, -531, -4856, 1057, -3407, -744, 1189, -4210, -2482, -2661, 2525, -3611, 2810, 236, 5825, -925, 3732, 2402, 9, -708, 433, -4096, 4850, 1943, -428, 422, -172, 1512, -2649, -377, 5243, -1768, -2177, -2211, -2044, 1713, -4057, 635, -3927, -2771, -2854, 3527, 5426, -914, 645, 1690, -771, -1022, -3902, -951, 7386, 585, 484, -3315, -2809, -2430, -2223, -3230, -3140, -1692, -2066, -1334, -1701, -2833, 3449, -2417, 2007, 877, 829, 3945, 201, 3072, 2368, -4251, 80, 335, 2270, -3596, -6005, 1091, 532, 1940, -451, -2343, 3776, 452, 4155, 4064, -2619, -3132, -580, -4158, -598, -408, -1660, 3223, -960, 1362, -5533, -3861, -3444, 904, -1438, -2916, 2058, 3409, -1384, -916, -1928, -1496, -106, -891, 1707, -2948, 138, 3898, -3612, -1888, -1525, -3172, -3416, -2098, 2585, -1831, 3514, -539, 4747, -4321, -188, -3053, 1788, 2746, 467, -719, -1845, 2340, 1385, 2093, 514, 1499, 1026, -3003, 4686, -646, 439, 1266, 2137, 856, -301, 1159, -3008, 2950, 3306, -62, -6157, -2786, -1545, -324, 1269, 2257, 1633, 845, 1174, 2143, -539, -234, -1856, -3617, 2910, 2940, 4905, -3062, 3556, -2784, -1733, 4672, -1265, 3381, -4697, -2791, -1314, -2960, -2254, 2400, 2313, 2941, 3436, -4746, -2833, 1702, -512, 3569, -366, 2174, -822, 2612, 972, -2854, -3263, 1760, 3617, 1612, 5563, -4934, -3941, 587, -533, 1895, -2875, 4405, 2977, -2747, 2364, -2318, -31, -1526, 3340, -1074, -6759, 58, -1250, -4429, 1884, 2231, 3304, 673, 1340, 1193, -61, 391, 1731, 395, -3637, -2277, -2368, 4244, -3638, -523, -4953, 2268, 13, 3155, 2180, 2043, -3717, 1766, 6504, 2201, 2736, 4330, 5645, -3181, -1594, -2208, 1247, -2584, -3098, 853, -2032, -658, -1414, -514, -4983, 136, 2712, 411, 1963, 1947, 3128, -3083, 3702, 1081, 4021, -1128, -1402, 917, 3159, -1293, 2069, 3841, -1697, 950, 2952, -1658, -3444, -1899, 2, -1549, 2310, 154, -5213, 3250, 3143, 1400, -57, -2449, 3384, 3706, -6224, 569, 1573, 5139, 2039, 1451, 4086, 3638, -2894, -1263, -2803, 549, -2780, -3122 };   
   
int main(int argc, char** argv)   
{      
	IMG_fdct_8x8_c(fdct_data_c, num_fdcts);   

	if (argc > 42 && ! strcmp(argv[0], ""))	printf("%hd", fdct_data_c[384-1]);

	int i;
	for(i=0; i < 384; i++) {
			if(fdct_data_c[i] != fdct_data_c_expected[i]) {
					return 1;
			}
	}
	return 10;

}   
