#!/bin/sh

rm -rf info.dat

# AREA OPTIMIZED
#microblaze-sim -area_optimized -o info.dat code_timing

# PERFORMANCE OPTIMIZED
timelimit -t1 /opt/microblaze-ace/microblaze-sim -o info.dat application

#cat info.dat
