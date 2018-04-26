#!/usr/bin/perl -w
use strict;

my %idHash;
open(my $IN, "<:encoding(UTF-8)", $ARGV[0]) or die "Could not open input file";
my $line;
my $id;
my $count;
while ($line = <$IN>)
{
    ($id, $count) = split(" ", $line);
    $idHash{$id} += $count;
}

foreach my $key (keys %idHash)
{
    print "$key $idHash{$key}\n";
}