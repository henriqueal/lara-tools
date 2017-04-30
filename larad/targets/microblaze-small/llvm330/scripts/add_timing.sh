filename=${1%.*}
echo $filename
cp $filename\_main.c main_wtiming.c
cp $1 function.c
cp $filename.h include.h

