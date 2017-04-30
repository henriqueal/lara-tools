#include <stdio.h>
#include <string.h>

int DSP_maxidx_c(const  short *x, int nx);

/* ======================================================================== */  
/*  DSPLIB function-specific alignments. Refer to the                       */  
/*  TMS320C64x DSP Library Programmer's Reference for details.              */  
/* ======================================================================== */  
#pragma DATA_ALIGN(x, 8);  
  
/* ======================================================================== */  
/*  Constant dataset.                                                       */  
/* ======================================================================== */  
#define NX   (64)  
  
  
/* ======================================================================== */  
/*  Initialize arrays with random test data.                                */  
/* ======================================================================== */  
const short  x[NX] =   
{  
    -0x31F2,  0x0C4B, -0x6C90,  0x66A8,  0x3AB8,  0x45C6,  0x7216,  0x52F2,  
    -0x6035, -0x7DD3,  0x7B3C, -0x3979, -0x7B93, -0x6BC1, -0x5B07,  0x7CF9,  
     0x6605,  0x6027, -0x3A7E,  0x548C, -0x27B3, -0x7502, -0x76BE, -0x4C19,  
    -0x0509,  0x0EE6,  0x60BF,  0x71D4, -0x37BF, -0x7567,  0x1D31,  0x7B5B,  
    -0x4DBC,  0x21DA, -0x0F54,  0x7AC2, -0x4C1A, -0x4D63,  0x19CF, -0x0BF2,  
     0x269B,  0x04A2,  0x65DD, -0x4914, -0x7BD8,  0x1DEC, -0x74F9,  0x552E,  
    -0x46FE,  0x4EEF,  0x2220, -0x0D52, -0x1AEE, -0x5705, -0x7338,  0x0630,  
    -0x72DB, -0x1038,  0x7510, -0x2363,  0x0762,  0x2384, -0x43E5,  0x337F  
};  
  
  
/* ======================================================================== */  
/*  Variables to catch return values from function.                         */  
/* ======================================================================== */  
int ret_val_c = 0;  
  
int main(int argc, char** argv)  
{     
 
    ret_val_c = DSP_maxidx_c(x, NX);  

    if (argc > 42 && ! strcmp(argv[0], ""))	printf("%d", ret_val_c);

    int expected_value = 15;
    if(ret_val_c == expected_value) {
        return 10;
    }
    else {
        return 1;
    }

}  
