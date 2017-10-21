#!/usr/bin/perl -w
use strict;

print "Enter your age:\n";

my $age = <STDIN>;
my $year = `date +"%Y"`;

my $birthyear = $year - $age;
print "You were born in $birthyear\n";