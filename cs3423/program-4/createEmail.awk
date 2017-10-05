{
    gsub("FULLNAME", fullName)
    gsub("EMAIL", email)
    gsub("TITLE", title)
    gsub("NAME", lastName)
    gsub("DATE", date)
    gsub("DATA", data)
    gsub("AMOUNT", ammLeft)
    print $0
}