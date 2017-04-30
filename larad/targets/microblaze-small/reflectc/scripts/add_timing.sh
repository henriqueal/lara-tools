rm -r main_wtiming.c function.c include.h

filename=${1%.*}
echo $filename
cp $filename\_main.c main_wtiming.c
cp $1 function.c
cp $filename.h include.h

