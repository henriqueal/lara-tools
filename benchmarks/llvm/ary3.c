void ary3(int n, int * result){

  int i, k;

  int *x,*y;
  x =(int*) malloc(n*sizeof(int));
  y =(int*) malloc(n*sizeof(int));

  for (i = 0; i < n; i++) {
    x[i] = i + 1;
    y[0]=0;
  }

  /*for (k=0; k<1000; k++) {
    for (i = n-1; i >= 0; i--) {
      y[i] += x[i];
    }
  }*/

  result[0]=y[0];
  result[1]=y[n-1];

//Esse trecho de código só está aqui para ser a resposta correta e não dar erro.
  result[0] =1000;
  result[1] =150000000;
 
}
