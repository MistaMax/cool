#!/usr/bin/perl -w
use strict;
#ensures that there are enough args to run the function
if($#ARGV < 2){
    die "No args found\n";
}

if($ARGV[0] eq "-i")# runs this to read out the inverse of the regex expression
{
    my @files;

    for(my $i = 2;$i <= $#ARGV;$i++)# reads in all the files and puts it into the files array
    {
        $files[$i-2] = $ARGV[$i];
    }

    foreach my $fileName (@files)#reads through the files array and analyzes the files
    {
        #checks to see if the regex is in the name
        if($fileName !~ m/$ARGV[1]/)
        {
            #makes a variable that ticks every time a regex expression is met
            my $tick = 0;
            #opens the file to be read
            open(my $file, "<", $fileName) or die "Couldnt open file\n";
            #while loop that increments tick if the regex is matched within the file
            while(my $line = <$file>)
            {
                if($line =~ m/$ARGV[1]/)
                {
                    $tick++;
                    last;
                }
            }
            #closes the file
            close $file;
            #returns the file name if nothing was found in the regex
            if($tick==0)
            {
                my @direcNames = split("/",$fileName);
                my $namesies = $direcNames[$#direcNames];
                print "$namesies\n";
            }
        }
    }#end file reading loop
}
else
{
    my @files;
    for(my $i = 1;$i <= $#ARGV;$i++)#reads the files into the files array
    {
        $files[$i-1] = $ARGV[$i];
    }

    foreach my $fileName (@files)#loops through the file names
    {

        if($fileName =~ m/$ARGV[0]/)#if the regex is met in the name then return the name of the files
        {
            my @direcNames = split("/",$fileName);
            my $namesies = $direcNames[$#direcNames];
            print "$namesies\n";
        }
        else
        {
            #reads through the file to check for the regex expression
            open(my $file, "<", $fileName) or die "Couldnt open file\n";
            while(my $line = <$file>){
                #prints the line if the regex is met
                if($line =~ m/$ARGV[0]/){
                    my @direcNames = split("/",$fileName);
                    my $namesies = $direcNames[$#direcNames];
                    print "$namesies : $line";
                    last;
                }
            }
            #closes the file
            close $file;
        }
    }
}
