my $something = "";
our $something2;

open (OUTFILE, ">jsonstring.h") || die "error writing file";
while (length($something) > 0) {
	$something =~ /^(.{1})/;
	if (ord($1) >= 0 && ord($1) <= 127) {
		$something2 = $something2.$1;
	}
	$something =~ s/^.{1}//g;
}

#$something2 =~ s/\'/__010__/g;
$something2 =~ s/\"/\\"/g;
#$something2 =~ s/\'/__010__/g;

print OUTFILE "string jsonString = \"$something2\"\;";

close (OUTFILE);

#print $something2;
#print $something;

print "\n\n".length($something2)."\n";
