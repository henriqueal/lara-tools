#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void ary3(int n, int * rc);

int rc[2];


int rc_exp[2] = {1000, 150000000};

int main(int argc, char **argv) {

  int n = 150000;


  ary3(n, rc); 

  if(rc[0] == rc_exp[0] && rc[1] == rc_exp[1]){
    return 10;
  }

  return 1;
}
