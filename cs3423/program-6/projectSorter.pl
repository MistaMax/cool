#!/usr/bin/perl -w
use strict;
#makes sure that there is an argument
if($#ARGV == -1)
{
    die "Not enough args";
}

my $dir = $ARGV[0];
#makes sure the directory exists
if(!(-d $dir))
{
    die "Not a directory\n";
}
#reads in all the file names from that directory
my @fNArr = glob("$dir/*");
#loop to read all the file names and sort them
foreach my $fN (@fNArr)
{
    #editing the file name to be readable by the rest of my code
    my $end = $fN;
    my $dirName = "misc";
    $end =~ s/^$dir\///g;
    #checks to see if file name begins with proj and sets the directory name accordingly
    if($end =~ m/^proj/)
    {
        $end =~ s/^proj|\..*$//g;
        $dirName = join("","assignment",$end);
    }
    #checks to see if the generated directory name exists, if it doesnt make a directory
    if(!(-d $dirName))
    {
        print `mkdir $dirName`;
    }
    #moves the file into its designated directory
    print `mv $fN $dirName`;
}
