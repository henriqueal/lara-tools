/* the name was converted to pgm5.c */
/*******************************************************

program:	MISR.C


This program creates two MISR's one which contains the 
true outputs and the other in which the outputs are 
not currupted with the probability given in the input. 
The values of the MISR's are compared to see if the
introduced errors have cancelled themselves.

The usage  is : MISR fileout reg_len #_vectors prob 
#_times [structure] [seed] [seed] [seed].
fileout has been nullified in this case to fit with
    the description of the project.
reg_len is the length of the MISR's in considerstion.
#_vectors is the number of vectors to input to the 
    MISR's before checking to see of they are 
    identical. If '0', assume large value (infinite).
prob described above.
#_times is the number of times that the MISR's are 
    initialized and the experiment done before the
    # of times outputs same/ # of times it is run
    (#_times) is calculated.
[structure] gives the feedback structure of the MISR's.
    if it is omitted, the  situition where the end   
    feeds back to the beginning is used.
[seed]* is the seed to be used to initialize the random
    generator.
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 10000
#define MAX_REG_LN 100
#define BIN_MASK 1
#define TRUE 1
#define FALSE 0

#ifdef __MINGW32__
# define seed48(x) srand(x)
# define lrand48() ((rand() << 16) ^ (rand()))
#endif

int reg_len;

typedef struct cells {
        int f_free;
	int faulty;
        struct cells *next;
        }misr_type;

/* Prototypes */
/*
int simulate(int iterations, misr_type *present, double prob, char *structure);
void init(misr_type *present);
void kill_list(misr_type *present);
void create_link_list(misr_type *cell_array);
*/

/*************************************************************
create and initialize the MISR's which is a linked list of 
misr_type.
*************************************************************/
void create_link_list(misr_type *cell_array)
{
	int i;
	misr_type *temp, *present;

        memset(cell_array, 0, sizeof(*cell_array));
        present = cell_array ;
	for(i=0; i<reg_len+1; i++)
	{
		temp = (misr_type *) malloc(sizeof(misr_type));
        	temp->f_free = 1;
		temp->faulty = 1;
        	temp->next = NULL;
                present->next = temp; 
		present = present->next;
	}
}


/*************************************************************
release linked list when finished
*************************************************************/
void kill_list(misr_type *present)
{
        misr_type *temp;
 
        while(present)
        {
                temp = present->next;
                free(present);
                present = temp;
        }
        return;
}


/************************************************************
make both MISR's identical to start the experiment
************************************************************/
void init(misr_type *present)
{

	while(present->next != NULL)
	{
		present->faulty = present->f_free;
		present = present->next;
	}
}


/***********************************************************
this proceedure is the workhorse of the program. Each time it
is called, it calculates the next value of each cell in the
MISR's and does this for hte number of times necessary.
***********************************************************/
int simulate(int iterations, misr_type *present, double prob, char *structure)
{
	misr_type *temp;
	int different, savef_free, savefaulty;
	int rem, quot, h, i, j;
	long randv;
	double randprob;

	different = FALSE;
	quot = (reg_len-1) / 31;
        rem = (reg_len-1) % 31;
	temp = present;

	for(h=0; h<iterations; h++)
	{
		savef_free = 0;
		savefaulty = 0;
		for (i=0; i<quot; i++)
		{
			randv = lrand48();
			for (j=0; j<31; j++)
			{
				if (structure[i*31 + j] == '1')
				{
					savef_free += temp->f_free;
					savefaulty += temp->faulty;
				}
				temp->f_free = ((temp->next->f_free + randv) & BIN_MASK);
				randprob = ((double)(lrand48() % 1000) / 1000);
				if (prob > randprob) randv ^= BIN_MASK;
				temp->faulty = ((temp->next->faulty + randv) & BIN_MASK);
				temp = temp->next;
				randv >>= 1;
			}
		}
		randv = lrand48();
		for (j=0; j<rem; j++)
		{
                        if (structure[quot*31 + j] == '1')
                        {
                                savef_free += temp->f_free;
                                savefaulty += temp->faulty;
                        }
                        temp->f_free = ((temp->next->f_free + randv) & BIN_MASK);                                             
                        randprob = ((double)(lrand48() % 1000) / 1000);                                
			if (prob > randprob) randv ^= BIN_MASK;
                        temp->faulty = ((temp->next->faulty + randv) & BIN_MASK);
                        temp = temp->next;
                        randv >>= 1;
                }
		randv = lrand48();
		if (structure[reg_len - 1] == '1')
		{
			savef_free += temp->f_free;
			savefaulty += temp->faulty;
		}
		temp->f_free = ((savef_free + randv) & BIN_MASK);
		randprob = ((double)(lrand48() % 10000) / 10000);
		if (prob > randprob) randv ^= BIN_MASK;
		temp->faulty = ((savefaulty + randv) & BIN_MASK);

		temp = present;
	}

	for (i=0; i<reg_len; i++)
	{
		if (temp->f_free != temp->faulty) different = TRUE;
		temp = temp->next;
	}
	return different;

}
