#!/usr/bin/perl

#print "one","two";

$truthy = 1;

#if(!$truthy){
#    print "true\n";
#} else {
#    print "false\n";
#}

#$cnt == 0;

#print "cnt: $cnt\n";
#$cnt++;
#print "cnt: $cnt\n";
#$cnt--;
#print "cnt: $cnt\n";
#$cnt++;
#print "cnt: $cnt\n";
#$cnt++;
#print "cnt: $cnt\n";

$tststr = "class Tes;";
$tststr2 = "class Test {";

$pat = qr/^\s*class (\w+)(?!.*;$)/;

$tsts = "c    ;";
if($tsts =~ /\w+(?!.*;$)/){
    print "bads\n";
}

if($tststr =~ $pat){
    print "bad\n";
}else{
    print "good\n";
    print $1;
}

if($tststr2 =~ $pat){
    print "good\n";
    print $1;
}else{
    print "bad\n";
}

#$line = "~EncodingMapper(){};";

#if ($line =~ /\{/){
#    print "t1\n";
#}

#if ($line =~ /((\w+)\s+)?([\w|~]+)/){
#    print "t2 $1\n";
#    print "t3 $3\n";
#}

#if ( $line =~ /((\w+)\s+)?([\w|~]+)\(.*\)\s*\{/ ) {
#    print "ok!\n";
#    print $1,"\n";
#    print $2,"\n";
#    print $3,"\n";
#} else {
#    print "bad\n";
#}

#print "parameters: ",@ARGV,"\n";
#foreach (@ARGV) {
#    print $_,"\n";
#}
