# trans .cls to .clsresource

$R_filename=$ARGV[0];

open(R_FILE, $R_filename) || die "ERROR:can not open file $R_filename\n";
@array_file = <R_FILE>;
close(R_FILE);

$inpatch="./Png/";
$outpatch="./Res/";

$insuffix=".png";
$outsuffix=".PngRes";

foreach $line(@array_file){
    #print $line;
    $line=~s/[\r\n]$//;
    $infilename=$inpatch.$line.$insuffix;
    $outfilename=$outpatch.$line.$outsuffix;
    system("./LoadPng '$infilename' '$outfilename'");
}