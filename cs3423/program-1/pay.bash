
read email fName lName
read aptNum bal rate dDate

bal=$(($bal+$1))
{
    echo "$email $fName $lName"
    echo "$aptNum $bal $rate $dDate"
}>"Data/$email"