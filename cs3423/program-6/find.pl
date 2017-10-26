#!/usr/bin/perl
use strict;

if($#ARGV == -1){
    die "No args found\n";
}

if($ARGV[0] eq "-i")
{
    my @files;
    for(my $i = 2;$i <= $#ARGV;$i++)
    {
        $files[$i-2] = $ARGV[$i];
    }
    foreach my $fileName (@files)
    {
        #print "\n\n$fileName\n\n";
        if($fileName !~ m/$ARGV[1]/)
        {
            my $tick = 0;
            open(my $file, "<", $fileName) or die "Couldnt open file\n";
            while(my $line = <$file>)
            {
                if($line =~ m/$ARGV[1]/)
                {
                    $tick++;
                    last;
                }
            }
            close $file;
            if($tick==0)
            {
                print "$fileName\n";
            }
        }
    }
}
else
{
    my @files;
    for(my $i = 1;$i <= $#ARGV;$i++)
    {
        $files[$i-1] = $ARGV[$i];
    }
    foreach my $fileName (@files)
    {
        if($fileName =~ m/$ARGV[0]/)
        {
            print "$fileName\n";
        }
        else
        {
            open(my $file, "<", $fileName) or die "Couldnt open file\n";
            while(my $line = <$file>){
                if($line =~ m/$ARGV[0]/){
                    print "$fileName : $line";
                    last;
                }
            }
            close $file;
        }
    }
}
