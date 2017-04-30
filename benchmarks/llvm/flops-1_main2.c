#include "flops-1.c"

int main(){
  long loops, NLimit;
  			/****************************/
  loops = 15625;        /* Initial number of loops. */
			/*     DO NOT CHANGE!       */
			/****************************/

  NLimit = 512000000;

  A0 = 1.0;
  A1 = -0.1666666666671334;
  A2 = 0.833333333809067E-2;
  A3 = 0.198412715551283E-3;
  A4 = 0.27557589750762E-5;
  A5 = 0.2507059876207E-7;
  A6 = 0.164105986683E-9;

  B0 = 1.0;
  B1 = -0.4999999999982;
  B2 = 0.4166666664651E-1;
  B3 = -0.1388888805755E-2;
  B4 = 0.24801428034E-4;
  B5 = -0.2754213324E-6;
  B6 = 0.20189405E-8;

  C0 = 1.0;
  C1 = 0.99999999668;
  C2 = 0.49999995173;
  C3 = 0.16666704243;
  C4 = 0.4166685027E-1;
  C5 = 0.832672635E-2;
  C6 = 0.140836136E-2;
  C7 = 0.17358267E-3;
  C8 = 0.3931683E-4;

  D1 = 0.3999999946405E-1;
  D2 = 0.96E-3;
  D3 = 0.1233153E-5;

  E2 = 0.48E-3;
  E3 = 0.411051E-6;

  TLimit = 1.0;
  piref = 3.14159265358979324;
  one   = 1.0;
  two   = 2.0;
  three = 3.0;
  four  = 4.0;
  five  = 5.0;
  scale = one;

  printf("\n");
  printf("   FLOPS C Program (Double Precision), V2.0 18 Dec 1992\n\n");

  printf("   Module     Error        RunTime      MFLOPS\n");
  printf("                            (usec)\n");

  flops1(loops, NLimit);
  return 0;
}
