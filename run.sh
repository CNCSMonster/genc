#!/bin/bash


# compile to bc
clang -I /snap/klee/9/usr/local/include -emit-llvm -c -g -O0 -Xclang -disable-O0-optnone a.c genc.inc
# run klee
klee a.bc
