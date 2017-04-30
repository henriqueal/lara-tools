#include "ffbench.c"

int main()
{
	int i, j, k, l, m, npasses = Passes, faedge;
	Float *fdata;
	static int nsize[] = {0, 0, 0};
	long fanum, fasize;
	double mapbase, mapscale, rmin, rmax, imin, imax;

	faedge = Asize; 	   /* FFT array edge size */
	fanum = faedge * faedge;   /* Elements in FFT array */
	fasize = ((fanum + 1) * 2 * sizeof(Float)); /* FFT array size */
	nsize[1] = nsize[2] = faedge;

	fdata = (Float *) malloc(fasize);
	if (fdata == NULL) {
           fprintf(stderr, "Can't allocate data array.\n");
	   exit(1);
	}

	/*  Generate data array to process.  */

#define Re(x,y) fdata[1 + (faedge * (x) + (y)) * 2]
#define Im(x,y) fdata[2 + (faedge * (x) + (y)) * 2]

	memset(fdata, 0, fasize);
	for (i = 0; i < faedge; i++) {
	   for (j = 0; j < faedge; j++) {
	      if (((i & 15) == 8) || ((j & 15) == 8))
		 Re(i, j) = 128.0;
	   }
	}

	for (i = 0; i < npasses; i++) {
/*printf("Pass %d\n", i);*/
	   /* Transform image to frequency domain. */
	   fourn(fdata, nsize, 2, 1);

	   /*  Back-transform to image. */
	   fourn(fdata, nsize, 2, -1);
	}

	{
	   double r, ij, ar, ai;
	   rmin = 1e10; rmax = -1e10;
	   imin = 1e10; imax = -1e10;
	   ar = 0;
	   ai = 0;

	   for (i = 1; i <= fanum; i += 2) {
	      r = fdata[i];
	      ij = fdata[i + 1];
	      ar += r;
	      ai += ij;
	      rmin = min(r, rmin);
	      rmax = max(r, rmax);
	      imin = min(ij, imin);
	      imax = max(ij, imax);
	   }
#ifdef DEBUG
           printf("Real min %.4g, max %.4g.  Imaginary min %.4g, max %.4g.\n",
	      rmin, rmax, imin, imax);
           printf("Average real %.4g, imaginary %.4g.\n", 
	      ar / fanum, ai / fanum);
#endif
	   mapbase = rmin;
	   mapscale = 255 / (rmax - rmin);
	}

	/* See if we got the right answers. */

	m = 0;
	for (i = 0; i < faedge; i++) {
	   for (j = 0; j < faedge; j++) {
	      k = (Re(i, j) - mapbase) * mapscale;
	      l = (((i & 15) == 8) || ((j & 15) == 8)) ? 255 : 0;
	      if (k != l) {
		 m++;
		 fprintf(stderr,
                    "Wrong answer at (%d,%d)!  Expected %d, got %d.\n",
		    i, j, l, k);
	      }
	   }
	}
	if (m == 0) {
           fprintf(stderr, "%d passes.  No errors in results.\n", npasses);
	} else {
           fprintf(stderr, "%d passes.  %d errors in results.\n",
	      npasses, m);
	}

#ifdef CAPOUT

	/* Output the result of the transform as a CA Lab pattern
	   file for debugging. */

	{
#define SCRX  322
#define SCRY  200
#define SCRN  (SCRX * SCRY)
	   unsigned char patarr[SCRY][SCRX];
	   FILE *fp;

/*  Map user external state numbers to internal state index  */

#define UtoI(x)     (((((x) >> 1) & 0x7F) | ((x) << 7)) & 0xFF)

	   /* Copy data from FFT buffer to map. */

	   memset(patarr, 0, sizeof patarr);
	   l = (SCRX - faedge) / 2;
	   m = (faedge > SCRY) ? 0 : ((SCRY - faedge) / 2);
	   for (i = 1; i < faedge; i++) {
	      for (j = 0; j < min(SCRY, faedge); j++) {
		 k = (Re(i, j) - mapbase) * mapscale;
		 patarr[j + m][i + l] = UtoI(k);
	      }
	   }

	   /* Dump pattern map to file. */

           fp = fopen("fft.cap", "w");
	   if (fp == NULL) {
              fprintf(stderr, "Cannot open output file.\n");
	      exit(0);
	   }
           putc(':', fp);
	   putc(1, fp);
	   fwrite(patarr, SCRN, 1, fp);
	   putc(6, fp);
	   fclose(fp);
	}
#endif

	return 0;
}
