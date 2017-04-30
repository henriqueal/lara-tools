#include "lists.c"
int main(int argc, char *argv[]) {
#ifdef SMALL_PROBLEM_SIZE
#define LENGTH 300000
#else
#define LENGTH 3000000
#endif
  int n = ((argc == 2) ? atoi(argv[1]) : LENGTH);
  int result = 0;
  while(n--) result = test_lists();
  printf("%d\n", result);
  return 0;
}
