#!/bin/sh

rm -f main_wtiming.s
# CoSy does not alow importing the CCMIR

# Compiles the main with no optimization
# NOTE: DO NOT USE TIMELIMIT HERE! IN CASE OF USING TIMELIMIT, THERE IS THE RISK THE CHILD PROCESS (cosy_mb.bin) DOES NOT TERMINATE!
/opt/reflectc/reflectc main_wtiming.c reflectc_runoptims.xml -gen=mb -v0 -I /opt/reflectc/include "-argv=([])" -o main_wtiming.s


