#!/usr/bin/perl -w
use strict;
#checking if the emails directory exists, if so, delete it and its contents
if ( -d "Emails"){
  system("rm","-rf", "Emails");
}
#creates the Emails directory
system("mkdir","Emails");
#opens the customer data file
my $filename = "p5Customer.txt";
open(my $fh, '<:encoding(UTF-8)', $filename) or die "Could not open file '$filename' $!";
#Loop to read the file
while (my $row = <$fh>) {
  chomp $row;
  #sets up all the variables read from the line
  my $data = $row;
  my @arr = split(/,/,$row);
  my $email = $arr[0];
  my $name = $arr[1];
  my @sepName = split(/ /,$name);
  my $lastName = $sepName[$#sepName];
  my $title = $arr[2];
  my $owed = $arr[4] - $arr[3];
  my $date = $ARGV[0];
  #creates an email if someone owes the owner money
  if($owed > 0){
    #opens the template and creates a write file
    open(my $template, '<', "template.txt") or die "Could not open file template.txt $!";
    open(my $write, '>', "Emails/$email") or die "Could not write file $!";
    #reads the template and replaces all the strings with the values above using regex and writes to the file
    while(my $tmpRow = <$template>){
      $tmpRow =~ s/EMAIL/$email/g;
      $tmpRow =~ s/FULLNAME/$name/g;
      $tmpRow =~ s/NAME/$lastName/g;
      $tmpRow =~ s/TITLE/$title/g;
      $tmpRow =~ s/AMOUNT/$owed/g;
      $tmpRow =~ s/DATE/$date/g;
      $tmpRow =~ s/DATA/$data/g;
      print $write "$tmpRow";
    }
    #closes the files
    close($write);
    close($template);
  }
}
#closes the file
close($fh);