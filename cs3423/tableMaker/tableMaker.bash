#!/bin/bash
#echos the menu of commands
echo "Enter one of the following actions or press CTRL-D to exit"
echo "C - create a Table"

#starts the loop
while read -p "Input Command: " input
do
    #reads through the input
    case "$input" in
        [Cc])
            read -p "What is the name of the table: " tblName
            read -p "How many Rows: " rowC
            read -p "How many Collumns: " colC
            
            bash tableCreate.bash $rowC $colC $tblName < "tables/$tblName.txt"
            ;;
        *)
            #defaults to error invalid action value
            echo "Error: invalid action value"
            ;;
    esac
done