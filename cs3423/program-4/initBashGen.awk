#creates the base of the generated bash script
BEGIN{
    print "#!/bin/bash\n"
    FS = ","
}
#sets up the data to be exported
{
    l = split($2,name," ")
    print "data=\""$0"\""
    print "email=\""$1"\""
    print "fullName=\""$2"\""
    print "title=\""$3"\""
    print "ammLeft="$5-$4
    print "lastName=\""name[l]"\""
    print "export email fullName title ammLeft lastName"
}