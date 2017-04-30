#!/bin/sh

rm -f main_wtiming.s

# CoSy does not alow importing the CCMIR

# Compiles the main with no optimization
/opt/reflectc/reflectc main_wtiming.c reflectc_runoptims.xml -gen=mb -v0 -I /opt/reflectc/include "-argv=([])" -o main_wtiming.s


