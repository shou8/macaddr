#!/opt/local/bin/perl

open(FH,"mac.db");
@lines = <FH>;

foreach $line(@lines){
    print length($line)."\n";
}
