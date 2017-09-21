read -p "Enter your new customer email: " custEmail
read -p "Enter the customer's full name: " custFirstName custLastName
read -p "Enter the apartment number: " apptNum
read -p "Enter the monthly rent: " rentAmnt
read -p "Enter the next due date: " rentDueDt
accBal=0
count=0
#checks to see if customer exists
for fn in $(grep -r -l "$custEmail" Data);do
    count=$(($count+1))
done
if [ $count -eq 0 ]
then
#creates the file
{
    echo "$custEmail $custFirstName $custLastName"
    echo "$apptNum $accBal $rentAmnt $rentDueDt"
}>"Data/$custEmail"
else
    echo "Error: customer already exists"
fi