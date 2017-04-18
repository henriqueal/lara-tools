cp /opt/lara-tools/larad/reflectc_runoptims.xml .

/opt/lara-tools/larad/targets/microblaze/llvm330/scripts/cleanall.sh
/opt/lara-tools/larad/targets/microblaze/llvm330/scripts/add_timing.sh $1
/opt/lara-tools/larad/targets/microblaze/llvm330/scripts/frontend.sh
/opt/lara-tools/larad/targets/microblaze/llvm330/scripts/opt.sh $2
/opt/lara-tools/larad/targets/microblaze/llvm330/scripts/backend.sh
/opt/lara-tools/larad/targets/microblaze/llvm330/scripts/execute.sh

rm reflectc_runoptims.xml

cat info.dat
