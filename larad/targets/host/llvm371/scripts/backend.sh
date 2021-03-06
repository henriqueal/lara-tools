#!/bin/sh

# Porque e que o LLC nao suporta '-march=native'?

rm -rf function.optim.s application

# Parece que gera o mesmo codigo assembly com ou sem o -O3
# Suponho que seja porque a LLVM IR vem modificada pelo LLVM OPT, e então o LLVM LLC já não aplica o -O3 à IR, que já entra optimizada (pelo OPT) 
timelimit -t10 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/llc -mcpu=native -fp-contract=fast function.optim.ll -o function.optim.s
#timelimit -t1 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/llc -mcpu=native function.optim.ll -o function.optim.s


timelimit -t10 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/clang -o application function.optim.s main_wtiming.s -lm -fopenmp=libomp -L /opt/llvm-openmp-3.7.1/lib

#GCC 2x faster than CLANG at assembly the code! Why?! But causes the compilation to fail around 20% of the times with some kernels...
#gcc code_timing.optim.s -o code_timing -lm

