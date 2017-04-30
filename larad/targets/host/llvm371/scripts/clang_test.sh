/opt/lara-tools/larad/targets/host/llvm371/scripts/cleanall.sh
/opt/lara-tools/larad/targets/host/llvm371/scripts/add_timing.sh $1


rm -rf function.ll main_wtiming.s function.optim.s application

# Generate optimized ASM for function
timelimit -t60 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/clang "$2" -S -o function.optim.s function.c

# Generate ASM for main, as it only needs to be done a single time
timelimit -t60 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/clang -S -o main_wtiming.s main_wtiming.c

timelimit -t1 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/clang -o application function.optim.s main_wtiming.s -lm

/opt/lara-tools/larad/targets/host/llvm371/scripts/execute.sh
cat info.dat
