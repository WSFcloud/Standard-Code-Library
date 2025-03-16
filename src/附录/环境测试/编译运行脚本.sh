#!/bin/bash
g++ $1.cpp -o $1 -O2 -std=c++20 -Wall -D__LOCAL__ -g
if [ $? -eq 0 ]; then
    ./$1
fi