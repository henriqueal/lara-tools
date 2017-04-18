#include "lpbench.c"

int main(int argc, char ** argv)
{
    int i;
    
    // do we have verbose output?
    bool ga_testing = false;
    
    if (argc > 1)
    {
        for (i = 1; i < argc; ++i)
        {
            if (!strcmp(argv[1],"-ga"))
            {
                ga_testing = true;
                break;
            }
        }
    }
    
    double ** a = (double **)malloc(sizeof(double) * N);
    
    for (i = 0; i < N; ++i)
        a[i] = (double *)malloc(sizeof(double) * NP1);
    
    double * b = (double *)malloc(sizeof(double) * N);
    double * x = (double *)malloc(sizeof(double) * N);
    int * ipvt = (int *)malloc(sizeof(int)    * N);

    // calculate operations per timeInSeconds
    double ops = (2.0 * ((double)N * N * N)) / 3.0 + 2.0 * ((double)N * N);

    // generate matrix    
    matgen(a,b);
    
    // get starting time    
    //struct timespec start, stop;
    //clock_gettime(CLOCK_REALTIME,&start);

    // what we're timing
    dgefa(a,ipvt);
    dgesl(a,ipvt,b);
    
    // calculate run time
    //clock_gettime(CLOCK_REALTIME,&stop);        
    double run_time = 0;//(stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec) / 1000000000.0;
    
    // clean up
    free(ipvt);
    free(x);
    free(b);
    
    for (i = 0; i < N; ++i)
        free(a[i]);
    
    free(a);

    // report runtime
    if (ga_testing)
        fprintf(stdout,"%f",run_time);
    else        
        fprintf(stdout,"\nlpbench (Std. C) run time: %f\n\n",run_time);
    
    fflush(stdout);
    
    // done
    return 0;
}
