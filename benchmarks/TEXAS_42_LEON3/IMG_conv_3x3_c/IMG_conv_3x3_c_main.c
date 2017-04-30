#include <stdio.h>
#include <string.h>

void IMG_conv_3x3_c(const unsigned char * inptr,
                 unsigned char       * outptr,
                 int                 x_dim,
                 const char          * mask,
                 int                 shift);

/* ======================================================================== */   
/*  Constant dataset.                                                       */   
/* ======================================================================== */   
#define COLS (256)   
#define N    (COLS*3)   
   
/* ======================================================================== */   
/*  Initialize arrays with random test data.                                */   
/* ======================================================================== */   
const unsigned char  in_data[N] =    
{   
     0x04,  0xEC,  0xA4,  0xE9,  0x64,  0x4E,  0x57,  0x6F,   
     0x2F,  0x1F,  0x77,  0xA3,  0x78,  0xF5,  0x74,  0x5B,   
     0x17,  0x72,  0x81,  0xF9,  0xAA,  0xBC,  0x04,  0xFF,   
     0x94,  0x6A,  0xBB,  0x8A,  0x0A,  0xF0,  0xDA,  0x19,   
     0x5C,  0x67,  0x7B,  0xFF,  0x2F,  0xB8,  0x58,  0x15,   
     0x9E,  0xC9,  0x80,  0xA2,  0x09,  0x17,  0xBD,  0x69,   
     0xD6,  0x55,  0x0B,  0x19,  0xA8,  0xF8,  0x0D,  0x18,   
     0x9C,  0xD9,  0xCE,  0x64,  0x17,  0x21,  0x40,  0x25,   
     0x73,  0x56,  0xCA,  0xC5,  0x4D,  0x21,  0x65,  0xD1,   
     0x08,  0x09,  0xEF,  0xEF,  0x62,  0xA4,  0x06,  0x2A,   
     0xD6,  0xB1,  0x4D,  0xEA,  0x15,  0x7F,  0x9C,  0xDC,   
     0x76,  0x7A,  0xD0,  0x00,  0x15,  0x0B,  0x26,  0x2A,   
     0x71,  0xA6,  0x2C,  0x65,  0x3E,  0x0E,  0x09,  0xC1,   
     0xF5,  0xFB,  0x3D,  0x8D,  0x8C,  0x90,  0x1A,  0x3D,   
     0x57,  0x71,  0x6A,  0xDB,  0x5E,  0x5C,  0x6D,  0x74,   
     0xCA,  0x60,  0xCE,  0xC7,  0x20,  0xFE,  0xD6,  0x07,   
     0x83,  0xC1,  0xAA,  0xB6,  0x7B,  0x21,  0x2A,  0x2C,   
     0xE9,  0x81,  0x91,  0x92,  0xB3,  0x25,  0x65,  0x95,   
     0x5E,  0x33,  0xE1,  0x6E,  0xDD,  0xA2,  0x69,  0xDC,   
     0xA3,  0x98,  0xC1,  0xCE,  0x4B,  0x41,  0xAD,  0x50,   
     0xCC,  0x8B,  0x78,  0xA8,  0x93,  0x2E,  0x74,  0xC1,   
     0x60,  0xDE,  0x25,  0xE2,  0x51,  0xB4,  0x34,  0x9A,   
     0x11,  0xB4,  0x19,  0xB3,  0xEA,  0x56,  0xB4,  0xCC,   
     0x61,  0x83,  0xD9,  0x77,  0x59,  0xE8,  0x11,  0xFB,   
     0x44,  0xD6,  0x7F,  0x71,  0x47,  0xA2,  0x2D,  0xDA,   
     0xDE,  0x72,  0x9E,  0x52,  0x81,  0x2A,  0x6B,  0xF9,   
     0x39,  0xF1,  0x12,  0xC4,  0x25,  0xEC,  0x61,  0xFF,   
     0x00,  0x87,  0xFF,  0xB3,  0xC8,  0xD1,  0x18,  0xF5,   
     0x02,  0xD7,  0x3D,  0xF6,  0x28,  0xA9,  0xE9,  0x5C,   
     0x8A,  0x08,  0xD5,  0xAD,  0xEF,  0x12,  0x4F,  0xAA,   
     0x77,  0x81,  0x9A,  0xC6,  0x82,  0xBD,  0x47,  0x43,   
     0x2A,  0xA4,  0x09,  0x61,  0xC0,  0x45,  0x84,  0x31,   
     0x73,  0x04,  0x84,  0x01,  0x28,  0xA4,  0xA3,  0xA0,   
     0xD4,  0x41,  0x98,  0x0F,  0xDC,  0x7F,  0xCC,  0xA1,   
     0x9E,  0xAB,  0xA3,  0xE6,  0x87,  0x17,  0x85,  0xE2,   
     0x92,  0x55,  0x2A,  0x56,  0x57,  0xCC,  0x7A,  0xA6,   
     0x03,  0xFD,  0x7E,  0xA9,  0xB5,  0x69,  0xC1,  0xF0,   
     0xAC,  0x98,  0xE0,  0x31,  0xCB,  0x62,  0xBF,  0xB5,   
     0xC4,  0xB3,  0x28,  0xD9,  0x58,  0x4C,  0x20,  0xD0,   
     0x20,  0x4F,  0x0B,  0x7C,  0xB9,  0xA1,  0x85,  0xB6,   
     0xAC,  0xE2,  0x93,  0x87,  0xC2,  0xC1,  0x77,  0x15,   
     0xBF,  0x7A,  0xFC,  0x0A,  0x43,  0xBF,  0xCF,  0x35,   
     0x75,  0xE0,  0x29,  0x60,  0xED,  0x4C,  0x49,  0x39,   
     0x6B,  0x9E,  0x25,  0x9D,  0xAC,  0x57,  0x57,  0x92,   
     0xF7,  0xA6,  0xA0,  0x28,  0x5C,  0xC0,  0x11,  0x78,   
     0x4B,  0x03,  0x30,  0x52,  0x2D,  0x5C,  0x3B,  0xAE,   
     0x9F,  0xBA,  0x3E,  0x44,  0x15,  0x46,  0xD0,  0xD2,   
     0xFA,  0x93,  0xCB,  0x43,  0xEF,  0x1D,  0xD8,  0x09,   
     0xE7,  0xDC,  0xFE,  0x3C,  0x2F,  0x56,  0x9F,  0x4B,   
     0xF6,  0xC1,  0x4A,  0x70,  0x59,  0x47,  0x41,  0x65,   
     0xA1,  0x05,  0x3B,  0x60,  0xAC,  0xD9,  0x2E,  0x84,   
     0xDB,  0x0F,  0x66,  0x45,  0xF4,  0x32,  0xEC,  0x46,   
     0x54,  0x78,  0xE6,  0x0C,  0x94,  0xB1,  0x8F,  0x51,   
     0x38,  0x26,  0xAB,  0x3B,  0x92,  0xCF,  0x75,  0xFD,   
     0x0A,  0xEE,  0x68,  0x1F,  0x94,  0x47,  0xBE,  0xE4,   
     0xFE,  0xA5,  0x6C,  0x6C,  0x7D,  0x05,  0x92,  0x02,   
     0x30,  0x14,  0xA6,  0xAE,  0x90,  0xEC,  0xA3,  0xAB,   
     0xD4,  0x00,  0x46,  0x25,  0xDB,  0x67,  0xAE,  0xD5,   
     0x88,  0xFA,  0xD8,  0x06,  0xE5,  0x32,  0x9D,  0x00,   
     0xE2,  0x1C,  0x88,  0xBE,  0x90,  0x76,  0xB3,  0xA9,   
     0x3A,  0x1F,  0x2A,  0x7D,  0x58,  0x7B,  0xCC,  0x3F,   
     0xD2,  0x95,  0x12,  0x48,  0x41,  0xEC,  0xF0,  0x8F,   
     0x82,  0x27,  0x47,  0xB7,  0xE1,  0x67,  0xA2,  0xF6,   
     0x10,  0xBE,  0x77,  0xE5,  0x4C,  0xC1,  0x43,  0xE9,   
     0x9E,  0x90,  0x5A,  0x4A,  0xD3,  0xEB,  0x72,  0x26,   
     0x99,  0xD6,  0x77,  0xCA,  0xD0,  0xD8,  0xD8,  0x4E,   
     0xDC,  0xC7,  0x17,  0xF7,  0x1E,  0x2A,  0x0B,  0xE1,   
     0xDE,  0x0A,  0x1E,  0x40,  0x1B,  0x9A,  0x27,  0x3B,   
     0x04,  0x90,  0xD4,  0xD8,  0x91,  0x65,  0x97,  0xB4,   
     0x83,  0x29,  0x25,  0x30,  0x20,  0xDF,  0x16,  0x23,   
     0x6E,  0x97,  0xDD,  0x3B,  0x72,  0x93,  0x43,  0x9C,   
     0x04,  0x3A,  0x4F,  0x0A,  0xBD,  0xEB,  0x58,  0xD4,   
     0x8A,  0x9A,  0x6E,  0x13,  0xC7,  0x7C,  0x6B,  0x8F,   
     0x8B,  0x4A,  0xED,  0x07,  0x02,  0x6F,  0x67,  0x2A,   
     0xA3,  0x8C,  0x08,  0x2C,  0x1D,  0x6D,  0x54,  0xC6,   
     0x7C,  0x24,  0xC7,  0x2A,  0xB4,  0xBA,  0xD1,  0x90,   
     0x28,  0x96,  0x19,  0x8B,  0xC2,  0xC7,  0xB4,  0x52,   
     0x83,  0xCE,  0x04,  0x71,  0xC8,  0xA1,  0x91,  0xD8,   
     0xC6,  0xDD,  0x18,  0xB3,  0xA6,  0x25,  0x7A,  0xAB,   
     0x2D,  0xF6,  0xE1,  0x20,  0x8B,  0xBE,  0xC3,  0x47,   
     0x0A,  0x6E,  0x95,  0xAB,  0x5F,  0xBC,  0xAF,  0x48,   
     0x55,  0xB5,  0x43,  0x16,  0xAE,  0x0D,  0xE9,  0xFE,   
     0x7D,  0xBE,  0xEA,  0x04,  0x07,  0x3B,  0x5C,  0x6D,   
     0xE8,  0x44,  0x7C,  0x96,  0x7B,  0x15,  0x88,  0x13,   
     0x4C,  0x97,  0x75,  0x3A,  0xF5,  0x5B,  0xC4,  0xB3,   
     0xD7,  0x98,  0xD4,  0xF4,  0xD9,  0x0B,  0xDD,  0xF7,   
     0xF5,  0x5F,  0x9C,  0x2C,  0x80,  0xC4,  0x6B,  0x09,   
     0x2E,  0xF5,  0x98,  0x0E,  0xED,  0xB0,  0xE2,  0x0F,   
     0xA9,  0x1C,  0xFF,  0x91,  0x47,  0x20,  0xAD,  0x25,   
     0xA7,  0xF3,  0xDE,  0x8B,  0x7B,  0xD8,  0xFF,  0x8C,   
     0x30,  0x9B,  0x89,  0x99,  0xBC,  0x69,  0xE8,  0xA8,   
     0x40,  0x89,  0x27,  0x35,  0x59,  0xD4,  0xFB,  0xFB,   
     0x9B,  0x99,  0x60,  0x1F,  0xE9,  0xC0,  0x77,  0x6D,   
     0x94,  0x09,  0x9C,  0xF8,  0x8E,  0x2A,  0x1E,  0x05,   
     0x0C,  0xE2,  0xCE,  0x2D,  0xA3,  0x7D,  0x07,  0xC3,   
     0x08,  0x36,  0x91,  0x56,  0xFF,  0x5B,  0xA6,  0x5E   
   
};   
   
