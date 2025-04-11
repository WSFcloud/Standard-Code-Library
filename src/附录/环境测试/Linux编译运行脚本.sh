#!/bin/bash
g++ -std=c++20 -g -Wall -Wextra -DLOCAL $1.cpp -o $1 
if [ $? -eq 0 ]; then
    ./$1
fi