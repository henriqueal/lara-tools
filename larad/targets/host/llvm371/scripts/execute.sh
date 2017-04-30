#!/bin/sh

rm -rf info.dat

#taskset -c 0 timelimit -t60 ./application > info.dat
timelimit -t60 ./application > info.dat
#cat info.dat

