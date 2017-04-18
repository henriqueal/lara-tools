#include "oourafft.c"

int main()
{
  int i, j;
  int *ip;
  double *ref, *cmp, *src, *w;
  double t_start, t_end, t_overhead, t_total = 0, err_val;

  /* Measure overhead of get_time() call */
  t_start = get_time();
  t_end = get_time();
  t_overhead = t_end - t_start;

  /* Prepare aux data */
#if !defined(__APPLE__) && !defined(__FreeBSD__) /* Darwin always 16-byte aligns malloc data */
  ip = memalign(16, sqrt(N)*sizeof(int));
  w  = memalign(16, 2*N*5/4*sizeof(double));
#else
  ip = malloc(sqrt(N)*sizeof(int));
  w  = malloc(2*N*5/4*sizeof(double));
#endif
  makewt(N >> 1, ip, w);
  
  /* Allocate buffers */
#if !defined(__APPLE__) && !defined(__FreeBSD__) /* Darwin always 16-byte aligns malloc data */
  ref = memalign(16, 2*N*sizeof(double));
  cmp = memalign(16, 2*N*sizeof(double));
  src = memalign(16, 2*N*sizeof(double));
#else
  ref = malloc(2*N*sizeof(double));
  cmp = malloc(2*N*sizeof(double));
  src = malloc(2*N*sizeof(double));
#endif
  
  /* Perform sanity check of FFT */
  putdata(0, 2*N - 1, ref);
  cdft(2*N,  1, ref, ip, w);
  cdft(2*N, -1, ref, ip, w);
  err_val = errorcheck(0, 2*N - 1, 1.0/N, ref);
  if (fabs(err_val) > 1e-10) {
    printf("FFT sanity check failed! Difference is: %le\n", err_val);
    abort();
  }
  
  /* Prepare reference sequence */
  memset(ref, 0, 2*N*sizeof(double));
  putdata(0, N-1, ref);
  cdft(2*N, 1, ref, ip, w);
  for (j=0; j<N; ++j)
    ref[2*j+1] = -ref[2*j+1];
  
  /*printf("Doing %d correlations (%d FFTs of size %d)\n", TRIES, 2*TRIES, N);*/
  memset(src, 0, 2*N*sizeof(double));
  putdata(0, N-1, src);

  t_start = get_time();
  for (i=0; i<TRIES; ++i) {
    int k;

    memcpy(cmp, src, 2*N*sizeof(double));
    cdft(2*N, 1, cmp, ip, w);

    for (k=0; k<N; ++k) {
      double re1 = cmp[2*k];
      double re2 = ref[2*k];
      double im1 = cmp[2*k+1];
      double im2 = ref[2*k+1];
      cmp[2*k]   = re1*re2 - im1*im2;
      cmp[2*k+1] = re1*im2 + im1*re2;
    }

    cdft(2*N, -1, cmp, ip, w);
  }
  t_end = get_time();
  t_total += t_end - t_start - t_overhead; 

  for (j=0; j<N; ++j) {
    printf("%e %e\n",
           (fabs(cmp[2*j]) > 1e-9 ? cmp[2*j] : 0),
           (fabs(cmp[2*j+1]) > 1e-9 ? cmp[2*j+1] : 0));
  }
  /*printf("Overall time: %le, for single correlation: %le\n", t_total, t_total/TRIES);*/

  free(ref);
  free(w);
  free(ip);

  free(cmp);
  free(src);
  
  return 0;
}

