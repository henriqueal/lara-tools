#!/bin/sh

rm -rf function.optim.ll
 
timelimit -t1 /opt/clang+llvm-3.3-Ubuntu-13.04-x86_64-linux-gnu/bin/opt $1 function.ll -S -o function.optim.ll
