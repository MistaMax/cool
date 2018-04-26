#!/usr/bin/perl -w
use strict;

open(my $IN, "<", $ARGV[0]) or die "Could not open input file";
my $line;

while ($line = <$IN>)
{
    if($line =~ m/<h\d>.*[pP]roject.*<\/h\d>/)
    {
        $line = "<strong>$1</strong>";
        print $line;
    }
    else
    {
        print $line;
    }
}