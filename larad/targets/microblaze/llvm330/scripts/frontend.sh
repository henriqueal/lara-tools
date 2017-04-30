#!/bin/sh

rm -rf function.ll main_wtiming.s
 
timelimit -t1 /opt/clang+llvm-3.3-Ubuntu-13.04-x86_64-linux-gnu/bin/clang -target mblaze-unknown-none-elf function.c -emit-llvm -S -o function.ll

# Generate ASM for main, as it only needs to be done a single time
# TODO: use clang + llc instead of GCC
/opt/reflectc/reflectc main_wtiming.c reflectc_runoptims.xml -gen=mb -v0 -I /opt/reflectc/include "-argv=([])" -o main_wtiming.s
