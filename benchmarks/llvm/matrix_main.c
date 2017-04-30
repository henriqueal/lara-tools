#include "matrix.c"

int main(int argc, char *argv[]) {
#ifdef SMALL_PROBLEM_SIZE
#define LENGTH 300000
#else
#define LENGTH 3000000
#endif
    int i, n = ((argc == 2) ? atoi(argv[1]) : LENGTH);
	
    int **m1 = mkmatrix(SIZE, SIZE);
    int **m2 = mkmatrix(SIZE, SIZE);
    int **mm = mkmatrix(SIZE, SIZE);

    for (i=0; i<n; i++) {
	mm = mmult(SIZE, SIZE, m1, m2, mm);
    }
    printf("%d %d %d %d\n", mm[0][0], mm[2][3], mm[3][2], mm[4][4]);

    freematrix(SIZE, m1);
    freematrix(SIZE, m2);
    freematrix(SIZE, mm);
    return(0);
}
