#!/bin/sh

rm -rf function.optim.s function.optim.o application modsi3.o muldi3.o mulsi3.o

# AREA OPTIMIZED 
#/opt/clang+llvm-3.3-Ubuntu-13.04-x86_64-linux-gnu/bin/llc -march=mblaze -mcpu=mblaze3 -O3 code_timing.optim.ll -o code_timing.optim.s

# PERFORMANE OPTIMIZED
timelimit -t1 /opt/clang+llvm-3.3-Ubuntu-13.04-x86_64-linux-gnu/bin/llc -march=mblaze -mcpu=mblaze3 -mattr=+patcmp,+barrel,+div,+mul,+fpu -O3 function.optim.ll -o function.optim.s

timelimit -t1 /opt/microblaze-ace/microblaze-cc -o application function.optim.s main_wtiming.s /opt/lara-tools/larad/targets/microblaze/mulsi3.S /opt/lara-tools/larad/targets/microblaze/muldi3.S /opt/lara-tools/larad/targets/microblaze/modsi3.S


#GCC 2x faster than CLANG at assembly the code! Why?! But causes the compilation to fail around 20% of the times with some kernels...
#gcc code_timing.optim.s -o code_timing -lm
