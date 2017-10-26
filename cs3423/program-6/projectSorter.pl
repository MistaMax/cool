#!/usr/bin/perl -w
use strict;

#if($#ARGV == -1)
#{
#    die "Not enough args";
#}

my $dir = $ARGV[0];

if(!(-d $dir))
{
    die "Not a directory\n";
}

my @fNArr = glob($dir . /*);

foreach my $fN (@fNArr)
{
    my $end = $fN;
    my $dirName = "misc";
    if($end =~ m/^proj/)
    {
        $end =~ s/^proj|\..*$//g;
        $dirName = join("","assignment",$end);
    }
    if(!(-d $dir))
    {
        print `mkdir $dirName`;
    }
    print `cp $dir/$fN $dirName`;
}
