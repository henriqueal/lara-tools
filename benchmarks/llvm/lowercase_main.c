#include "lowercase.c"
int main(int argc, char **argv)
{
  size_t i;
  for (i = 0; i < 32; i++)
    doTest(i);

  return 0;
}
