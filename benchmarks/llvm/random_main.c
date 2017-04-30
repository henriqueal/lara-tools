#include "random.c"
int main(int argc, char *argv[]) {
#ifdef SMALL_PROBLEM_SIZE
#define LENGTH 40000000
#else
#define LENGTH 400000000
#endif
  int N = ((argc == 2) ? atoi(argv[1]) : LENGTH) - 1;
    
  while (N--) {
    gen_random(100.0);
  }
  printf("%.9f\n", gen_random(100.0));
  return(0);
}
