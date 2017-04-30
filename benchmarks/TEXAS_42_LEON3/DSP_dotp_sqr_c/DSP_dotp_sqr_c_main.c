#include <stdio.h>
#include <string.h>

int DSP_dotp_sqr_c
(
    int G,
    const short  *x,
    const short  *y,
    int * r,
    int nx
);

/* ======================================================================== */  
/*  Constant dataset.                                                       */  
/* ======================================================================== */  
#define NX   (100)  
  
  
/* ======================================================================== */  
/*  Initialize arrays with random test data.                                */  
/* ======================================================================== */  
int g = -0x708B9B1D;  
  
const short  x[NX] =   
{  
    -0x69C1,  0x1A57, -0x5865, -0x63AA,  0x3A4C,  0x0333, -0x675A, -0x086F,  
     0x5121,  0x3D18,  0x1902, -0x1943, -0x5FF1, -0x1DDD, -0x2B5D, -0x196A,  
    -0x1BFD, -0x71F6,  0x7498, -0x656B, -0x49E7,  0x0320, -0x1B91, -0x1CF4,  
    -0x7E49,  0x2034, -0x2BB8,  0x610C,  0x3D2E,  0x0F9E,  0x1F8B, -0x7E1B,  
    -0x3D7C,  0x7FC4, -0x2E72, -0x06FA,  0x636A, -0x7979, -0x52A3, -0x69A4,  
     0x6954,  0x62DD,  0x7D56,  0x555E, -0x7FC7,  0x5DE0,  0x645E, -0x04C3,  
    -0x5DE3, -0x3C18, -0x36BD, -0x1EF6,  0x1D04,  0x793B,  0x1887,  0x74F1,  
    -0x428D, -0x0A37,  0x6F9F,  0x1EDA,  0x1E07, -0x4B2D,  0x184F, -0x1B05,  
    -0x476A, -0x030D,  0x0142, -0x68D8,  0x2F7C,  0x0CE7, -0x4AC9,  0x3002,  
    -0x274F, -0x24BB, -0x7CE9,  0x57AA, -0x3291,  0x5D9F,  0x5BCD, -0x3B40,  
    -0x2A27, -0x4A85, -0x02FC, -0x0DF6,  0x5090,  0x65EF,  0x2DE3,  0x0064,  
    -0x2BC6, -0x3C8E,  0x4B53, -0x7178,  0x7A3A,  0x30D7,  0x0AB9,  0x75F6,  
     0x757B, -0x5780, -0x0BFE,  0x2530  
};  
  
const short  y[NX] =   
{  
    -0x1B94,  0x05E0, -0x5D64,  0x366F, -0x3157, -0x7314, -0x164B, -0x495D,  
    -0x7F2D, -0x3A0D, -0x6E50,  0x3BD5, -0x00D4,  0x6AF9, -0x24A7,  0x1092,  
     0x2345,  0x5071,  0x6A6B,  0x40DD,  0x742A,  0x6EFA,  0x5102,  0x3529,  
    -0x5143, -0x31E9,  0x546C,  0x43D6, -0x7F81, -0x2551, -0x5A19, -0x673C,  
    -0x0CFD,  0x0C2B,  0x245B,  0x60A8,  0x4DCF, -0x1F90,  0x09D8, -0x50D7,  
    -0x06D6, -0x107D, -0x3A55,  0x71D9,  0x64A3,  0x15C8, -0x2FEC, -0x46AE,  
    -0x7C19, -0x3DC6,  0x761C, -0x64B8,  0x5261, -0x673A, -0x5927, -0x1F4E,  
     0x1F3C, -0x3ED3, -0x62D8, -0x5AA5, -0x1215, -0x2066, -0x4561,  0x4C62,  
     0x125B,  0x570A, -0x2477, -0x4D29, -0x33D5,  0x2125, -0x5F75,  0x1D4B,  
    -0x543D, -0x22AD, -0x497F, -0x197D,  0x784E, -0x5C51,  0x6729, -0x4423,  
     0x5E66,  0x4D97,  0x4977,  0x2301, -0x7478, -0x169F,  0x4B48,  0x5B2D,  
     0x0D8E,  0x0D23,  0x7C28,  0x15F7, -0x32C2, -0x72FC, -0x57A3,  0x20AF,  
    -0x6199,  0x7EAE, -0x5466, -0x7634  
};  
  
int  r_c = 0;  
  
  
  
/* ======================================================================== */  
/*  Variables to catch return values from function.                         */  
/* ======================================================================== */  
int ret_val_c = 0;  

int main(int argc, char** argv)  
{     
	ret_val_c = DSP_dotp_sqr_c(g, x, y, &r_c, NX);  

    if (argc > 42 && ! strcmp(argv[0], ""))	printf("%d", r_c);

	int expected_value = 1802068826;
	if(ret_val_c == expected_value) {
		return 10;
	}
	else {
		return 1;
	}
}  
