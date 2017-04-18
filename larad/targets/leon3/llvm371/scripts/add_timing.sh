filename=${1%.*}
echo $filename
cp $1 function.c
cp $filename.h include.h

cp $filename\_main.c main_notiming.c
php /opt/lara-tools/larad/targets/leon3/llvm371/scripts/add_timing.php main_notiming.c $funcname
rm main_notiming.c

