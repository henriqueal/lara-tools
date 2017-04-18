#include "mandel-2.c"
int main() {
  int i, j;
    for (j = -39; j < 39; ++j) {
        for (i = -39; i < 39; ++i)
            printf(loop(j/40.0-0.5 + i/40.0*I) > max_i ? "*" : " ");
        printf("\n");
    }
    return 0;
}

