#include "heapsort.c"
int main(int argc, char *argv[]) {
#ifdef SMALL_PROBLEM_SIZE
#define LENGTH 800000
#else
#define LENGTH 8000000
#endif
    int N = ((argc == 2) ? atoi(argv[1]) : LENGTH);
    double *ary;
    int i;
    
    /* create an array of N random doubles */
    ary = (double *)malloc((N+1) * sizeof(double));
    for (i=1; i<=N; i++) {
	ary[i] = gen_random(1);
    }

    heapsort(N, ary);

    printf("%f\n", ary[N]);

    free(ary);
    return(0);
}

