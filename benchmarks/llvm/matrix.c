/* -*- mode: c -*-
 * $Id: matrix.c 36673 2007-05-03 16:55:46Z laurov $
 * http://www.bagley.org/~doug/shootout/
 */

#include <stdio.h>
#include <stdlib.h>

/*#define SIZE 30*/
#define SIZE 10

int **mkmatrix(int rows, int cols) {
    int i, j, count = 1;
    int **m = (int **) malloc(rows * sizeof(int *));
    for (i=0; i<rows; i++) {
	m[i] = (int *) malloc(cols * sizeof(int));
	for (j=0; j<cols; j++) {
	    m[i][j] = count++;
	}
    }
    return(m);
}

void zeromatrix(int rows, int cols, int **m) {
    int i, j;
    for (i=0; i<rows; i++)
	for (j=0; j<cols; j++)
	    m[i][j] = 0;
}

void freematrix(int rows, int **m) {
    while (--rows > -1) { free(m[rows]); }
    free(m);
}

int **mmult(int rows, int cols, int **m1, int **m2, int **m3) {
    int i, j, k, val;
    for (i=0; i<rows; i++) {
	for (j=0; j<cols; j++) {
	    val = 0;
	    for (k=0; k<cols; k++) {
		val += m1[i][k] * m2[k][j];
	    }
	    m3[i][j] = val;
	}
    }
    return(m3);
}


