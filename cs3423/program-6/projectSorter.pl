#!/usr/bin/perl -w
use strict;

#if($#ARGV == -1)
#{
#    die "Not enough args";
#}

my $dir = "/home/max/git/schoolCode/cs3423/program-6/DataB";

if (! -d $dir)
{
    die "Not a directory\n";
}

my $dirName;

my @filesArr = glob($dir);

foreach my $file (@filesArr)
{
    my $assignment = $file;
    if($assignment =~ m/^proj/)
    {
        $assignment =~ s/^proj|\..*$//g;
        $dirName = join("","assignment",$assignment);
    }
    else
    {
        $dirName = "misc";
    }
    if (! -d $dirName)
    {
        print `mkdir $dirName`;
    }
    print `cp $dir/$file $dirName`;
}