#!/usr/bin/perl -w
use strict;

if($#ARGV < 2){
    die "not enough arguments\n";
}

my $a;
my $b;
my $c;

($a, $b, $c) = @ARGV;

print "\$a = $a\n";
print "\$b = $b\n";
print "\$c = $c\n";