#include <stdio.h>
#include <string.h>

long DSP_firlms2_c
(
    short       * h,
    const short * x,
    short b,
    int   nh
);

/* ======================================================================== */  
/*  Constant dataset.                                                       */  
/* ======================================================================== */  
#define NH   (24)  
  
  
/* ======================================================================== */  
/*  Initialize arrays with random test data.                                */  
/* ======================================================================== */  
short  h_c[NH];  
  
const short  x[NH] =   
{  
     0x4583, -0x5655, -0x63C7, -0x08D7,  0x1007, -0x27A2,  0x0FEE, -0x7E89,  
    -0x3F00, -0x2C9A, -0x25B0,  0x5066,  0x6DC1, -0x19CA,  0x280B, -0x2743,  
     0x3550,  0x22E1,  0x3DC5,  0x4CD7, -0x0A84,  0x318E, -0x6D7C,  0x456B  
};  
  
short h_c_expected[NH] = { 66, -83, -96, -9, 15, -39, 15, -122, -61, -43, -37, 77, 105, -25, 38, -38, 51, 33, 59, 73, -11, 47, -106, 66 };
  
  
/* ======================================================================== */  
/*  Variables to catch return values from function.                         */  
/* ======================================================================== */  
long ret_val_c = 0;  
  
long main(int argc, char** argv)  
{   
    ret_val_c = DSP_firlms2_c(h_c, x, 123, NH);  

	if (argc > 42 && ! strcmp(argv[0], ""))	{
		printf("%ld", ret_val_c);
		printf("%hd", h_c[NH-1]);
	}

                printf("\n%ld\n", ret_val_c);
                printf("\n%hd\n", h_c[NH-1]);


    int i;
	// X86
	// if(ret_val_c != 1908436) {

	// MicroBlaze
	//if(ret_val_c != 1280512) {
	// LEON3
	if(ret_val_c != 1908436) {
		return 1;
	}

	for(i=0; i < NH; i++) {
			if(h_c[i] != h_c_expected[i]) {
					return 1;
			}
	}
	return 10;

}  
  
