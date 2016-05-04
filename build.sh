#!/bin/bash
rm ./build 
mkdir ./build
cd ./build
cmake  ..
cp ../Makefile ./
cp ../HelloX.c ./
make

