#include "misr.c"

/* Main Program */

int main(int argc,char *argv[])
{
        misr_type cell_array;
	int num_vect, num_times, num_true, i;
	double prob;
	char structure[MAX_REG_LN];
	unsigned short seed[3];

/* Check usage */
	if (0 && argc < 6)
	{
		printf("Usage: MISR fileout reg_len #_vectors prob #_times [structure] [seed] [seed] [seed]\n");
		return 1;
	}

/* input and translate arguments */
	/*sscanf(argv[2], "%lu", &reg_len);
	sscanf(argv[3], "%lu", &num_vect);
	sscanf(argv[4], "%le", &prob);
	sscanf(argv[5], "%lu", &num_times);*/

        reg_len = num_vect = 10;
        prob = .25;
#ifdef SMALL_PROBLEM_SIZE
        num_times = 30000;
#else
        num_times = 100000;
#endif


	if (argc > 6) strcpy(structure, argv[6]);
	else {
		for (i=1; i<reg_len; i++)
			structure[i] = '0';
		structure[0] = '1';
		structure[reg_len] = 0;
	}
        if (argc > 7) sscanf(argv[7], "%hu", &seed[0]); else seed[0] = 1;
        if (argc > 8) sscanf(argv[8], "%hu", &seed[1]); else seed[1] = 0;
        if (argc > 9) sscanf(argv[9], "%hu", &seed[2]); else seed[2] = 0;


/* Check validity of input */
	if (reg_len > MAX_REG_LN)
	{
		printf("Register too long; Max. = %d\n", MAX_REG_LN);
		return 2;
	}
	if ((prob > 1) || (prob < 0))
	{
		printf("Prob. out of range 0=<Prob>=1\n");
		return 3;
	}
	if (strlen(structure) != reg_len)
	{
		printf("Structure does not match Register length:\n");
		return 4;
	}


/*initialize random f'n generator */
        seed48(seed);


/* create MISRs of reg_len length */
	create_link_list(&cell_array);

/* simulate both circuits */
	num_true = 0; 
	if (num_vect != 0)
	{
		for (i=0; i<num_times; i++)
		{
			init(&cell_array);
			num_true += simulate(num_vect, &cell_array, prob, structure);
		}
	}
	else  /* ie. infinite case */
	{
		init(&cell_array); 
		simulate(INF, &cell_array, prob, structure);
		for(i=0; i<num_times; i++)
		{
			num_true += simulate(1, &cell_array, prob, structure);
		}
	}


/* output results */
	printf("reg_len	#_vect	prob      #_tms	struct	seed1	seed2	seed3	Prob same output\n ");

	printf("%d	%d	%.3e %d	%s	%d	%d	%d	%.8e\n", reg_len, num_vect, prob, num_times, structure, seed[0], seed[1], seed[2],(double)(num_times - num_true)/(double)num_times);
	//kill_list(&cell_array);
        return 0;
}

