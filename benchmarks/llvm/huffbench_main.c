
#include "huffbench.c"
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
    
    // initialization
    byte * test_data = generate_test_data(TEST_SIZE);
    
    /*
    FILE * before = fopen("before","wb");
    fwrite(test_data,1,TEST_SIZE,before);
    fclose(before);
    */
            
    // get starting time    
    //struct timespec start, stop;
    //clock_gettime(CLOCK_REALTIME,&start);

    // what we're timing
    for (i = 0; i < NUM_LOOPS; ++i)
        compdecomp(test_data,TEST_SIZE);
    
    // calculate run time
    //clock_gettime(CLOCK_REALTIME,&stop);        
    double run_time = 0; //(stop.tv_sec - start.tv_sec) + (double)(stop.tv_nsec - start.tv_nsec) / 1000000000.0;

    /*
    FILE * after = fopen("after","wb");
    fwrite(test_data,1,TEST_SIZE,after);
    fclose(after);
    */
    
    // release resources
    free(test_data);

    // report runtime
    if (ga_testing)
        fprintf(stdout,"%f",run_time);
    else        
        fprintf(stdout,"\nhuffbench (Std. C) run time: %f\n\n",run_time);
    
    fflush(stdout);
    
    // done
    return 0;
}
