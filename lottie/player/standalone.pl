#!/usr/bin/perl

use strict;

my $start_dir = `pwd`;
#my $sed_command = "sed -i'.sed_orig' -E 's/^\s*EM_ASM/\\\/\\\/EM_ASM/g'"
chomp $start_dir;

print $start_dir;

&process_dir($start_dir);

exit;

sub process_dir {
	my $dir = shift;
	opendir DIR, $dir;
	my @dir = readdir(DIR);
	close DIR;
	foreach(@dir) {
		if ($_ eq '.' || $_ eq '..') {
			next;
		}
		if (-f $dir."/". $_) {
			my $complete_filename = $dir."/".$_;
			if ($_ =~ /(\.cpp)$/) {
				#my $returned = `$sed_command $complete_filename`;
				&process_file($complete_filename);
				print "[PROCESSED] ",$_,"   : file\n";
			}
		} elsif (-d $dir."/".$_) {
			print $_,"--------------   : folder\n";
			&process_dir($dir."/".$_);
		} else {
			#print $_,"   : other\n";
		}
	}
}

sub process_file {
	my $file = shift;
	open (FILE, $file);
	open (OUTFILE, ">".$file.".outtemp");

	while (my $line = <FILE>) {
		$line =~ s/\/+EM_ASM/EM_ASM/g;
		$line =~ s/EM_ASM/\/\/EM_ASM/g;
		print OUTFILE $line;	
	}

	close (FILE);
	close (OUTFILE);
	unlink $file;
	rename $file.".outtemp", $file;
}

