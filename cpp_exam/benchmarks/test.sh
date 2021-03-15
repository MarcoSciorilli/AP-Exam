#!/bin/bash
mkdir results
c++ -O3 -std=c++14 -Wall -Wextra -o benchmark.x benchmark.cc
./benchmark.x
python3 analisys.py
