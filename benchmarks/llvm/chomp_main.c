#include "chomp.c"

#define N 55

int main(void)
{ 
  int i;
  int *r_c;
  int r_c_expected[55] = {0, 2, 2, 1, 7, 1, 0, 0, 2, 1, 7, 0, 0, 6, 1, 1, 6, 0, 0, 5, 1, 1, 5, 0, 0, 4, 1, 1, 4, 0, 0, 3, 1, 1, 3, 0, 0, 2, 1, 1, 2, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1};

  r_c = chomp_game();

  for(i=0; i<N; i++){
    if(r_c[i] != r_c_expected[i]){
      free(r_c);
      return 1;
    }
  }
  free(r_c);
  return 10;

}

/*****************************************************************************/
