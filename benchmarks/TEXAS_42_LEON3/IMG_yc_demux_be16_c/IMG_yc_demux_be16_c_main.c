#include <stdio.h>
#include <string.h>

void IMG_yc_demux_be16_c
(
    int n,
    const unsigned char *yc,
    short * y,
    short * cr,
    short * cb
);

/* ======================================================================== */   
/*  IMGLIB function-specific alignments. Refer to the                       */   
/*  TMS320C64x IMG Library Programmer's Reference for details.              */   
/* ======================================================================== */   
#pragma DATA_ALIGN(yc, 8);   
#pragma DATA_ALIGN(y_c, 8);   
#pragma DATA_ALIGN(cr_c, 8);   
#pragma DATA_ALIGN(cb_c, 8);   
   
/* ======================================================================== */   
/*  Constant dataset.                                                       */   
/* ======================================================================== */   
#define N    (32)   
   
   
/* ======================================================================== */   
/*  Initialize arrays with random test data.                                */   
/* ======================================================================== */   
   
unsigned char yc[N*2] =    
{   
    0xF2, 0x8C, 0x24, 0xDA, 0x5F, 0x9B, 0xBE, 0x6A,   
    0xDF, 0x89, 0x5B, 0xFE, 0x7B, 0xEE, 0x23, 0x20,   
    0x65, 0xC4, 0x3B, 0xE7, 0x64, 0x81, 0x60, 0x69,   
    0xE3, 0x63, 0x5E, 0x96, 0x98, 0x5F, 0x74, 0x5E,   
    0xCB, 0xF0, 0x1E, 0xEF, 0xFB, 0x91, 0x2D, 0x49,   
    0xC5, 0x27, 0x28, 0xB3, 0x33, 0x9E, 0x49, 0x47,   
    0xC9, 0x13, 0x3A, 0x71, 0xEB, 0xF8, 0xBE, 0x47,   
    0x94, 0x66, 0x16, 0xF5, 0xBB, 0x72, 0x8C, 0x36   
};   
   

short  y_c[N];   
short  cr_c[N/2];   
short  cb_c[N/2];   

short  y_c_expected[N] = { 218, 140, 106, 155, 254, 137, 32, 238, 231, 196, 105, 129, 150, 99, 94, 95, 239, 240, 73, 145, 179, 39, 71, 158, 113, 19, 71, 248, 245, 102, 54, 114 }; 

short  cr_c_expected[N/2] = { 36, 190, 91, 35, 59, 96, 94, 116, 30, 45, 40, 73, 58, 190, 22, 140 }; 

short  cb_c_expected[N/2] = { 242, 95, 223, 123, 101, 100, 227, 152, 203, 251, 197, 51, 201, 235, 148, 187 };

int main(int argc, char** argv)   
{      

	IMG_yc_demux_be16_c(N, yc, y_c, cr_c, cb_c);   

	if (argc > 42 && ! strcmp(argv[0], ""))	{
		printf("%hd", y_c[N-1]);
		printf("%hd", cr_c[N/2-1]);
		printf("%hd", cb_c[N/2-1]);
	}

	int i;
	for(i=0; i < N; i++) {
			if(y_c[i] != y_c_expected[i]) {
					return 1;
			}
	}
	for(i=0; i < (N/2); i++) {
			if(cr_c[i] != cr_c_expected[i]) {
					return 1;
			}
	}
	for(i=0; i < (N/2); i++) {
			if(cb_c[i] != cb_c_expected[i]) {
					return 1;
			}
	}


    return 10;


}  
