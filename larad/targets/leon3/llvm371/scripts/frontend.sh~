#!/bin/sh

rm -rf function.ll main_wtiming.ll main_wtiming.s

# NOTE: If I put '-cpu=v8' here it does not recognize it for some reason. But it works with the 'llc' tool...
#timelimit -t10 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/clang --target=sparc-unknown-none-elf function.c -emit-llvm -S -o function.ll

timelimit -t10 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-14.04/bin/clang --target=sparc-unknown-none-elf function.c -emit-llvm -S -o function.ll


# Generate ASM for main, as it only needs to be done a single time
#timelimit -t1 /opt/sparc-elf-4.4.2/bin/sparc-elf-gcc -mcpu=v8 -S -o main_wtiming.s main_wtiming.c
#timelimit -t25 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/clang --target=sparc-unknown-none-elf main_wtiming.c -emit-llvm -S -o main_wtiming.ll
timelimit -t25 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-14.04/bin/clang --target=sparc-unknown-none-elf main_wtiming.c -emit-llvm -S -o main_wtiming.ll

#timelimit -t25 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/llc -march=sparc -mcpu=v8 main_wtiming.ll -o main_wtiming.s
timelimit -t25 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-14.04/bin/llc -march=sparc -mcpu=v8 main_wtiming.ll -o main_wtiming.s

# Maybe does the same as the two above lines, but I am not sure that it targets SPARC V8 specifically
#timelimit -t1 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/clang -target sparc -S -o main_wtiming.s main_wtiming.c
