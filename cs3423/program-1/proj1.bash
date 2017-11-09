#!/bin/bash
#echos the menu of commands
echo "Enter one of the following actions or press CTRL-D to exit"
echo "C - create a customer file"
echo "P - accept a customer file"
echo "F - find customer by apartment number"
#starts the loop
while read -p "Input Command: " input
do
    #reads through the input
    case "$input" in
        [Cc])
            #creates the customer
            bash create.bash
            ;;
        [Pp])
            #pays the customer
            read -p "Enter the customer email: " recCustEmail
            read -p "Enter the ammount you want to transfer: " transAmmnt
            count=0
            #checks to see if the customer exists
            for fn in $(grep -r -l "$recCustEmail" Data);do
                count=$(($count+1))
            done
            if [ $count -eq 0 ]
            then
                echo "Error: customer does not exist"
            else
                bash pay.bash $transAmmnt <"Data/$recCustEmail"
            fi
            ;;
        [Ff])
            #Finds the customer at an appartment
            read -p "Enter the Apartment Number: " aptNum
            count=0
            #checks to see if the customer exists
            for fn in $(grep -r -l "$aptNum" Data);do
                bash find.bash<$fn;
                count=$(($count+1))
            done
            if [ $count -eq 0 ]
            then
                echo "Error: apartment number not found"
            fi
            ;;
        *)
            #defaults to error invalid action value
            echo "Error: invalid action value"
            ;;
    esac
done