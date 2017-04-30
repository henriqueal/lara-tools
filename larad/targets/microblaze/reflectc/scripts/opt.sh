#!/bin/sh

rm -rf function.optim.s

#killall -9 cosy_mb.bin
echo $1
compilerseq=$1
toreplace=" "
replacement='", "'
compilerseq=\"$(echo "$1" | sed -e "s/$toreplace/$replacement/g")\"
echo $compilerseq

# NOTE: DO NOT USE TIMELIMIT HERE! IN CASE OF USING TIMELIMIT, THERE IS THE RISK THE CHILD PROCESS (cosy_mb.bin) DOES NOT TERMINATE!
/opt/reflectc/reflectc function.c reflectc_runoptims.xml -gen=mb -v0 -I /opt/reflectc/include "-argv=([$compilerseq])" -o function.optim.s

# The REFLECTC CoSy module may still be working after the main reflectc tool exits
# It seems that by putting the call to the driver in other shell script file I do not need this any more
#  sleep 0.1

