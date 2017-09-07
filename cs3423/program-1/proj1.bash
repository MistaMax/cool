#!/bin/bash

echo "Enter one of the following actions or press CTRL-D to exit"
echo "C - create a customer file"
echo "P - accept a customer file"
echo "F - find customer by apartment number"
cmnd=0
while read -p "Input Command: " input
do
    #read -p "Input Command: " input
    case "$input" in
        [Cc])
            read -p "Enter your new customer email: " custEmail
            read -p "Enter the customer's full name: " custFirstName custLastName
            read -p "Enter the apartment number: " apptNum
            read -p "Enter the monthly rent: " rentAmnt
            read -p "Enter the next due date: " rentDueDt
            accBal=0
            count=0
            for fn in $(grep -r -l "$custEmail" Data);do
                count=$(($count+1))
            done
            if [ $count -eq 0 ]
            then
                {
                    echo "$custEmail $custFirstName $custLastName"
                    echo "$apptNum $accBal $rentAmnt $rentDueDt"
                }>"Data/$custEmail"
            else
                echo "Email already exists"
            fi
            ;;
        [Pp])
            read -p "Enter the customer email: " recCustEmail
            read -p "Enter the ammount you want to transfer: " transAmmnt
            count=0
            for fn in $(grep -r -l "$recCustEmail" Data);do
                count=$(($count+1))
            done
            if [ $count -eq 0 ]
            then
                echo "Email does not exist"
            else
                bash pay.bash $transAmmnt <"Data/$recCustEmail"
            fi
            ;;
        [Ff])
            read -p "Enter the Apartment Number: " aptNum
            count=0
            for fn in $(grep -r -l "$aptNum" Data);do
                bash find.bash<$fn;
                count=$(($count+1))
            done
            if [ $count -eq 0 ]
            then
                echo "Not Found"
            fi
            ;;
    esac
done