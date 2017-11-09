#!/usr/bin/perl -w
use strict;

my @valid_list;
my @invalid_list;

foreach ( @ARGV )
{
    if ( -f $_)
    {
        push @valid_list, $_;
    }
    else
    {
        push @invalid_list, $_;
    }
}

print "Valid list:\n";
print join("\n",sort(@valid_list));
print "\n";

print "Invalid list:\n";
print join("\n",reverse(sort(@invalid_list)));
print "\n";