#include "ackermann.c"
#include <stdio.h>
int main() {
    int n = 8;

 #pragma monitor start
    int result = ackermann(3, 3);
    
 #pragma monitor stop
    if(result == 61){  
      return 10;
    } else{
      return 1;
    }
}
