#!/bin/bash
echo -n "SOURCES :=" > sources.mk ;
find src -type f -name *.c | awk '{print "	" $0 " \\"}' >> sources.mk ;
echo -n "HEADERS :=" > headers.mk ;
find include -type f -name *.h | awk '{print "	" $0 " \\"}' >> headers.mk ;