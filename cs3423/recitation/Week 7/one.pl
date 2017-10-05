#!/usr/bin/perl -w
use strict;

my @array = (1..5);
foreach (@array)
{
    print "$_\n";
}
my $number = $#array+1;
print "Num of elements = $number\n"