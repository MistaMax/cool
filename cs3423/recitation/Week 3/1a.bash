#!/bin/bash
# 1.a

echo "Your current directory $PWD, your home directory $HOME"

# 1.b

echo $(($# * 2))

# 1.c

one=1
two=2
#. can be replaced with source
. 1d.bash

echo $one
echo $two