#!/bin/sh
g++ concur8.cc -O2 -o /soup -std=c++20 -march=native
/soup | ssh -i /do do@COLLECTOR_HOST "cat > '$(date --iso-8601=ns)'"
