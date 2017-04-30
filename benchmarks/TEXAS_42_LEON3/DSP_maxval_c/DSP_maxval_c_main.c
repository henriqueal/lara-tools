#include <stdio.h>
#include <string.h>

short DSP_maxval_c(const short *x, int nx);

/* ======================================================================== */  
/*  Constant dataset.                                                       */  
/* ======================================================================== */  
#define N    (64)  
  
  
/* ======================================================================== */  
/*  Initialize arrays with random test data.                                */  
/* ======================================================================== */  
const short  x[N] =   
{  
    -0x013B, -0x004F,  0x031C,  0x0344,  0x00C0,  0x0028,  0x012B, -0x0035,  
     0x000C,  0x00C6, -0x0321,  0x0043,  0x0335, -0x01AF, -0x00AF, -0x03BD,  
     0x00E0, -0x0242, -0x00C9,  0x0295,  0x0103, -0x024C, -0x0188, -0x015E,  
     0x0128, -0x01CD,  0x0277,  0x020D, -0x01DE, -0x00CF,  0x037B, -0x00E1,  
     0x03B1,  0x03C6, -0x037F, -0x0331, -0x013C,  0x02F4, -0x0067,  0x009A,  
     0x02D3,  0x0028, -0x0260,  0x0015, -0x0303,  0x00F1, -0x0205,  0x035F,  
    -0x0349,  0x027F, -0x0241,  0x0198,  0x02F4, -0x0195, -0x0206, -0x0137,  
    -0x02F3, -0x0194, -0x03A9, -0x00D4, -0x0298,  0x0221, -0x0357, -0x0070  
};  
  
  
  
/* ======================================================================== */  
/*  Variables to catch return values from function.                         */  
/* ======================================================================== */  
short ret_val_c = 0;  
  
int main(int argc, char** argv)  
{     
	ret_val_c = DSP_maxval_c(x, N);  

	if (argc > 42 && ! strcmp(argv[0], ""))	printf("%hd", ret_val_c);

	int expected_value = 966;
	if(ret_val_c == expected_value) {
		return 10;
	}
	else {
		return 1;
	}

}  
