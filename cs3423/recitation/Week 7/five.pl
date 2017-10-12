#!/usr/bin/perl -w
use strict;

if(!defined($ARGV[0]))
{
    die "Arg not defined";
}

open(IN, "<", $ARGV[0]) or die "Couldn't open input file\n";

my $n = 1;
my $var;
while ($var = <IN>){
    if($var eq "findme\n"){
        print "$n\n";
        last;
    }
    $n++;
}