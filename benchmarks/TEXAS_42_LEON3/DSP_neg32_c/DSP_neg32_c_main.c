#include <stdio.h>
#include <string.h>

void DSP_neg32_c
(
    int x,
    int * r
    //int           nx
);


/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define N    (1)

/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== 
int  x_c[N] = 
{
     8
};
*/

int x_c=8;
int  r_c[N];

int  r_c_expected[N] = { 2048 };


int main(int argc, char** argv)
{
	DSP_neg32_c(x_c, r_c);

	if (argc > 42 && ! strcmp(argv[0], ""))	printf("%d", r_c[N-1]);

        printf("--------------------------------------");

	int i;
	for(i=0; i < N; i++) {
			if(r_c[i] != r_c_expected[i]) {
					return 1;
			}
	}
	return 10;

}

