#!/bin/bash
echo -n "SOURCES :=" > sources.mk ;
find src -type f -name *.c | awk '{print "	" $0 " \\"}' >> sources.mk ;