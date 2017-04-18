/opt/lara-tools/larad/targets/host/llvm371/scripts/cleanall.sh
/opt/lara-tools/larad/targets/host/llvm371/scripts/add_timing.sh $1
/opt/lara-tools/larad/targets/host/llvm371/scripts/frontend.sh
/opt/lara-tools/larad/targets/host/llvm371/scripts/opt.sh "$2"
/opt/lara-tools/larad/targets/host/llvm371/scripts/backend.sh
/opt/lara-tools/larad/targets/host/llvm371/scripts/execute.sh
cat info.dat
