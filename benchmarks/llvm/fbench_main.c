#include "fbench_main.c"

/*  Initialise when called the first time  */

int
main(argc, argv)
int argc;
char *argv[];
{
	int i, j, k, errors;
	double od_fline, od_cline;
#ifdef ACCURACY
	long passes;
#endif

	spectral_line[1] = 7621.0;	 /* A */
	spectral_line[2] = 6869.955;	 /* B */
	spectral_line[3] = 6562.816;	 /* C */
	spectral_line[4] = 5895.944;	 /* D */
	spectral_line[5] = 5269.557;	 /* E */
	spectral_line[6] = 4861.344;	 /* F */
        spectral_line[7] = 4340.477;     /* G'*/
	spectral_line[8] = 3968.494;	 /* H */

	/* Process the number of iterations argument, if one is supplied. */

  niter = 1000000;

	/* Load test case into working array */

	clear_aperture = 4.0;
	current_surfaces = 4;
	for (i = 0; i < current_surfaces; i++)
	   for (j = 0; j < 4; j++)
	      s[i + 1][j + 1] = testcase[i][j];

#ifdef ACCURACY
        printf("Beginning execution of floating point accuracy test...\n");
	passes = 0;
#else
        printf("Ready to begin John Walker's floating point accuracy\n");
        printf("and performance benchmark.  %d iterations will be made.\n\n",
	   niter);

        printf("\nMeasured run time in seconds should be divided by %.f\n", niter / 1000.0);
        printf("to normalise for reporting results.  For archival results,\n");
        printf("adjust iteration count so the benchmark runs about five minutes.\n\n");
#endif

	/* Perform ray trace the specified number of times. */

#ifdef ACCURACY
	while (TRUE) {
	   passes++;
	   if ((passes % 100L) == 0) {
              printf("Pass %ld.\n", passes);
	   }
#else
	for (itercount = 0; itercount < niter; itercount++) {
#endif

	   for (paraxial = 0; paraxial <= 1; paraxial++) {

	      /* Do main trace in D light */

	      trace_line(4, clear_aperture / 2.0);
	      od_sa[paraxial][0] = object_distance;
	      od_sa[paraxial][1] = axis_slope_angle;
	   }
	   paraxial = FALSE;

	   /* Trace marginal ray in C */

	   trace_line(3, clear_aperture / 2.0);
	   od_cline = object_distance;

	   /* Trace marginal ray in F */

	   trace_line(6, clear_aperture / 2.0);
	   od_fline = object_distance;

	   aberr_lspher = od_sa[1][0] - od_sa[0][0];
	   aberr_osc = 1.0 - (od_sa[1][0] * od_sa[1][1]) /
	      (sin(od_sa[0][1]) * od_sa[0][0]);
	   aberr_lchrom = od_fline - od_cline;
	   max_lspher = sin(od_sa[0][1]);

	   /* D light */

	   max_lspher = 0.0000926 / (max_lspher * max_lspher);
	   max_osc = 0.0025;
	   max_lchrom = max_lspher;
#ifndef ACCURACY
	}
#endif

	/* Now evaluate the accuracy of the results from the last ray trace */

        sprintf(outarr[0], "%15s   %21.11f  %14.11f",
           "Marginal ray", od_sa[0][0], od_sa[0][1]);
        sprintf(outarr[1], "%15s   %21.11f  %14.11f",
           "Paraxial ray", od_sa[1][0], od_sa[1][1]);
	sprintf(outarr[2],
           "Longitudinal spherical aberration:      %16.11f",
	   aberr_lspher);
	sprintf(outarr[3],
           "    (Maximum permissible):              %16.11f",
	   max_lspher);
	sprintf(outarr[4],
           "Offense against sine condition (coma):  %16.11f",
	   aberr_osc);
	sprintf(outarr[5],
           "    (Maximum permissible):              %16.11f",
	   max_osc);
	sprintf(outarr[6],
           "Axial chromatic aberration:             %16.11f",
	   aberr_lchrom);
	sprintf(outarr[7],
           "    (Maximum permissible):              %16.11f",
	   max_lchrom);

	/* Now compare the edited results with the master values from
	   reference executions of this program. */

	errors = 0;
	for (i = 0; i < 8; i++) {
	   if (strcmp(outarr[i], refarr[i]) != 0) {
#ifdef ACCURACY
              printf("\nError in pass %ld for results on line %d...\n",
		     passes, i + 1);
#else
              printf("\nError in results on line %d...\n", i + 1);
#endif
              printf("Expected:  \"%s\"\n", refarr[i]);
              printf("Received:  \"%s\"\n", outarr[i]);
              printf("(Errors)    ");
	      k = strlen(refarr[i]);
	      for (j = 0; j < k; j++) {
                 printf("%c", refarr[i][j] == outarr[i][j] ? ' ' : '^');
		 if (refarr[i][j] != outarr[i][j])
		    errors++;
	      }
              printf("\n");
	   }
	}
#ifdef ACCURACY
	}
#else
	if (errors > 0) {
           printf("\n%d error%s in results.  This is VERY SERIOUS.\n",
              errors, errors > 1 ? "s" : "");
	} else
           printf("\nNo errors in results.\n");
#endif
	return 0;
}
