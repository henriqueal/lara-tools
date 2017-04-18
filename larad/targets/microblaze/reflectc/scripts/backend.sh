#!/bin/sh

rm -rf function.optim.o main_wtiming.o application modsi3.o muldi3.o mulsi3.o

timelimit -t1 /opt/microblaze-ace/microblaze-cc -o application function.optim.s main_wtiming.s /opt/lara-tools/larad/targets/microblaze/mulsi3.S /opt/lara-tools/larad/targets/microblaze/muldi3.S /opt/lara-tools/larad/targets/microblaze/modsi3.S



#GCC 2x faster than CLANG at assembly the code! Why?! But causes the compilation to fail around 20% of the times with some kernels...
#gcc code_timing.optim.s -o code_timing -lm
