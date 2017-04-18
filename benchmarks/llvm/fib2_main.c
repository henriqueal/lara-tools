#include "fib2.c"
int
main(int argc, char *argv[]) {
#ifdef SMALL_PROBLEM_SIZE
#define LENGTH 40
#else
#define LENGTH 43
#endif
    int N = ((argc == 2) ? atoi(argv[1]) : LENGTH);
    printf("%ld\n", fib(N));
    return(0);
}
