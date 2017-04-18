#!/bin/sh

rm -rf function.ll main_wtiming.ll main_wtiming.s
 
timelimit -t60 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/clang function.c -emit-llvm -S -o function.ll -march=native -fopenmp=libomp -I /opt/llvm-openmp-3.7.1/include

# Generate ASM for main, as it only needs to be done a single time
timelimit -t60 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/clang main_wtiming.c -emit-llvm -S -o main_wtiming.ll -march=native
timelimit -t60 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/llc -mcpu=native -fp-contract=fast main_wtiming.ll -o main_wtiming.s
#timelimit -t60 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/clang -S -o main_wtiming.s main_wtiming.c
