#!/bin/sh

rm -rf function.optim.s application

# Parece que gera o mesmo codigo assembly com ou sem o -O3
# Suponho que seja porque a LLVM IR vem modificada pelo LLVM OPT, e então o LLVM LLC já não aplica o -O3 à IR, que já entra optimizada (pelo OPT) 
#timelimit -t5 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/llc -march=sparc -mcpu=v8 function.optim.ll -o function.optim.s
timelimit -t5 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-14.04/bin/llc -march=sparc -mcpu=v8 function.optim.ll -o function.optim.s

#timelimit -t1 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/llc -march=sparc -mcpu=v8 -O3 function.optim.ll -o function.optim.s

timelimit -t5 /opt/sparc-elf-4.4.2/bin/sparc-elf-gcc -mcpu=v8 -o application function.optim.s main_wtiming.s -lm


#timelimit -t1 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10/bin/clang -target sparc -o application function.optim.s main_wtiming.s -lm
#	ERROR:
#	/usr/bin/ld: /tmp/function-c54c4b.o: Relocations in generic ELF (EM: 2)
#	/tmp/function-c54c4b.o: error adding symbols: File in wrong format
#	collect2: error: ld returned 1 exit status
#	clang-3.7: error: linker (via gcc) command failed with exit code 1 (use -v to see invocation)
