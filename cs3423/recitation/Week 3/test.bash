#!/bin/bash

count=1
while read input
do
    if [ $(($count % 2)) = 0 ]
    then
        echo "$input"
    fi
    count=$(($count + 1))
done
if [ $count -gt 10 ]
then
    echo "big"
else
    echo "small"
fi