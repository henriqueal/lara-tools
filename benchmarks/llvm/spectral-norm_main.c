#include "spectral-norm.c"

int main(int argc, char *argv[])
{
  int i;
  int N = ((argc == 2) ? atoi(argv[1]) : 2000);
  double u[N],v[N],vBv,vv;
  for(i=0;i<N;i++) u[i]=1;
  for(i=0;i<10;i++)
    {
      eval_AtA_times_u(N,u,v);
      eval_AtA_times_u(N,v,u);
    }
  vBv=vv=0;
  for(i=0;i<N;i++) { vBv+=u[i]*v[i]; vv+=v[i]*v[i]; }
  printf("%0.9f\n",sqrt(vBv/vv));
  return 0;
}
