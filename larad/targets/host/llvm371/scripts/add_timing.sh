filename=${1%.*}
echo $filename
#funcname = basename($filename)
funcname=$(basename "$filename")
echo $funcname
cp $filename\_main.c main_notiming.c
cp $1 function.c
php /opt/lara-tools/larad/targets/host/llvm371/scripts/add_timing.php main_notiming.c $funcname
rm main_notiming.c
cp $filename.h include.h

#/opt/pluto-0.11.4/polycc function.c --parallel
#mv function.pluto.c function.c
