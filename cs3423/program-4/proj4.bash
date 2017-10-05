#!/bin/bash
#checks to see if the emails directory exists
if [ -d "Emails" ]; then
    rm -rf "Emails"
fi
#make the emails directory
mkdir "Emails"
#main section of code
{
    while read inp
    do
        #uses awk script to extrat the variables and generate a bash file with the variables in them then makes it export said variables
        echo "$inp" | awk -f initBashGen.awk -v "date=$1" >gForm.bash
        #exports the variables from gform and stores them in this bash file
        . ./gForm.bash
        #uses the values created by gform to generate a sed script
        {
            echo "s/FULLNAME/$fullName/"
            echo "s/NAME/$lastName/"
            echo "s/AMOUNT/$ammLeft/"
            echo "s/DATA/$data/"
            echo "s/TITLE/$title/"
            echo "s/EMAIL/$email/"
        }>gFormEmail.sed
        #this massive line of code essentially replaces the need for sed and uses the template to form a propper email
        if [ $ammLeft -gt 0 ]; then
            sed -f gFormEmail.sed template.txt >Emails/$email
        fi
    done
}<p4Customer.txt #this allows the while loop to read out the lines in the customer txt file