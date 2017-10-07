#!/usr/bin/perl -w
use strict;

foreach my $arg (@ARGV){
    if(-d $arg){
        print "$arg\n";
        `ls -l $arg`;
    }
}