#include <stdio.h>
#include <string.h>

short DSP_minval_c(const short *x, int nx);

/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define N    (64)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
const short  x[N] = 
{
    -0x00ED, -0x0014,  0x00CF, -0x0011,  0x00C9, -0x0379, -0x0173,  0x0384,
    -0x033B, -0x0127, -0x0132,  0x00B1, -0x039F, -0x0068,  0x01D7,  0x01A4,
     0x0287, -0x0004, -0x01E0,  0x0052,  0x00AC, -0x0127,  0x0295, -0x005B,
    -0x006D, -0x02F6,  0x01E5, -0x01D2,  0x02D5,  0x005A, -0x00E1,  0x02C2,
     0x00FF,  0x0393, -0x02FE, -0x018C,  0x010C,  0x018B,  0x018B, -0x02E2,
     0x01B6,  0x0032, -0x016C, -0x0137,  0x01BD, -0x01F2, -0x019C, -0x02AD,
    -0x00A5, -0x02D3, -0x0255,  0x0009, -0x01C0,  0x026F,  0x020A, -0x025C,
     0x02A0,  0x0141, -0x02F9, -0x01CE,  0x01DD,  0x03AC, -0x011E, -0x0343
};



/* ======================================================================== */
/*  Variables to catch return values from function.                         */
/* ======================================================================== */
short ret_val_c = 0;

int main(int argc, char** argv)  
{     
	ret_val_c = DSP_minval_c(x, N);  

	if (argc > 42 && ! strcmp(argv[0], ""))	printf("%hd", ret_val_c);

	short expected_value = -927;
	if(ret_val_c == expected_value) {
		return 10;
	}
	else {
		return 1;
	}
}  
