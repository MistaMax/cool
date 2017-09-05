#!/bin/bash

echo "Enter one of the following actions or press CTRL-D to exit"
echo "C - create a customer file"
echo "P - accept a customer file"
echo "F - find customer by apartment number"
cmnd=0
while true
do
    read -p "Input Command: " input
    case "$input" in
        [Cc])
            read -p "Enter your new customer email: " custEmail
            read -p "Enter the customer's full name: " custFirstName custLastName
            read -p "Enter the apartment number: " apptNum
            read -p "Enter the monthly rent: " rentAmnt
            read -p "Enter the next due date: " rentDueDt
            accBal=0
            {
                echo "$custEmail $custFirstName $custLastName"
                echo "APT-$apptNum $accBal $rentAmnt $rentDueDt"
            }>$custEmail
            ;;
        [Pp])
            read -p "Enter the customer email: " recCustEmail
            read -p "Enter the ammount you want to transfer: " transAmmnt
            find -r $recCustEmail
            ;;
        [Ff])
            cmnd=3;;
    esac
done