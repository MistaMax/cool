#!/bin/bash

# 3a
read -p "enter two numbers: " number_one number_two
echo $(($number_one * $number_two))

#3b

if [ $# -ne 2 ]
then
    echo "usage: $0 [number1] [number2]"
    #exit 1
fi

echo $(($2 * $1))

# 3c
sum=0
product=1

while read input
do
    sum=$(($sum + $input))
    product=$(($product * $input))
done
echo "Sum is: $sum"
echo "Product is: $product"

# 3d

count=0

while read line
do
    if [ $line = "findme" ]
    then
        echo $count
    fi
    count=$(($count+1))
done