unsigned char  out_data_c[COLS];   

unsigned char  out_data_c_expected[COLS] = { 105, 108, 95, 108, 137, 135, 130, 130, 119, 115, 131, 165, 183, 167, 142, 141, 146, 160, 178, 135, 81, 110, 175, 158, 95, 78, 78, 99, 144, 138, 89, 85, 137, 171, 172, 150, 135, 151, 163, 155, 146, 130, 104, 102, 120, 133, 144, 158, 138, 108, 112, 123, 106, 89, 97, 92, 87, 87, 100, 132, 136, 127, 140, 156, 161, 149, 140, 147, 137, 114, 110, 111, 135, 159, 109, 86, 129, 118, 94, 136, 144, 98, 101, 119, 105, 105, 119, 119, 117, 112, 108, 113, 106, 105, 126, 151, 145, 109, 91, 112, 116, 97, 111, 126, 100, 75, 89, 110, 106, 105, 133, 158, 141, 109, 101, 87, 92, 141, 175, 177, 178, 167, 138, 135, 155, 142, 102, 127, 182, 179, 130, 93, 102, 108, 117, 161, 160, 113, 104, 102, 86, 107, 138, 121, 101, 106, 110, 131, 135, 114, 144, 156, 115, 111, 137, 128, 114, 124, 106, 104, 137, 135, 117, 132, 141, 138, 130, 114, 119, 138, 147, 148, 144, 157, 162, 138, 135, 113, 101, 126, 135, 151, 166, 167, 165, 139, 116, 119, 121, 109, 88, 76, 100, 144, 147, 133, 144, 146, 159, 161, 127, 105, 112, 133, 145, 168, 169, 154, 172, 151, 124, 135, 138, 134, 125, 111, 108, 129, 147, 151, 157, 172, 160, 113, 85, 89, 109, 127, 151, 153, 132, 128, 108, 105, 127, 132, 135, 135, 118, 104, 109, 127, 153, 163, 136, 129, 124, 94, 104, 126, 142, 149, 132, 126, 132, 121 };   

char  mask[9] =    
{   
    1, 2, 1,   
    2, 4, 2,   
    1, 2, 1   
};   

#define SHIFT  (4)   


int main(int argc, char** argv) {

	IMG_conv_3x3_c(in_data, out_data_c, COLS, mask, SHIFT);

	if (argc > 42 && ! strcmp(argv[0], ""))	printf("%d", out_data_c[COLS - 1]); // NAO FUNCIONA FAZENDO O CAST PARA UNSIGNED INT?!?!

	int i;
	for(i=0; i < COLS; i++) {
			if(out_data_c[i] != out_data_c_expected[i]) {
					return 1;
			}
	}

	return 10;

}
