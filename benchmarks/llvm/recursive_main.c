#include "recursive.c"

int main(int argc, char ** argv) {
  int n = 10;

  printf("Ack(3,%d): %d\n", n + 1, ack(3, n+1));
  printf("Fib(%.1f): %.1f\n", 28.0 + n, fibFP(28.0+n));
  printf("Tak(%d,%d,%d): %d\n", 3 * n, 2 * n, n, tak(3*n, 2*n, n));
  printf("Fib(3): %d\n", fib(3));
  printf("Tak(3.0,2.0,1.0): %.1f\n", takFP(3.0, 2.0, 1.0));

  return 0;
}
