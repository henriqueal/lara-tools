int ackermann(int M, int N) {
    if (M == 0) return( N + 1 );
    if (N == 0) return( ackermann(M - 1, 1) );
    return( ackermann(M - 1, ackermann(M, (N - 1))) );
}



