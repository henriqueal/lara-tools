#include "perlin.c"
int main() {
  init();
  
  double x, y, z, sum = 0.0;
#ifdef SMALL_PROBLEM_SIZE
  for (x = -11352.57; x < 23561.57; x += 1.235)
    for (y = -346.1235; y < 124.124; y += 2.4325)
      for (z = -156.235; y < 23.2345; y += 2.45)
#else
  for (x = -11352.57; x < 23561.57; x += .1235)
    for (y = -346.1235; y < 124.124; y += 1.4325)
      for (z = -156.235; y < 23.2345; y += 2.45)
#endif
        sum += noise(x, y, z);
  
  printf("%e\n", sum);
  return 0;
}
