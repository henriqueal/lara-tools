#!/bin/sh

rm -rf info.dat

# timeout aqui faz isto nao funcionar... porque?
#timelimit -t10 /opt/tsim2-leon3-eval/tsim/linux-x64/tsim-leon3 -c /opt/lara-tools/larad/targets/leon3/llvm371/scripts/tsim_input.txt -logfile info.dat application

timelimit -t10 /opt/tsim-eval/tsim/linux-x64/tsim-leon3 -c /opt/lara-tools/larad/targets/leon3/llvm371/scripts/tsim_input.txt -logfile info.dat application


#cat info.dat

