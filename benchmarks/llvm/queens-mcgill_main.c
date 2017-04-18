#include "queens-mcgill.c"

int main(int argc, char **argv)
{
   register int  i;				/* Loop variable */
   register char *p;				/* Ptr to argument */
   char *usage =
"Usage:  %s [-ac] n\n\
\tn\tNumber of queens (rows and columns). An integer from 1 to 100.\n\
\t-a\tFind and print all solutions.\n\
\t-c\tCount all solutions, but do not print them.\n";

#ifdef	MPW					/* Macintosh MPW ONLY */
   InitCursorCtl(0);				/* Enable cursor control */
#endif

   progname = argv[0];				/* Name of the program */

   /****   DECODE COMMAND LINE ARGUMENTS   ****/
   printing = 0;
#ifdef SMALL_PROBLEM_SIZE
   queens = 13;
#else
   queens = 14;
#endif
   findall = 1;

   for(i = 1; i < argc; ++i) {			/* Scan through arguments */
      p = argv[i];				/* Ptr to base of argument */
      if(*p == '-') {				/* Command line option? */
         while(*++p) {				/* Loop through characters */
            switch(*p) {			/* What is the character */
               case 'c':			/* '-c' option */
                  printing = 0;			/* Counting, not printing */
               case 'a':			/* '-a' option */
                  findall = 1;			/* Find all solutions */
                  break;
               default:				/* Illegal option */
                  fprintf(stderr,"%s: Illegal option '%s'\n",progname,argv[i]);
                  fprintf(stderr,usage,progname);
                  exit(-1);
            }					/* End of switch */
         }					/* End of loop */
      }						/* End of option test */
      else {
         if(sscanf(p,"%d",&queens) != 1) {	/* Read integer argument */
            fprintf(stderr,"%s: Non-integer argument '%s'\n",progname,p);
            exit(-1);
         }
         if(queens <= 0) {			/* N must be positive */
            fprintf(stderr,"%s: n must be positive integer\n",progname);
            exit(-1);
         }
         if(queens > MAXQUEENS) {		/* N can't be too large */
            fprintf(stderr,"%s: Can't have more than %d queens\n",
               progname, MAXQUEENS);
            exit(-1);
         }
      }						/* End of argument test */
   }						/* End of argument scan loop */
   if(!queens) {
      fprintf(stderr,"%s: Missing n argument\n",progname);
      fprintf(stderr,usage,progname);
      exit(-1);
   }

   ranks = files = queens;			/* NxN board for N queens */
   printf("%d queen%s on a %dx%d board...\n",
      queens, queens > 1 ? "s" : "", ranks, files);
   fflush(stdout);

   /* Initialization */
   solutions = 0;				/* No solutions yet */
   for(i = 0; i < MAXFILES; ++i) file[i] = EMPTY;
   for(i = 0; i < MAXDIAGS; ++i) fordiag[i] = bakdiag[i] = EMPTY;

   /* Find all solutions (begin recursion) */
   find(0);
   if(printing && solutions) putchar('\n');

   /* Report results */
   if(solutions == 1) printf("...there is 1 solution\n");
   else printf("...there are %ld solutions\n", solutions);

   exit(0);					/* No errors */
}

