BEGIN {
    print "<table>"
    FS = ","
}
{
    print "<tr>"

    for(i = 1; i <= NF; i++)
        print "<td>"$i"</td>"
    print "</tr>"
}
END {
    print "</table>"
}