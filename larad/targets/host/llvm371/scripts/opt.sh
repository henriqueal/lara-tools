#!/bin/sh

rm -rf function.optim.ll
 
#timelimit -t1 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/opt $1 -ffp-contract=fast function.ll -S -o function.optim.ll
timelimit -t10 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/opt $1 function.ll -S -o function.optim.ll

