BEGIN {
    sum = 0
    count = 0
}

{
    if(match($3, user)){
        print $0
        if ($NF ~ /\.zip$/){
            sum += $5
            count++
        }
    }
}
END {
    print "Zip statistics for "user":"
    avg = sum/count
    print "Count "count" | Total size "sum" | Average size "avg
}
#ls -l | awk -f awk3.awk -v 'user=root'