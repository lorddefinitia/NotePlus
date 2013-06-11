#!/usr/bin/perl

#find class definitions in header files

#open header file
#$filen = @ARGV[0];

#append into cpp files

use DateTime;

print "arguments: ",$#ARGV,"\n";

$date = DateTime->now;

foreach my $filen (@ARGV) {

    my $cpp_filen = $filen;
    $cpp_filen =~ s/(\w+)\.h/$1.cpp/;
    
    if(! -e "$cpp_filen.base" ){
        system("cp", "$cpp_filen", "$cpp_filen.base");
        print "made copy of $cpp_filen\n";
    }
    #clean slate
    system("cp", "$cpp_filen.base", "$cpp_filen.work");
    #open(my$cp_cmd,"| xargs cp");

    print "h: $filen.work\n";

    open(my $cpp_file,">> $cpp_filen.work");
    open(my $file, "< $filen");
    open(my $test_mod,"> $filen.work");

    #find a class
    my $done = 0;
    my $in_class = 0;
    my $line = '';
    while(!$done){
        if ($in_class) {
            if(!($line=<$file>)){
                $done = 1;
                next;
            }
            #TODO nested functions?
            if ($line =~ /((?:virtual\s+)?(?:static\s+)?(?:const\s+)?(?:\w+\s+)(?:\*\s+)?(?:const(:?\s*))?)([\w|~]+)(\(.*\))(.*)\{/  ) {
                #found a method to replace
                my $ret_type = "$1";
                print "rettype: $ret_type\n";
                my $func_name = $3;
                print "funcname: $func_name\n";
                my $func_params = $4;
                my $construct_params = $5;
                print "cparams: $construct_params\n"; 
                #then find the whole method
                #readline
                my $block;
                if($line =~ /{(.+)/){
                    #print "match: $1\n";
                    $block = "{$1";
                } else {
                    #print "nomatch\n";
                    $block = "{\n";
                }
                my $blkcnt = 1;
                if($line =~ /\}/){
                    $blkcnt--;
                }
                while (!$blkcnt == 0) {
                    $line = <$file>;
                    $block = "$block$line";
                    if($line =~ /\}/){
                        $blkcnt--;
                    }
                    if($line =~ /\{/){
                        $blkcnt++;
                    }
                    #print "n\n";
                }
                #insert
                print "modified cpp_file: $cpp_filen.work\n";
                my $better_ret_type = $ret_type;
                $better_ret_type =~ s/^static//;
                $better_ret_type =~ s/^virtual//;
                print $cpp_file $better_ret_type,$class,"::",$func_name,$func_params,
                   $construct_params," ",$block,"\n";
                #replace
                #print $test_mod "//[MODIFIED $date]\n";
                print $test_mod "$ret_type $func_name $func_params$construct_params;\n";
                #echo for debug
                print "$ret_type $func_name$func_params$construct_params;\n";
            } else {
                #print "[UNMODIFIED]: $.\n";
                print $test_mod "$line";
                if($line =! /\{/){
                    $in_class++;
                }
                if($line =~ /\}/){
                    $in_class--;
                }
            }
            #exit class
        } else {
            if(!($line=<$file>)){
                $done = 1;
                next;
            }
            if($line =~ /^\s*class (\w+)(?!.*;$)/){
                $in_class = 1;
                $class = $1;
                print "[CLASS]: $class \n";
                print $test_mod $line;
            }else{
                print $test_mod $line;
            }
            #if($line == '\0'){
#                print "quitting...\n";
#                $done = 1;
#            }
        }
    }

    close $file;
    close $cpp_file;
    close $test_mod;
    
    #finally move the test file over the original
    system("mv","$filen.work", "$filen");
    #system("rm","$filen.work");

    #and delete the work file
    system("mv","$cpp_filen.work", "$cpp_filen");
    #system("rm","$cpp_filen.work");
}

#find the cpp file

#insert



#call with find . iname '*.h' | xargs findclassmethods.pl

