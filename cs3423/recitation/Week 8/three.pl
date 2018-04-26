#!/usr/bin/perl -w
use strict;

open(my $IN, "<", $ARGV[0]) or die "Could not open input file";
my $line;

while ($line = <$IN>)
{
    $line =~ s/\(?(\d{3})[^\w]*(\d{3})[^\w]*(\d{4})/($1)-$2-$3/g;
    print "$line";
}