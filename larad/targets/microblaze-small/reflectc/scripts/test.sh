/opt/lara-tools/larad/targets/microblaze/reflectc/scripts/cleanall.sh
/opt/lara-tools/larad/targets/microblaze/reflectc/scripts/add_timing.sh $1
/opt/lara-tools/larad/targets/microblaze/reflectc/scripts/frontend.sh
/opt/lara-tools/larad/targets/microblaze/reflectc/scripts/opt.sh $2
/opt/lara-tools/larad/targets/microblaze/reflectc/scripts/backend.sh
/opt/lara-tools/larad/targets/microblaze/reflectc/scripts/execute.sh
cat info.dat
