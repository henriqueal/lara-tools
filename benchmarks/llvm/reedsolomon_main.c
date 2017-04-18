#include "reedsolomon.c"
int main(void) {
  unsigned char rs_in[204], rs_out[204];
  int i, j, k;

#ifdef SMALL_PROBLEM_SIZE
#define LENGTH 15000
#else
#define LENGTH 150000
#endif

#ifdef __MINGW32__
#define random() rand()
#endif

  for (i=0; i<LENGTH; ++i) {
    /* Generate random data */
    for (j=0; j<188; ++j) {
      rs_in[j] = (random() & 0xFF);
    }
    rsenc_204(rs_out, rs_in);
    /* Number of errors to insert */
    k = random() & 0x7F;

    for (j=0; j<k; ++j) {
      rs_out[random() % 204] = (random() & 0xFF);
    }
    
    rsdec_204(rs_in, rs_out);
  }
  return 0;
}
