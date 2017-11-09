BEGIN{
    #initializes everything
    sex = ""
    date = ""
    email = ""
    lastName = ""
    name = ""
    flightNum = ""
    seats = 0
    cost = 0
    totCost = 0
    flightAmm = 0
    flightSeat[200]
    flightName[200]
}
#checks for ENDCUST
match($1, "ENDCUST"){
    #Ends the table with the total overall
    printf "|------------|----------|-----|----------|\n"
    printf "|            |          |%-5s|%10.2f|\n", "Total", totCost
    printf "==========================================\n\n\n"
    sex = ""
    date = ""
    email = ""
    lastName = ""
    name = ""
    flightNum = ""
    seats = 0
    cost = 0
    totCost = 0
}
#checks for cust
!match($1,"ENDCUST") && match($1,"CUST"){
    #Table header
    printf "==========================================\n"
    printf "|%-12s|%-10s|%-5s|%-10s|\n", "Name", "Flight", "Seats", "Total Cost"
    printf "|------------|----------|-----|----------|\n"
    #scanning text file data
    sex = $2
    date = $3
    email = $4
    c=NF
    lastName = $c
    c--
    name = $i" "lastName
}
#checks for RESERVE
match($1,"RESERVE"){
    flightNum = $2
    seats = $3
    cost = seats*$4
    printf "|%-12s|%-10s|%5i|%10.2f|\n", lastName, flightNum, seats, cost
    totCost += cost
    #add ending table code
    if(flightAmm > 1){
        #if it is not the first call of reservation
        if(!(flightNum in flightName)){
            #if flight num does not exist
            flightName[flightAmm] = flightNum
            flightSeat[flightAmm] = seats
            flightAmm++
        }
        else
        {
            #if flight num does exist
            for(i = 1; i < flightAmm; i++){
                if(match(flightName[i],flightNum)){
                    flightSeat[i] += seats
                    break
                }
            }
        }
    }
    else
    {
        #first call of the reservation
        flightName[flightAmm] = flightNum
        flightSeat[flightAmm] = seats
        flightAmm++
    }
}
END{
    #prints the table containing flight numbers and seats on the flights
    printf "=========================\n"
    printf "|%10s|%12s|\n", "Flight Num", "Num of Seats"
    printf "|----------|------------|\n"
    for(i = 0; i < flightAmm; i++){
        printf "|%10s|%12i|\n", flightName[i], flightSeat[i]
    } 
    printf "=========================\n"
}