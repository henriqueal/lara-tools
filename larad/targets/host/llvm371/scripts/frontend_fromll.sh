#!/bin/sh

rm -rf main_wtiming.s

#timelimit -t1 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/clang function.c -emit-llvm -S -o function.ll

# Generate ASM for main, as it only needs to be done a single time
timelimit -t1 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/clang -S -o main_wtiming.s main_wtiming.c

