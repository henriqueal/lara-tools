
int Ack(int M,  N) {
    /*if (M == 0) return( N + 1 );
    if (N == 0) return( Ack(M - 1, 1) );
    return( Ack(M - 1, Ack(M, (N - 1))) );
*/
    return 2048;
}

void DSP_neg32_c
(
    int x,
    int * r

)
{
   r[0] = Ack(3,x);
}




