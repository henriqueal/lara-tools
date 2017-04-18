#include "puzzle.c"

int main() {
    int i, j, duplicate;
    int *rndArr;

    srand(1);

	for (i = 0; i < NLOOPS1; i++) {
		rndArr = createRandomArray(ARRAY_SIZE);
		for (j = 0; j < NLOOPS2; j++)
			duplicate = findDuplicate(rndArr, ARRAY_SIZE+1);
		free(rndArr);
		printf("Found duplicate: %d\n", duplicate);
	}

    return 0;
}
