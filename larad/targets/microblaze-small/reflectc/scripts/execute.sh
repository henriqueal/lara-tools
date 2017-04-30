#!/bin/sh

rm -rf info.dat

# AREA OPTIMIZED
timelimit -t1 microblaze-sim -area_optimized -o info.dat code_timing

# PERFORMANCE OPTIMIZED
#/opt/microblaze-ace/microblaze-sim -o info.dat application

#cat info.dat
