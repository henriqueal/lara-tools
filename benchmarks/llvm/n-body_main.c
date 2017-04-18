#include "n-body.c"
int main(int argc, char ** argv)
{
  int n = 5000000;
  int i;

  offset_momentum(NBODIES, bodies);
  printf ("%.9f\n", energy(NBODIES, bodies));
  for (i = 1; i <= n; i++)
    advance(NBODIES, bodies, 0.01);
  printf ("%.9f\n", energy(NBODIES, bodies));
  return 0;
}
