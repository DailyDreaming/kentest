#!/usr/bin/env perl

use strict;
use warnings;

# 1. reading iucnToNcbiEquivalent.txt to get ncbiToIucnNames hash
# 2. reading iucn/IUCN.CR.txt
# 3. reading iucn/IUCN.EN.txt
# 4. reading iucn/IUCN.VU.txt
# 5. reading iucn/links.csv
# 6. reading asmId.sciName.commonName to get better common names
# 7. reading accumulateMetaInfo.tsv to get better common names
# 8. reading ../../../sizes/asmId.sciName.commonName.date.tsv
# 9. reading assembly_summary_genbank.txt and assembly_summary_refseq.txt
             # to get asmId and scientific names for all assemblies
# 10. reading asmId.suppressed.list
# 11. reading asmId.date.taxId.asmSubmitter.tsv
# 12. reading asmId.country.date.by.tsv
# 13. now in a perClade loop, reading each all.*.clade.today listings
      # to get all refseq and genbank assemblies
# 14. during that loop, it may use the sizes chromInfo and the n50.txt
      # files from
# /hive/data/outside/ncbi/genomes/sizes/gcX/d0/d1/d2/asmId.chromInfo.txt";

###############################################################################
# from Perl Cookbook Recipe 2.17, print out large numbers with comma
# delimiters:
sub commify($) {
    my $text = reverse $_[0];
    $text =~ s/(\d\d\d)(?=\d)(?!\d*\.)/$1,/g;
    return scalar reverse $text
}
###############################################################################

###############################################################################
# obtain assembly size and sequence count from chromInfo file
sub sizeUpChromInfo($) {
  my ($ciFile) = @_;
  my $sizeCount=`ave -col=2 "$ciFile" | egrep -w "count|total" | awk '{printf "%d ", \$NF}'`;
  chomp $sizeCount;
  my ($count, $size, undef) = split('\s+', $sizeCount, 3);
  return ($size, $count);
}
###############################################################################

###############################################################################
# read an N50.txt output file from n50.pl to extract the size and count
sub readN50($) {
  my ($n50File) = @_;
  my $size = 0;
  my $count = 0;
  open (TF, "grep -v '^#' $n50File|") or die "can not read $n50File";
  while (my $line = <TF>) {
    chomp $line;
    my @a = split('\s+', $line);
    last if ($size > $a[0]);
    if ($a[1] ne "one") {
      $size = $a[3];
      $count = $a[1];
    }
  }
  close (TF);
  return ($size, $count);
}
###############################################################################

###############################################################################
# given a number, return reduced significant digits for giga, mega, kilo or none
sub gmk($) {
  my ($n) = @_;
  return sprintf("%d", $n) if ($n < 1000);
  my $m = $n/1000;
  return sprintf("%.2fK", $m) if ($m < 1000);
  $m = $n/1000000;
  return sprintf("%.2fM", $m) if ($m < 1000);
  $m = $n/1000000000;
  return sprintf("%.3fG", $m);
}
###############################################################################

###############################################################################
# output a table cell for an N50 measurement
sub n50Cell($$$) {
  my ($size, $count, $fh) = @_;
  if ($size > 0) {
    printf "<td style='display:none; text-align:right;' sorttable_customkey='%d'>%s&nbsp;(%s)</td>", $size, gmk($size), commify($count);
    printf $fh "\t%d (%d)", $size, $count;	# output to clade.tableData.txt
  } else {
    printf "<td style='display:none;'>&nbsp;</td>";
    printf $fh "\tn/a (n/a)";	# output to clade.tableData.txt
  }
}
###############################################################################

my @clades = qw( primates mammals birds fish vertebrate invertebrates plants fungi );
# my @clades = qw( primates mammals birds );

# to help weed out some of the noise
# key is clade, value is minimal size to count as a whole genome
# these are actually pretty low to allow in some alternate haplotype
# assemblies that don't seem to be the whole assembly.
# The assemblies are also filtered by NCBI status 'full/partial' to only
# allow in the 'full' genomes meaning representation of the whole genome
my %minimalGenomeSize = (
  primates => 1000000000,
  mammals => 20000000,
  birds => 200000000,
  fish => 100000,
  vertebrate => 4000000,
  invertebrates => 10000,
  plants => 100000,
  fungi => 50000,
);

#########################################################################
## read in list of current GenArk assemblies

my %genArkAsm;	# key is asmId, value is string with:

# accession<tab>assembly<tab>scientific name<tab>common name<tab>taxonId

my $genArkCount = 0;
printf STDERR "# reading UCSC_GI.assemblyHubList.txt\n";
open (FH, "<UCSC_GI.assemblyHubList.txt") or die "can not read UCSC_GI.assemblyHubList.txt";
while (my $line = <FH>) {
  next if ($line =~ m/^#/);
  chomp $line;
  my ($accession, $assembly, $sciName, $commonName, $taxonId) = split('\t', $line);
  die "ERROR: duplicate accession from UCSC_GI.assemblyHubList.txt" if (defined($genArkAsm{$accession}));
  my $asmId = sprintf("%s_%s", $accession, $assembly);
  $genArkAsm{$asmId} = sprintf("%s\t%s\t%s\t%s\t%s", $accession, $assembly, $sciName, $commonName, $taxonId);
  ++$genArkCount;
}
close (FH);

# accession     assembly        scientific name common name     taxonId
# GCA_000001905.1 Loxafr3.0       Loxodonta africana      African savanna elephant (2009 genbank) 9785

printf STDERR "# have %s assemblies from GenArk UCSC_GI.assemblyHubList.txt\n", commify($genArkCount);

my $rrCount = 0;
my %rrGcaGcfList;	# key is asmId, value is UCSC db name
open (FH, "<rr.GCF.GCA.list") or die "can not read rr.GCF.GCA.list";
while (my $line = <FH>) {
  chomp $line;
  my ($ucscDb, $asmId) = split('\s+', $line);
  $rrGcaGcfList{$asmId} = $ucscDb;
  ++$rrCount;
}
close (FH);

printf STDERR "# have %d assemblies with RR equivalent databases\n", $rrCount;

# establish a name equivalence for some NCBI three word scientific names
# to IUCN two word scientific names

my %ncbiToIucnNames;	# key is NCBI name (one), value is IUCN name (many)
# for example:
# Giraffa camelopardalis antiquorum -> Giraffa camelopardalis
# Giraffa camelopardalis rothschildi -> Giraffa camelopardalis

printf STDERR "### reading iucnToNcbiEquivalent.txt\n";
open (FH, "<../iucnToNcbiEquivalent.txt") or die "can not read iucnToNcbiEquivalent.txt";
while (my $line = <FH>) {
  chomp $line;
  my ($ncbiName, $iucnName) = split('\t', $line);
  $ncbiToIucnNames{$ncbiName} = $iucnName;
}
close (FH);

my $criticalColor = "#ff0000";
my $endangeredColor = "#dd6600";
my $vulnerableColor = "#663300";
my %statusColors = (
  "CR" => $criticalColor,
  "EN" => $endangeredColor,
  "VU" => $vulnerableColor,
);

my %iucnCR;	# key is scientific name, value is 1 == Critically Endangered
my %iucnEN;	# key is scientific name, value is 1 == Endangered
my %iucnVU;	# key is scientific name, value is 1 == Vulnerable

my %iucnSciNames;	# key is scientific name, value is IUCN code CR EN VU

my $iucnSpeciesCount = 0;
my $iucnCount = 0;
printf STDERR "### reading iucn/IUCN.CR.txt\n";
open (FH, "<../iucn/IUCN.CR.txt") or die "can not read iucn/IUCN.CR.txt";
while (my $sName = <FH>) {
  chomp $sName;
  $iucnCR{$sName} = 1;
  ++$iucnCount;
  $iucnSciNames{$sName} = "CR";
}
close (FH);
printf STDERR "# IUCN Critical %s\n", commify($iucnCount);
$iucnSpeciesCount += $iucnCount;

$iucnCount = 0;
printf STDERR "### reading iucn/IUCN.EN.txt\n";
open (FH, "<../iucn/IUCN.EN.txt") or die "can not read iucn/IUCN.EN.txt";
while (my $sName = <FH>) {
  chomp $sName;
  $iucnEN{$sName} = 1;
  ++$iucnCount;
  die "ERROR: duplicate sciName in IUCN CR and EN listings" if (defined($iucnCR{$sName}));
  $iucnSciNames{$sName} = "EN";
}
close (FH);
printf STDERR "# IUCN Endangered %s\n", commify($iucnCount);
$iucnSpeciesCount += $iucnCount;

$iucnCount = 0;
printf STDERR "### reading iucn/IUCN.VU.txt\n";
open (FH, "<../iucn/IUCN.VU.txt") or die "can not read iucn/IUCN.VU.txt";
while (my $sName = <FH>) {
  chomp $sName;
  $iucnVU{$sName} = 1;
  ++$iucnCount;
  $iucnSciNames{$sName} = "VU";
  die "ERROR: duplicate sciName in IUCN CR and VU listings" if (defined($iucnCR{$sName}));
  die "ERROR: duplicate sciName in IUCN EN and VU listings" if (defined($iucnEN{$sName}));
}
close (FH);
printf STDERR "# IUCN Vulnerable %s\n", commify($iucnCount);
$iucnSpeciesCount += $iucnCount;

my %iucnLink;	# key is sciName, value is the two id numbers 123/456
		# to make a link: https://www.iucnredlist.org/species/123/456
# get the id numbers from iucn to make links to IUCN
printf STDERR "### reading iucn/links.csv\n";
open (FH, "<../iucn/links.csv") or die "can not read iucn/links.csv";
while (my $line = <FH>) {
  chomp $line;
  my ($n2, $n1, $sName) = split(',', $line);
  $iucnLink{$sName} = sprintf("%d/%d", $n1, $n2);
}
close (FH);

my $comNameCount = 0;
my %ncbiCommonName;	# key is asmId, value is common name from NCBI assembly_report
my %ncbiDate;	# key is asmId, value is assembly submission date from NCBI assembly_report

#  common names from genArk hubs, better common name when available
my $hubComNames = 0;
my %sciName;	# key is asmId, value is scientific name
my %comName;	# key is asmId, value is common name
printf STDERR "### reading asmId.sciName.commonName\n";
open (FH, "<asmId.sciName.commonName") or die "can not read asmId.sciName.commonName";
while (my $line = <FH>) {
  chomp $line;
  my ($id, $sci, $com) = split('\t', $line);
  $sci =~ s/_/ /g;
  if (defined($sciName{$id})) {
    die "ERROR: duplicate asmId sciName: $id '$sci' '$sciName{$id}'";
  }
  $sciName{$id} = $sci;
  $comName{$id} = $com;
  ++$hubComNames;
}
close (FH);

printf STDERR "# common names from GenArk hubs: %s\n", commify($hubComNames);

my $genArkCatchup = 0;
### catch up for any missed genArk hubs
# accession<tab>assembly<tab>scientific name<tab>common name<tab>taxonId
foreach my $asmIdKey (sort keys %genArkAsm) {
  next if (defined($sciName{$asmIdKey}));
  next if (defined($comName{$asmIdKey}));
  my @a = split('\t', $genArkAsm{$asmIdKey});
  $a[2] =~ s/_/ /g;
  $sciName{$asmIdKey} = $a[2];
  $comName{$asmIdKey} = $a[3];
  ++$genArkCatchup;
}

printf STDERR "# catch up %d genArk hubs from hgdownload list\n", $genArkCatchup;

my %metaInfo;	# key is asmId, value is a tsv string of numbers for:
                # asmSize asmContigCount n50Size n50Count n50ContigSize
		# n50ContigCount n50ScaffoldSize n50ScaffoldCount
my %newMetaInfo;	# accumulate new metaInfo to add to end of this file

if ( -s "../accumulateMetaInfo.tsv" ) {
  printf STDERR "# reading ../accumulateMetaInfo.tsv\n";
  open (FH, "<../accumulateMetaInfo.tsv") or die "can not read ../accumulateMetaInfo.tsv";
  while (my $line = <FH>) {
    chomp $line;
    my ($asmId, $metaData) = split('\t', $line, 2);
    die "ERROR: duplicate metaInfo{$asmId}" if (defined($metaInfo{$asmId}));
    $metaInfo{$asmId} = $metaData;
  }
  close (FH);
}

my $earliestDate = 22001231;
my $latestDate = 19000101;
printf STDERR "### reading asmId.sciName.comonName.date.tsv\n";
open (FH, "<../asmId.sciName.commonName.date.tsv") or die "can not read ../asmId.sciName.commonName.date.tsv";
while (my $line = <FH>) {
  chomp $line;
  my @a = split('\t', $line);
  next if ($a[0] !~ m/^GC/);
  $a[0] =~ s/__/_/g;
  ++$comNameCount;
  $ncbiCommonName{$a[0]} = $a[2];
  if (defined($a[3]) && ($a[3] =~ m/^[12][0-9][0-9][0-9]-[0-9]+-[0-9]+$/) ) {
     my @b = split('-', $a[3]);
     $ncbiDate{$a[0]} = sprintf("%04d%02d%02d", $b[0], $b[1], $b[2]);
     $earliestDate = $ncbiDate{$a[0]} if ($ncbiDate{$a[0]} < $earliestDate);
     $latestDate = $ncbiDate{$a[0]} if ($latestDate < $ncbiDate{$a[0]});
  } else {
     $ncbiDate{$a[0]} = 19720101;
     if (defined($a[3])) {
       printf STDERR "# no date '%s' for %s'\n", $a[3], $a[0];
     } else {
       printf STDERR "# no date 'undef' for %s'\n", $a[0];
     }
  }
}
close (FH);
printf STDERR "# comNameCount %s from ../../../sizes/asmId.sciName.commonName.date.tsv\n", commify($comNameCount);
printf STDERR "# dates from %s to %s\n", $earliestDate, $latestDate;

my %sciNameCount;	# key is scientific name, value is count of assemblies
			# from NCBI assembly_summary .txt files
my %sciNames;	# key is asmId, value is scientific name
my %sciNameAsmList;	# key is scientific name, value is pointer to array
			# which is a list of assemblies on this sciName

# goodToGo will be the master asmId list for output
my %goodToGoSpecies;	# key is scientific name, value is asmId selected
my %goodToGo;	# key is asmId, value is iucn status code CR EN VU
my %goodToGoDate;	# key is sciName, value is date YYYYMMDD for selected
			# assembly
# choices in order when duplicate species:
# GCA assembly
# newer GCA assembly
# GCF assembly
# newer GCF assembly

my $ncbiTotalAssemblies = 0;
my $ncbiUniqueSpecies = 0;
my $highestSpeciesCount = 0;
my $highestCountName = "";

my $countingGoodToGo = 0;
my $goodToGoReplaced = 0;
my $warningNoDate = 0;

my %skipPartialGenome;	# key is asmId, value is sciName for 'partial' status

# obtain scientific name and asmId from assembly_summary files
printf STDERR "### reading genbank and refseq assembly_summary\n";
open (FH, "grep -v '^#' /hive/data/outside/ncbi/genomes/reports/assembly_summary_genbank.txt /hive/data/outside/ncbi/genomes/reports/assembly_summary_refseq.txt|cut -f8,14,20|") or die "can not read the assembly_summary files";
while (my $line = <FH>) {
  chomp $line;
  # asmId will be derived from the ftpPath
  my ($sName, $fullPartial, $asmId) = split('\t', $line);
  # most interesting, skipping these partial assemblies ends up with more
  # in the final result ?
  $asmId =~ s#.*/##;
  next if ($asmId =~ m/^na$/);
  # something wrong with these two
  next if ($asmId =~ m/GCA_900609255.1|GCA_900609265.1/);
  if ($fullPartial =~ m/partial/i) {        # skip partial assemblies
    $skipPartialGenome{$asmId} = $sName;
    next;
  }
  ++$sciNameCount{$sName};
  $sciNames{$asmId} = $sName;
  if (!defined($sciNameAsmList{$sName})) {
    my @a;
    $sciNameAsmList{$sName} = \@a;
  }
  my $sPtr = $sciNameAsmList{$sName};
  push (@$sPtr, $asmId);	# maintain list of asmIds for this sciName
  ++$ncbiTotalAssemblies;
  ++$ncbiUniqueSpecies if (1 == $sciNameCount{$sName});
  if ($sciNameCount{$sName} > $highestSpeciesCount) {
    $highestSpeciesCount = $sciNameCount{$sName};
    $highestCountName = $sName;
  }
  # only selecting assemblies if IUCN classification exists
  my $iucnSciName = $sName;	# check name equivalence
 $iucnSciName = $ncbiToIucnNames{$sName} if (defined($ncbiToIucnNames{$sName}));
#### XXX ### let's try everything instead of just those with IUCN class
  if ( 1 == 1 || defined($iucnSciNames{$iucnSciName})) {
    if (defined($goodToGoSpecies{$sName})) {	# already seen
      my $prevGC = $goodToGoSpecies{$sName};	# see if it should be override
      if ($prevGC =~ m/^GCA/) {
         if ($asmId =~ m/^GCF/) {	# GCF overrides GCA
           $goodToGoSpecies{$sName} = $asmId;
           delete $goodToGo{$prevGC};
           ++$goodToGoReplaced;
           $goodToGo{$asmId} = $iucnSciNames{$iucnSciName};
           if (defined($ncbiDate{$asmId})) {
             $goodToGoDate{$sName} = $ncbiDate{$asmId};
           } else {
#        printf STDERR "# 0 warning: no ncbiDate for $asmId $sName '$line'\n";
             ++$warningNoDate;
             $goodToGoDate{$sName} = 19720101;
           }
         } else {	# another GCA, check dates
           if (defined($ncbiDate{$asmId})) {
             if ($ncbiDate{$asmId} > $goodToGoDate{$sName}) { # newer
               delete $goodToGo{$prevGC};
               ++$goodToGoReplaced;
               $goodToGoSpecies{$sName} = $asmId;
               $goodToGo{$asmId} = $iucnSciNames{$iucnSciName};
               $goodToGoDate{$sName} = $ncbiDate{$asmId};
             } else {
             }
           } else {	# no date, no replace
#       printf STDERR "# 1 warning: no ncbiDate for $asmId $sName '$line'\n";
             ++$warningNoDate;
           }
         }
      } elsif ($asmId =~ m/^GCF/) {	# a second GCF
        if (defined($ncbiDate{$asmId})) {
          if ($ncbiDate{$asmId} > $goodToGoDate{$sName}) { # newer
             delete $goodToGo{$prevGC};
             ++$goodToGoReplaced;
             $goodToGoSpecies{$sName} = $asmId;
             $goodToGo{$asmId} = $iucnSciNames{$iucnSciName};
             $goodToGoDate{$sName} = $ncbiDate{$asmId};
          } else {
          }
        } else {	# no date, no replace
#        printf STDERR "# 2 warning: no ncbiDate for $asmId $sName '$line'\n";
             ++$warningNoDate;
        }
      }
    } else {	# first time, take this assembly
      ++$countingGoodToGo;
      $goodToGoSpecies{$sName} = $asmId;
      $goodToGo{$asmId} = $iucnSciNames{$iucnSciName};
      if (defined($ncbiDate{$asmId})) {
        $goodToGoDate{$sName} = $ncbiDate{$asmId};
      } else {
#      printf STDERR "# 3 warning: no ncbiDate for $asmId $sName '$line'\n";
             ++$warningNoDate;
        $goodToGoDate{$sName} = 19720101;
      }
    }
  } 	#	if (defined($iucnSciNames{$iucnSciName}))
}	#	while (my $line = <FH>) reading the assembly_summary files
close (FH);

printf STDERR "# countedGoodToGo: %d, replaced: %d, noDate: %d\n", $countingGoodToGo, $goodToGoReplaced, $warningNoDate;
printf STDERR "# have %s NCBI assemblies, %s unique NCBI species\n", commify($ncbiTotalAssemblies), commify($ncbiUniqueSpecies);
printf STDERR "#\thighest species count %s : '%s'\n", commify($highestSpeciesCount), $highestCountName;

my %gcxCountry;	# key is asmId, value is collection location
my %gcxDate;	# key is asmId, value is collection date
my %gcxSubmitter;	# key is asmId, value is collected by
my %asmSuppressed;	# key is asmId, value is 1 meaning suppressed

printf STDERR "### reading asmId.suppressed.list\n";
open (FH, "<asmId.suppressed.list") or die "can not read asmId.suppressed.list";
while (my $id = <FH>) {
  chomp $id;
  $asmSuppressed{$id} = 1;
}
close (FH);

my %asmDate;	# key is asmId, value is date of assembly
my %asmSubmitter;	# key is asmId, value is name of assembly submitter
my %asmTaxId;	# key is asmId, value is taxId of species

my $asmIdCount = 0;
printf STDERR "### reading ../asmId.date.taxId.asmSubmitter.tsv\n";
open (FH, "<../asmId.date.taxId.asmSubmitter.tsv") or die "can not read a../smId.date.taxId.asmSubmitter.tsv";
while (my $line = <FH>) {
  chomp $line;
  my ($id, $da, $tid, $asmS) = split('\t', $line);
  $id =~ s/__/_/g;
  $da = "&nbsp;" if ($da =~ m#n/a#);
  $tid = "&nbsp;" if ($tid =~ m#n/a#);
  $asmS = "&nbsp;" if ($asmS =~ m#n/a#);
  $asmDate{$id} = $da;
  $asmTaxId{$id} = $tid;
  $asmSubmitter{$id} = $asmS;
  ++$asmIdCount;
}
close (FH);
printf STDERR "# asmId count: %s from asmId.date.taxId.asmSubmitter.tsv\n", commify($asmIdCount);

$asmIdCount = 0;
printf STDERR "### reading ../asmId.country.date.by.tsv\n";
open (FH, "<../asmId.country.date.by.tsv") or die "can not read ../asmId.country.date.by.tsv";
while (my $line = <FH>) {
  chomp $line;
  my ($id, $country, $collectDate, $submitter) = split('\t', $line);
  $id =~ s/__/_/g;
  if (defined($gcxCountry{$id})) {
    die "ERROR: duplicate asmId data $id '$country' '$gcxCountry{$id}'";
  }
  printf STDERR "# undefined collectDate for $id" if (!defined($collectDate));
  printf STDERR "# undefined submitter for $id" if (!defined($submitter));
  $country =~ s/"//g;
  $collectDate =~ s/"//g;
  $submitter =~ s/"//g;
  $gcxCountry{$id} = $country;
  $gcxDate{$id} = $collectDate;
  $gcxSubmitter{$id} = $submitter;
  ++$asmIdCount;
}
close (FH);
printf STDERR "# asmId count: %s from asmId.country.date.by.tsv\n", commify($asmIdCount);

### This cladeToGo set of lists is the main driver of the table
### An assembly needs to be in this set in order to get into the table
my %cladeToGo;	# key is clade name, value is array pointer for asmId list
my $totalGoodToGo = 0;
my %cladeCounts;	# key is clade name, value is count of assemblies used

my $maxDupAsm = 0;
my %ncbiSpeciesRecorded;	# key is NCBI sciName, value is count of those
my $ncbiSpeciesUsed = 0;	# a unique count of NCBI sciName
my %iucnSpeciesRecorded;	# key is IUCN sciName, value is count of those
my $iucnSpeciesUsed = 0;	# a unique count of IUCN sciName

my $sciNameDisplayLimit = 5;    # do not display more than 5 instances

my $checkedAsmIds = 0;
my $acceptedAsmIds = 0;
my $notInGoodToGo = 0;
my %alreadyDone;	# key is asmId, value = 1 indicates already done
my %underSized;		# key is clade, value is count of underSized

my $NA = "/hive/data/outside/ncbi/genomes/reports/newAsm";
my %genArkClade;	# key is asmId, value is clade

my $shouldBeGenArk = 0;
my $shouldBeUcsc = 0;

foreach my $clade (@clades) {
  my $cladeCount = 0;
  my $goodToGoCount = 0;
  my $refSeq = "${NA}/all.refseq.${clade}.today";
  my $genBank = "${NA}/all.genbank.${clade}.today";
  open (FH, "sort ${refSeq} ${genBank}|") or die "can not read $refSeq or $genBank";
  while (my $asmId = <FH>) {
     chomp $asmId;
     $asmId =~ s/\.]/_/g;
     $asmId =~ s/\:/_/g;
     $asmId =~ s/\%/_/g;
     $asmId =~ s/\+/_/g;
     $asmId =~ s/\//_/g;
     $asmId =~ s/\#/_/g;
#      $asmId =~ s/[.:%+/#]/_/g;
     $asmId =~ s/[()]//g;
     $asmId =~ s/__/_/g;
     ++$shouldBeGenArk if (defined($genArkAsm{$asmId}));
     ++$shouldBeUcsc if (defined($rrGcaGcfList{$asmId}));
     next if (defined ($skipPartialGenome{$asmId}));
     next if (defined ($asmSuppressed{$asmId}));
     next if (defined ($alreadyDone{$asmId}));
     # something wrong with these two
# GCA_900609255.1_Draft_mitochondrial_genome_of_wild_rice_W1683
# GCA_900609265.1_Draft_mitochondrial_genome_of_wild_rice_W1679
     next if ($asmId =~ m/GCA_900609255.1|GCA_900609265.1/);
     # verify this asmId will pass the asmSize limit
     if (defined($metaInfo{$asmId})) {
      my ($asmSize, $asmContigCount, $n50Size, $n50Count, $n50ContigSize, $n50ContigCount, $n50ScaffoldSize, $n50ScaffoldCount) = split('\t', $metaInfo{$asmId});
      # if asmSize is below the minimum, don't use it
       if ($asmSize < $minimalGenomeSize{$clade}) {
         printf STDERR "# %s underSized 0 %d %s %s < %s\n", $clade, ++$underSized{$clade}, $asmId, commify($asmSize), commify($minimalGenomeSize{$clade});
     printf STDERR "# ACK would be genArk assembly %s\n", $asmId if (defined($genArkAsm{$asmId}));
     printf STDERR "# ACK would be UCSC RR %s\n", $asmId if (defined($rrGcaGcfList{$asmId}));
printf STDERR "# ACK metaInfo: %s '%s'\n", $asmId, $metaInfo{$asmId};
         next;
       }
     }
     $alreadyDone{$asmId} = 1;
     if (defined($genArkClade{$asmId})) {
      die "ERROR: duplicate asmId today $asmId '$clade' '$genArkClade{$asmId}'";
     }
     ++$checkedAsmIds;
     my $iucnSciName = "";
     if (defined($sciNames{$asmId})) {
       ++$ncbiSpeciesRecorded{$sciNames{$asmId}};
       next if ($ncbiSpeciesRecorded{$sciNames{$asmId}} > $sciNameDisplayLimit);
       $iucnSciName = $sciNames{$asmId};
 $iucnSciName = $ncbiToIucnNames{$sciNames{$asmId}} if (defined($ncbiToIucnNames{$sciNames{$asmId}}));
       ++$iucnSpeciesRecorded{$iucnSciName};
     } else {
       printf STDERR "# no sciName for: '%s' at %s\n", $asmId, commify($goodToGoCount + 1);
     }
     $genArkClade{$asmId} = $clade;
     ++$cladeCount;
     if (! defined($cladeToGo{$clade})) {
       my @a;
       $cladeToGo{$clade} = \@a;
     }
     my $cPtr = $cladeToGo{$clade};
     push (@$cPtr, $asmId);
     ++$acceptedAsmIds;
     ++$goodToGoCount;
     ++$ncbiSpeciesUsed if ( defined($sciNames{$asmId}) && defined($ncbiSpeciesRecorded{$sciNames{$asmId}}) && (1 == $ncbiSpeciesRecorded{$sciNames{$asmId}}) );
     ++$iucnSpeciesUsed if ( defined($iucnSpeciesRecorded{$iucnSciName}) && (1 == $iucnSpeciesRecorded{$iucnSciName}));
     ++$cladeCounts{$clade};
     my $assembliesAvailable = 0;
     if (defined($sciNames{$asmId})) {
       if (defined($sciNameCount{$sciNames{$asmId}})) {
         $assembliesAvailable = $sciNameCount{$sciNames{$asmId}};
       $maxDupAsm = $assembliesAvailable if ($assembliesAvailable > $maxDupAsm);
       }
       if ($assembliesAvailable > 1) {
          my $bPtr = $sciNameAsmList{$sciNames{$asmId}};
          foreach my $aId (@$bPtr) {
             next if (defined ($alreadyDone{$aId}));
             $alreadyDone{$aId} = 1;
             if ($aId ne $asmId) {
               if (defined($metaInfo{$aId})) {
                 my ($asmSize, $asmContigCount, $n50Size, $n50Count, $n50ContigSize, $n50ContigCount, $n50ScaffoldSize, $n50ScaffoldCount) = split('\t', $metaInfo{$aId});
                 # if asmSize is below the minimum, don't use it
                 if ($asmSize < $minimalGenomeSize{$clade}) {
                   printf STDERR "# %s underSized 1 %d %s %s < %s\n", $clade, ++$underSized{$clade}, $aId, commify($asmSize), commify($minimalGenomeSize{$clade});
     printf STDERR "# ACK would be genArk assembly %s\n", $aId if (defined($genArkAsm{$aId}));
     printf STDERR "# ACK would be UCSC RR %s\n", $aId if (defined($rrGcaGcfList{$aId}));
printf STDERR "# ACK metaInfo: %s '%s'\n", $aId, $metaInfo{$aId};
                   next;
                 }
               }
               ++$ncbiSpeciesRecorded{$sciNames{$aId}};
               # the defined($sciName{$aId}) indicates it is a GenArk genome
               # always accept those even if it goes beyond the limit
               if ( ($ncbiSpeciesRecorded{$sciNames{$aId}} <= $sciNameDisplayLimit) || defined($sciName{$aId}) ) {
                 push (@$cPtr, $aId);
                 ++$acceptedAsmIds;
                 ++$goodToGoCount;
                 ++$cladeCounts{$clade};
               }	#	under limit count or is GenArk assembly
             }	#	if ($aId ne $asmId)
          }	#	foreach my $aId (@$bPtr)
       }	#	if ($assembliesAvailable > 1)
     }	#	if (defined($sciNames{$asmId}))
  }	#	while (my $asmId = <FH>)
  close (FH);
  printf STDERR "# %s\t%s\tgood to go %s\n", $clade, commify($cladeCount), $goodToGoCount;
  $totalGoodToGo += $goodToGoCount;
}	#	foreach my $clade (@clades)

printf STDERR "# checkedAsmIds: %d, acceptedAsmIds: %d, notInGoodToGo: %d\n", $checkedAsmIds, $acceptedAsmIds, $notInGoodToGo;

printf STDERR "# total good to go %s, maxDupAsmCount: %s\n", commify($totalGoodToGo), commify($maxDupAsm);;

printf STDERR "# should be GenArk: %s\n", commify($shouldBeGenArk);
printf STDERR "# should be UCSC RR %s\n", commify($shouldBeUcsc);

printf "<hr>\n";
if ( 1 == 0 ) {
printf "<button id='summaryCountsHideShow' onclick='gar.hideTable(\"summaryCounts\")'>[hide]</button>\n";
printf "<table class='sortable borderOne' id='summaryCounts'>\n";
printf "<caption style='text-align:center;'><b>===== summary counts =====</b></caption>\n";
printf "<thead>\n";
printf "<tr>\n";
printf "<th>number of assemblies</th>\n";
printf "<th>category of count</th>\n";
printf "<th>table data in tsv<br>(tab separated value)<br>file format</th>\n";
printf "<th>assembly minimal size<br>to filter out projects that<br>are not whole genomes</th>\n";
printf "</tr>\n";
printf "</thead><tbody>\n";
printf "<tr><th style='text-align:right;'>%s</th><th>total number of NCBI assemblies under consideration</th><th>&nbsp;</th><th>&nbsp;</th></tr>\n", commify($ncbiTotalAssemblies);
printf "<tr><th style='text-align:right;'>%s</th><th>number of unique species in NCBI assemblies</th><th>&nbsp;</th><th>&nbsp;</th></tr>\n", commify($ncbiUniqueSpecies);
printf "<tr><th style='text-align:right;'>%s</th><th>number of unique NCBI species matched to IUCN classification</th><th>&nbsp;</th><th>&nbsp;</th></tr>\n", commify($ncbiSpeciesUsed);
printf "<tr><th style='text-align:right;'>%s</th><th>number of IUCN species with CR/EN/VU classification</th><th>&nbsp;</th><th>&nbsp;</th></tr>\n", commify($iucnSpeciesCount);
printf "<tr><th style='text-align:right;'>%s</th><th>number of such IUCN species matched to NCBI assemblies</th><th>&nbsp;</th><th>&nbsp;</th></tr>\n", commify($iucnSpeciesUsed);
printf "<tr><th style='text-align:right;'>%s</th><th>total number of NCBI assemblies classified in these tables</th><th>&nbsp;</th><th>&nbsp;</th></tr>\n", commify($totalGoodToGo);
foreach my $clade (@clades) {
  if (defined($cladeCounts{$clade})) {
    my $tsvFile = sprintf("%s.tableData.txt", $clade);
    printf "<tr><th style='text-align:right;'>%s</th>", commify($cladeCounts{$clade});
    printf "<th><a href='#%s'>%s</a></th>", $clade, $clade;
    printf "<th><a href='%s' target=_blank>%s</a></th>", $tsvFile, $tsvFile;
    printf "<th style='text-align:right;'>%s</th>", commify($minimalGenomeSize{$clade});
    printf "</tr>\n";
  }
}
print "</tbody></table>\n";
printf "<hr>\n";

sub sectionDiv($) {
  my ($clade) = @_;
  printf "<a id='%sSection'></a>\n", $clade;
  printf "<table class='sectionDiv'><tr>\n";
  printf "<td><button class='hideShowButton' id='%sHideShow' onclick='gar.hideTable(\"%s\")'>[hide]</button><b>&nbsp;%s</b></td>\n", $clade, $clade, $clade;
  foreach my $c (@clades) {
    if ($c ne $clade) {
      printf "<td><a href=#%sSection>%s</a></td>\n", $c, $c;
    } else {
      printf "<td><em>page sections</em></td>\n";
    }
  }
  printf "<td><a href='#pageTop'>top of page</a></td>\n";
  printf "</table>\n";
}
}	#	if ( 1 == 0 )

# count all assemblies in all clades
my $totalAssemblies = 0;
foreach my $c (@clades) {
  $totalAssemblies += $cladeCounts{$c};
}

printf "<!-- to get the pull-down menu items centered together -->\n";
printf "<div style='text-align: center;'><!-- this will cause the next div to center -->\n";
printf "  <div style='display: inline-block'>\n";

printf "<div class='pullDownMenu'>\n";
printf "  <span id='speciesSelectAnchor'>choose clades to view/hide</span>\n";
printf "  <div class='pullDownMenuContent'>\n";
printf "  <ul id='checkBoxSpeciesSelect'>\n";
printf "    <li><label><input class='hideAll' type='checkbox' onchange='gar.visCheckBox(this)' id='allCheckBox' value='all' checked><span class='hideAllLabel'> hide all</span></label></li>\n";
printf "    <li><label><input class='hideShow' type='checkbox' onchange='gar.visCheckBox(this)' id='primatesCheckBox' value='primates' checked><span id='primatesLabel'> primates</span></label></li>\n";
printf "    <li><label><input class='hideShow' type='checkbox' onchange='gar.visCheckBox(this)' id='mammalsCheckBox' value='mammals' checked><span id='mammalsLabel'> mammals</span></label></li>\n";
printf "    <li><label><input class='hideShow' type='checkbox' onchange='gar.visCheckBox(this)' id='birdsCheckBox' value='birds' checked><span id='birdsLabel'> birds</span></label></li>\n";
printf "    <li><label><input class='hideShow' type='checkbox' onchange='gar.visCheckBox(this)' id='fishCheckBox' value='fish' checked><span id='fishLabel'> fish</span></label></li>\n";
printf "    <li><label><input class='hideShow' type='checkbox' onchange='gar.visCheckBox(this)' id='vertebrateCheckBox' value='vertebrate' checked><span id='vertebrateLabel'> vertebrate</span></label></li>\n";
printf "    <li><label><input class='hideShow' type='checkbox' onchange='gar.visCheckBox(this)' id='invertebratesCheckBox' value='invertebrates' checked><span id='invertebratesLabel'> invertebrates</span></label></li>\n";
printf "    <li><label><input class='hideShow' type='checkbox' onchange='gar.visCheckBox(this)' id='plantsCheckBox' value='plants' checked><span id='plantsLabel'> plants<span></label></li>\n";
printf "    <li><label><input class='hideShow' type='checkbox' onchange='gar.visCheckBox(this)' id='fungiCheckBox' value='fungi' checked><span id='fungiLabel'> fungi</span></label></li>\n";
printf "  </ul>\n";
printf "  </div>\n";
printf "</div>\n";

printf "<div style='width: 260px;' class='pullDownMenu'>\n";
printf "  <span style='text-align: center;' id='assemblyTypeAnchor'>select assembly type to display</span>\n";
printf "  <div class='pullDownMenuContent'>\n";
printf "  <ul id='checkBoxAssemblyType'>\n";
printf "    <li><label><input class='hideAll' type='checkbox' onchange='gar.visCheckBox(this)' id='allCheckBox' value='all' checked><span class='hideAllLabel'> hide all</span></label></li>\n";
printf "    <li><label><input class='hideShow' type='checkbox' onchange='gar.visCheckBox(this)' id='gakCheckBox' value='gak' checked><span id='gakLabel'> Existing browser</span></label></li>\n";
printf "    <li><label><input class='hideShow' type='checkbox' onchange='gar.visCheckBox(this)' id='garCheckBox' value='gar' checked><span id='garLabel'> Request browser</span></label></li>\n";
printf "    <li><label><input class='hideShow' type='checkbox' onchange='gar.visCheckBox(this)' id='gcaCheckBox' value='gca' checked><span id='gcaLabel'> GCA/GenBank</span></label></li>\n";
printf "    <li><label><input class='hideShow' type='checkbox' onchange='gar.visCheckBox(this)' id='gcfCheckBox' value='gcf' checked><span id='gcfLabel'> GCF/RefSeq</span></label></li>\n";
printf "   </ul>\n";
printf "  </div>\n";
printf "</div>\n";

printf "<div class='pullDownMenu'>\n";
printf "  <span id='columnSelectAnchor'>select columns of information to display</span>\n";
printf "  <div class='pullDownMenuContent'>\n";
printf "  <ul id='checkBoxColumnSelect'>\n";
printf "    <li><label><input class='columnCheckBox' type='checkbox' onchange='gar.resetColumnVis(this)' id='comNameCheckBox' value='comName' checked> common name</label></li>\n";
printf "    <li><label><input class='columnCheckBox' type='checkbox' onchange='gar.resetColumnVis(this)' id='sciNameCheckBox' value='sciName' checked> scientific name</label></li>\n";
printf "    <li><label><input class='columnCheckBox' type='checkbox' onchange='gar.resetColumnVis(this)' id='asmIdCheckBox' value='asmId' checked> NCBI accession</label></li>\n";
printf "    <li><label><input class='columnCheckBox' type='checkbox' onchange='gar.resetColumnVis(this)' id='asmSizeCheckBox' value='asmSize'> assembly size</label></li>\n";
printf "    <li><label><input class='columnCheckBox' type='checkbox' onchange='gar.resetColumnVis(this)' id='seqCountCheckBox' value='seqCount'> sequence count</label></li>\n";
printf "    <li><label><input class='columnCheckBox' type='checkbox' onchange='gar.resetColumnVis(this)' id='scafN50CheckBox' value='scafN50'> scaffold N50 size (L50 count)</label></li>\n";
printf "    <li><label><input class='columnCheckBox' type='checkbox' onchange='gar.resetColumnVis(this)' id='ctgN50CheckBox' value='ctgN50'> contig N50 size (L50 count)</label></li>\n";
printf "    <li><label><input class='columnCheckBox' type='checkbox' onchange='gar.resetColumnVis(this)' id='IUCNCheckBox' value='IUCN'> IUCN status</label></li>\n";
printf "    <li><label><input class='columnCheckBox' type='checkbox' onchange='gar.resetColumnVis(this)' id='taxIdCheckBox' value='taxId'> NCBI taxonomy ID</label></li>\n";
printf "    <li><label><input class='columnCheckBox' type='checkbox' onchange='gar.resetColumnVis(this)' id='asmDateCheckBox' value='asmDate'> assembly date</label></li>\n";
printf "    <li><label><input class='columnCheckBox' type='checkbox' onchange='gar.resetColumnVis(this)' id='submitterCheckBox' value='submitter'> assembly submitter</label></li>\n";
printf "    <li><label><input class='columnCheckBox' type='checkbox' onchange='gar.resetColumnVis(this)' id='cladeCheckBox' value='clade'> clade</label></li>\n";
printf "  </ul>\n";
printf "  </div>\n";
printf "</div>\n\n";
printf "  </div>        <!-- display inline-block to be 'text' centered -->\n";
printf "</div>  <!-- this parent div is text-align: center to center children -->\n\n";

printf "<table style='width: 100%%;' class='borderOne' id='loadingStripes'>\n";
printf "<caption><h2>. . . please wait while page loads . . .</h2></caption>\n";
printf "</table>\n\n";

printf "<div style='text-align: center;'><!-- this will cause the next div to center -->\n";
printf "  <div style='display: inline-block'>\n\n";

printf "<h2 style='display: none;' id='counterDisplay'>%s total assemblies : use the selection menus to select subsets</h2>\n\n", commify($totalAssemblies);

##############################################################################
##  begin single table output, start the table and the header
##
## table starts out as display: hide and will be reset to 'table' after
## page load.  Saves a lot of time for Chrome browsers, however the page
## is still not usable until much time later.
##############################################################################
printf "<table style='display: hide;' class='sortable borderOne cladeTable' id='dataTable'>\n";

printf "<colgroup id='colDefinitions'>\n";
printf "<col id='comName' span='1' class=colGComName>\n";
printf "<col id='sciName' span='1' class=colGSciName>\n";
printf "<col id='asmId' span='1' class=colGAsmId>\n";
printf "<col id='asmSize' span='1' class=colGAsmSize>\n";
printf "<col id='seqCount' span='1' class=colGAsmSeqCount>\n";
printf "<col id='scafN50' span='1' class=colGScafN50>\n";
printf "<col id='ctgN50' span='1' class=colGContigN50>\n";
printf "<col id='IUCN' span='1' class=colGIUCN>\n";
printf "<col id='taxId' span='1' class=colGTaxId>\n";
printf "<col id='asmDate' span='1' class=colGAsmDate>\n";
printf "<col id='submitter' span='1' class=colGSubmitter>\n";
printf "<col id='clade' span='1' class=colGClade>\n";
printf "</colgroup>\n";

printf "<thead>\n";
printf "<tr>\n";
printf "  <th class='colComName'><div class='tooltip'>common name<span class='tooltiptext'>The <em>common name</em> links to a genome browser when it exists, or provides a request form to ask for the assembly to be added to the system</span></div></th>\n";
printf "  <th class='colSciName'><div class='tooltip'>scientific name (count)<span class='tooltiptext'>The numbers in parenthesis (1234) following the name indicates the number of assemblies available for this species.  The link does a google image search for that name.</span></div></th>\n";
printf "  <th class='colAsmId'><div class='tooltip'>NCBI assembly<span class='tooltiptext'>The <em>NCBI assembly</em> provides a link to the NCBI resource record for this assembly</span></div></th>\n";
printf "  <th class='colAsmSize'><div class='tooltip'>assembly<br>size<span class='tooltiptext'>The <em>assembly size</em> is the total number of nucleotides in the assembly.</span></div></th>\n";
printf "  <th class='colAsmSeqCount'><div class='tooltip'>sequence<br>count<span class='tooltiptext'>The <em>sequence count</em> is the number of sequences in this assembly.</span></div></th>\n";
printf "  <th class='colScafN50'><div class='tooltip'>scaffold N50<br>size (L50)<span class='tooltiptext'>The <em>scaffold N50</em> is the <a href='https://en.wikipedia.org/wiki/N50,_L50,_and_related_statistics' target=_blank>N50 measurement</a> for this assembly.</span></div> </th>\n";
printf "  <th class='colContigN50'><div class='tooltip'>contig N50<br>size (L50)<span class='tooltiptext'>The <em>contig N50</em> is the <a href='https://en.wikipedia.org/wiki/N50,_L50,_and_related_statistics' target=_blank>N50 measurement</a> for this assembly when there are contigs to measure.</span></div></th>\n";
printf "  <th class='colIUCN'><div class='tooltip'>I<br>U<br>C<br>N<span class='tooltiptext'>IUCN status column is the status from the <a href='https://www.iucnredlist.org/' target=_blank>IUCN (2021) Red List</a> of Threatened species, Version 2021-3, accessed on 17 Dec 2021 <span style='color:%s;'>CR - Critical</span> / <span style='color:%s;'>EN - Endangered</span> / <span style='color:%s;'>VU - Vulnerable</span> The link goes to the IUCN web site for more information for that species.</span></div></th>\n", $statusColors{"CR"}, $statusColors{"EN"}, $statusColors{"VU"};
printf "  <th class='colTaxId'><div class='tooltip'>NCBI taxID<span class='tooltiptext'>The <em>taxID</em> links to the <a href='https://www.ncbi.nlm.nih.gov/taxonomy' target='_blank'>NCBI taxonomy</a> database.</span></div></th>\n";
printf "  <th class='colAsmDate'><div class='tooltip'>assembly<br>date<span class='tooltiptext'>The submission date for this assembly to the <a href='https://www.ncbi.nlm.nih.gov/assembly' target=_blank>NCBI assembly</a> system.</span></div></th>\n";
printf "  <th class='colSubmitter sorttable_alpha'><div class='tooltip'>submitter of assembly<span class='tooltiptextright'>The name of the organization that produced this assembly.</span></div></th>\n";
printf "  <th class='colClade'><div class='tooltip'>clade<span class='tooltiptextright'>Indicating the <em>clade</em> of this organism.  Note: the <em>invertebrate</em> clade is a catch all category that includes organisims not typically classified as <em>invertebrate</em></span></div></th>\n";
printf "</tr>\n";
printf "</thead><tbody>\n";

my %equivalentNamesUsed;	# key is NCBI sciName, value is IUCN sciName
my $pageSectionCount = 0;

my %checkDupAsmId;	# key is asmId, value is count of times seen

my %cladeSciNameCounts;	# key is clade, value is number of different
			# scientific names

my %gcfGcaCounts;	# key is GCF or GCA, value is count of each
my $asmCountInTable = 0;	# counting the rows output
my %statusCounts;	# key is status: CR EN VU, value is count
my $totalAssemblySize = 0;	# sum of all assembly sizes

foreach my $clade (@clades) {
  my $cPtr = $cladeToGo{$clade};
  my $countThisClade = scalar(@$cPtr);
  printf STDERR "# working on clade '%s', count: %s\n", $clade, commify($countThisClade);

##  sectionDiv($clade);	# starting new clade table

  ++$pageSectionCount;
  my $totalContigCounts = 0;
  my $underSized = 0;

  ######################## rows of per clade table output here ################
  my $tsvFile = sprintf("%s.tableData.txt", $clade);
  open (PC, ">$tsvFile") or die "can not write to $tsvFile";

  foreach my $asmId (@$cPtr) {
     if (defined($checkDupAsmId{$asmId})) {
      printf STDERR "# what: duplicate asmId: %s in clade %s\n", $asmId, $clade;
        $checkDupAsmId{$asmId} += 1;
     } else {
        $checkDupAsmId{$asmId} = 1;
     }
    my $assembliesAvailable = 0;
    if (defined($sciNames{$asmId})) {
      if (defined($sciNameCount{$sciNames{$asmId}})) {
        $assembliesAvailable = $sciNameCount{$sciNames{$asmId}};
      }
    }
    if (defined ($asmSuppressed{$asmId})) {
      if (!defined($rrGcaGcfList{$asmId})) {
        printf STDERR "# suppressed $asmId\n";
        next;
      }
    }
    my $commonName = "n/a";
    if (defined($ncbiCommonName{$asmId})) {
      $commonName = $ncbiCommonName{$asmId};
      if ("n/a" eq $commonName) {
        printf STDERR "# getting n/a commonName from ncbiCommonName{%s}\n", $asmId;
      }
    } elsif (defined($comName{$asmId})) {
      $commonName = $comName{$asmId};
      if ("n/a" eq $commonName) {
        printf STDERR "# getting n/a commonName from comName{%s}\n", $asmId;
      }
    } else {
      printf STDERR "# no commonName for %s in ncbiCommonName or comName\n", $asmId;
      next;
    }

#   if (! defined($gcxCountry{$asmId})) {
#      printf STDERR "# no country for $asmId, date: %s, submitter: %s\n", $gcxDate{$asmId}, $gcxSubmitter{$asmId};
#      next;
#    }
#    if ("n/a" eq $gcxCountry{$asmId}) {
#      printf STDERR "# country is n/a $asmId\n";
#      next;
#    }
  my ($p0, $p1, $p2) = split('_', $asmId, 3);
  my $accessionId = "${p0}_${p1}";
  my $gcX = substr($asmId, 0, 3);
  my $d0 = substr($asmId, 4, 3);
  my $d1 = substr($asmId, 7, 3);
  my $d2 = substr($asmId, 10, 3);
  my $buildDir = "/hive/data/outside/ncbi/genomes/$gcX/$d0/$d1/$d2/$asmId";
  my $asmRpt = "$buildDir/${asmId}_assembly_report.txt";
  my $asmFna = "$buildDir/${asmId}_genomic.fna.gz";
  my $browserUrl = sprintf("https://genome.ucsc.edu/h/%s", $accessionId);
  my $arkDownload = sprintf("https://hgdownload.soe.ucsc.edu/hubs/%s/%s/%s/%s/%s/", $gcX, $d0, $d1, $d2, $accessionId);
  my $destDir = "/hive/data/outside/ncbi/genomes/sizes/$gcX/$d0/$d1/$d2";
  my $chromInfo = "/hive/data/outside/ncbi/genomes/sizes/$gcX/$d0/$d1/$d2/${asmId}.chromInfo.txt";
  my $n50Txt = "/hive/data/outside/ncbi/genomes/sizes/$gcX/$d0/$d1/$d2/${asmId}.n50.txt";
  my $contigN50 = "/hive/data/outside/ncbi/genomes/sizes/$gcX/$d0/$d1/$d2/${asmId}.contigs.n50.txt";
  my $scaffoldN50 = "/hive/data/outside/ncbi/genomes/sizes/$gcX/$d0/$d1/$d2/${asmId}.scaffolds.n50.txt";
  my $asmSize = 0;
  my $asmContigCount = 0;
  my $n50Size = 0;
  my $n50Count = 0;
  my $n50ContigSize = 0;
  my $n50ContigCount = 0;
  my $n50ScaffoldSize = 0;
  my $n50ScaffoldCount = 0;
  if (defined($metaInfo{$asmId})) {
   ($asmSize, $asmContigCount, $n50Size, $n50Count, $n50ContigSize, $n50ContigCount, $n50ScaffoldSize, $n50ScaffoldCount) = split('\t', $metaInfo{$asmId});
  } else {
  my ($dev, $ino, $mode, $nlink, $uid, $gid, $rdev, $size, $atime, $mtime, $ctime, $blksize, $blocks);
  my $fnaModTime = 0;
  if (-s "$asmFna") {
    ($dev, $ino, $mode, $nlink, $uid, $gid, $rdev, $size, $atime, $mtime, $ctime, $blksize, $blocks) = stat($asmFna);
    $fnaModTime = $mtime;
  }
  my $ciModTime = 0;
  if ( -s "$chromInfo" ) {
    ($dev, $ino, $mode, $nlink, $uid, $gid, $rdev, $size, $atime, $mtime, $ctime, $blksize, $blocks) = stat($chromInfo);
    $ciModTime = $mtime;
  }
  if ($fnaModTime > $ciModTime) {
    printf STDERR "# new %s\n", $chromInfo;
    printf STDERR "# from %s\n", $asmFna;
    print `mkdir -p $destDir`;
    print `faSize -detailed $asmFna | sort -k2,2nr > $chromInfo`;
    print `touch -r $asmFna $chromInfo`;
  }
  if ( -s "$chromInfo" ) {
    ($asmSize, $asmContigCount) = sizeUpChromInfo($chromInfo);
    if ( ! -s "$n50Txt" ) {
      print `n50.pl "$chromInfo" > "$n50Txt" 2>&1`;
    }
    ($n50Size, $n50Count) = readN50($n50Txt);
    if ( -s "$contigN50" ) {
      ($n50ContigSize, $n50ContigCount) = readN50($contigN50);
    }
    if ( -s "$scaffoldN50" ) {
      ($n50ScaffoldSize, $n50ScaffoldCount) = readN50($scaffoldN50);
    }
  } else {
    printf STDERR "# chromInfo missing: %s\n", $asmId;
    printf STDERR "# %s\n", $chromInfo;
  }
   die "ERROR duplicate newMetaInfo{$asmId}" if (defined($newMetaInfo{$asmId}));
   die "ERROR duplicate metaInfo{$asmId} for newMetaInfo{$asmId}" if (defined($metaInfo{$asmId}));
   $newMetaInfo{$asmId} = join("\t", ($asmSize, $asmContigCount, $n50Size, $n50Count, $n50ContigSize, $n50ContigCount, $n50ScaffoldSize, $n50ScaffoldCount) );
  }	# else if (defined($metaInfo{$asmId}))
  # if asmSize is below the minimum, don't use it
  if ($asmSize < $minimalGenomeSize{$clade}) {
    printf STDERR "# %s underSized 2 %d %s %s < %s\n", $clade, ++$underSized, $asmId, commify($asmSize), commify($minimalGenomeSize{$clade});
     printf STDERR "# ACK would be genArk assembly %s\n", $asmId if (defined($genArkAsm{$asmId}));
     printf STDERR "# ACK would be UCSC RR %s\n", $asmId if (defined($rrGcaGcfList{$asmId}));
     next;
  }
  my $iucnStatus = "&nbsp;";
  my $iucnLink = "";
  if (defined($sciNames{$asmId})) {
     my $iucnSciName = $sciNames{$asmId};
 $iucnSciName = $ncbiToIucnNames{$sciNames{$asmId}} if (defined($ncbiToIucnNames{$sciNames{$asmId}}));
     $iucnLink = "https://www.iucnredlist.org/species/$iucnLink{$iucnSciName}" if (defined($iucnLink{$iucnSciName}));
     if ($iucnSciName ne $sciNames{$asmId}) {
       $equivalentNamesUsed{$sciNames{$asmId}} = $iucnSciName;
     }
     if (defined($iucnSciNames{$iucnSciName})) {
       $iucnStatus = $iucnSciNames{$iucnSciName};
     }
  }
  ++$asmCountInTable;
  my $statusColor = "";
  if ($iucnStatus ne "&nbsp;") {
    $statusColor = $statusColors{$iucnStatus};
    ++$statusCounts{$iucnStatus};
  }

  ############# starting a table row  #################################
  if ($asmId =~ m/^GCF/) {
    $gcfGcaCounts{'GCF'} += 1;
  } elsif ($asmId =~ m/GCA/) {
    $gcfGcaCounts{'GCA'} += 1;
  }
  ### If equivalent to UCSC database browser, make reference to RR browser
  my $ucscDb = "";
  $ucscDb = "/" . $rrGcaGcfList{$asmId} if (defined($rrGcaGcfList{$asmId}));
  if (length($ucscDb)) {
     $browserUrl = sprintf("https://genome.ucsc.edu/cgi-bin/hgTracks?db=%s", $rrGcaGcfList{$asmId});
  }

  printf PC "%d", $asmCountInTable;	# start a line output to clade.tableData.tsv

  ## count number of different scientific names used in this clade table
  if (!defined($cladeSciNameCounts{$clade})) {
    my %h;
    $cladeSciNameCounts{$clade} = \%h;
  }
  my $csnPtr = $cladeSciNameCounts{$clade};
  $csnPtr->{$sciNames{$asmId}} += 1 if (defined($sciNames{$asmId}));
  my $rowClass = "";
  my $gcaGcfClass = "gca";
  $gcaGcfClass = " gcf" if ($asmId =~ m/^GCF/);
  if (defined($comName{$asmId})) {
    if (defined($rrGcaGcfList{$asmId})) {
      $rowClass = " class='ucscDb $gcaGcfClass $clade'"; # present in UCSC db
    } else {
      $rowClass = " class='gak $gcaGcfClass $clade'"; # present in GenArk
    }
  } else { # can be requested
    if (defined($rrGcaGcfList{$asmId})) {
      $rowClass = " class='ucscDb $gcaGcfClass $clade'"; # present in UCSC db
    } else {
      $rowClass = " class='gar $gcaGcfClass $clade'"; # available for request
    }
  }
### can override CSS settings here
###    $rowClass = " class='gar' style='display: none;'";

  ############# obsolete first column, a running count, and establish row color ###
  if ( 0 == 1 ) {
    if (length($statusColor)) {
       printf "<tr%s style='color:%s;'><th style='text-align:right;'>%d</th>", $rowClass, $statusColor, $asmCountInTable;
    } else {
       printf "<tr%s><th style='text-align:right;'>%d</th>", $rowClass, $asmCountInTable;
    }
  }
  # experiment with hiding all rows over 500 count to see if that helps
  # chrom browser initial loading performance
  # try out the table with out any count, just get the row started
  if (length($statusColor)) {
     if ($asmCountInTable > 500) {
       printf "<tr%s style='color:%s; display:none;'>", $rowClass, $statusColor;
     } else {
       printf "<tr%s style='color:%s;'>", $rowClass, $statusColor;
     }
  } else {
     if ($asmCountInTable > 500) {
       printf "<tr%s style='display:none;'>", $rowClass;
     } else {
       printf "<tr%s>", $rowClass;
     }
  }
  ############# first column, common name link to browser or request button ##
  if (defined($comName{$asmId})) {
     printf "<th style='text-align:left;'><a href='%s' target=_blank>%s</a></th>", $browserUrl, $commonName;
  } else {
     if (length($ucscDb)) {
       printf "<th style='text-align:left;'><a href='%s' target=_blank>%s</a></th>", $browserUrl, $commonName;
     } else {
       printf "<th style='text-align:left;'><button type='button' onclick='gar.openModal(this)' name='%s'>%s</button></th>", $asmId, $commonName;
     }
  }
  printf PC "\t%s", $commonName;	# output to clade.tableData.tsv

  ############# second column, scientific name and google image search #########
  if (defined($sciNames{$asmId})) {
    my $noSpace = $sciNames{$asmId};
    $noSpace =~ s/ /+/g;
    my $imgSearchUrl="https://images.google.com/images?q=$noSpace&um=1&hl=en&safe=active&nfpr=1&tbs=il:cl";
    if ($assembliesAvailable > 1) {
      printf "<td><a href='%s' target=_blank>%s</a>&nbsp;(%s)</td>", $imgSearchUrl, $sciNames{$asmId}, commify($assembliesAvailable);
    } else {
      printf "<td><a href='%s' target=_blank>%s</a></td>", $imgSearchUrl, $sciNames{$asmId};
    }
    printf PC "\t%s", $sciNames{$asmId};	# output to clade.tableData.txt
  } else {
    printf "<td>n/a</td>";
    printf PC "\t%s", "n/a";	# output to clade.tableData.txt
  }

  ############# third column,  NCBI assembly and link to NCBI ############
  my $asmUrl = "https://www.ncbi.nlm.nih.gov/assembly/$accessionId";
  printf "<td><a href='%s' target=_blank>%s%s</a></td>", $asmUrl, $asmId, $ucscDb;
  printf PC "\t%s", $asmId;	# output to clade.tableData.txt

  ############# fourth column,  assembly size ################
  if ($asmSize > 0) {
    $totalAssemblySize += $asmSize;
    printf "<td style='display:none; text-align:right;'>%s</td>", commify($asmSize);
    printf PC "\t%d", $asmSize;	# output to clade.tableData.txt
  } else {
    printf "<td style='display:none;'>&nbsp;</td>";
    printf PC "\t%s", "n/a";	# output to clade.tableData.txt
  }

  ############# fifth column,  sequence count ################
  if ($asmContigCount > 0) {
    $totalContigCounts += $asmContigCount;
    printf "<td style='display:none; text-align:right;'>%s</td>", commify($asmContigCount);
    printf PC "\t%d", $asmContigCount;	# output to clade.tableData.txt
  } else {
    printf "<td style='display:none;'>&nbsp;</td>";
    printf PC "\t%s", "n/a";	# output to clade.tableData.txt
  }

  ############# sixth, seventh columns, N50 for scaffold, contig ##############
  if ($n50ScaffoldSize > 0 ) {
    n50Cell($n50ScaffoldSize, $n50ScaffoldCount, \*PC);
  } else {	# substitute assembly N50 when no scaffold N50 available
    n50Cell($n50Size, $n50Count, \*PC);
  }
  n50Cell($n50ContigSize, $n50ContigCount, \*PC);

  ############# eighth column,  IUCN status and link ################
  if (length($iucnLink) > 0) {
    printf "<td style='display:none;'><a href='%s' target=_blank>%s</a></td>", $iucnLink, $iucnStatus;
  } else {
    printf "<td style='display:none;'>%s</td>", $iucnStatus;
  }
  printf PC "\t%s", $iucnStatus;	# output to clade.tableData.txt

  ############# ninth column,  taxId and link to NCBI ################
  if (defined($asmTaxId{$asmId})) {
    my $taxUrl = "https://www.ncbi.nlm.nih.gov/Taxonomy/Browser/wwwtax.cgi?id=$asmTaxId{$asmId}";
    printf "<td style='display:none; text-align:right;'><a href='%s' target=_blank>%s</a></td>", $taxUrl, $asmTaxId{$asmId};
    printf PC "\t%s", $asmTaxId{$asmId};	# output to clade.tableData.txt
  } else {
    printf "<td style='display:none;'>n/a</td>";
    printf PC "\t%s", "n/a";	# output to clade.tableData.txt
  }

  ############# tenth column,  assembly date ################
  if (defined($asmDate{$asmId})) {
    printf "<td style='display:none;'>%s</td>", $asmDate{$asmId};
    printf PC "\t%s", $asmDate{$asmId};	# output to clade.tableData.txt
  } else {
    printf "<td style='display:none;'>n/a</td>";
    printf PC "\t%s", "n/a";	# output to clade.tableData.txt
  }

  ############# eleventh column,  submitter ################
  $asmUrl = "https://www.ncbi.nlm.nih.gov/assembly/$accessionId";
  if (defined($asmSubmitter{$asmId})) {
    my $submitterSortKey = lc($asmSubmitter{$asmId});
    $submitterSortKey =~ s/ //g;
    printf "<td sorttable_customkey='%s' style='display:none;'>%s</td>", substr($submitterSortKey,0,20), $asmSubmitter{$asmId};
    printf PC "\t%s", $asmSubmitter{$asmId};	# output to clade.tableData.txt
  } else {
    printf "<td sorttable_customkey='n/a' style='display:none;'>n/a</td>";
    printf PC "\t%s", "n/a";	# output to clade.tableData.txt
  }

  ############# twelveth column,  clade ################
  printf "<td style='display:none;'>%s</td>\n", $clade;
  printf PC "\t%s", $clade;

  printf PC "\n";	# finished a line output to clade.tableData.txt
  printf "</tr>\n";
  }	#	foreach my $asmId (@$cPtr)
  close (PC);	# finished with clade.tableData.txt output
}	#	foreach my $clade (@clades)

##########################################################################
## single table is finished, output the end of tbody and the tfoot row
##########################################################################
if ($asmCountInTable > 1) {
  my $crCount = 0;
  my $enCount = 0;
  my $vuCount = 0;
  foreach my $statId (keys %statusCounts) {
    $crCount = $statusCounts{$statId} if ($statId eq "CR");
    $enCount = $statusCounts{$statId} if ($statId eq "EN");
    $vuCount = $statusCounts{$statId} if ($statId eq "VU");
  }
  my $sciNameTotal = 0;
  foreach my $c (@clades) {
    my $csnPtr = $cladeSciNameCounts{$c};
    my $sciNameTotal = 0;
    foreach my $cladeSciName (keys %$csnPtr) {
      ++$sciNameTotal;
    }
  }
  printf "
</tbody>
<!--
<tfoot><tr><th>assemblies:&nbsp;%s</th>
  <th>Species:&nbsp;%s</th>
  <td>GenBank: %s RefSeq %s</td>
  <td>%s nucleotides</td>
  <td colspan=4><span style='color:%s;'>CR&nbsp;%s</span><span style='color:%s;'>&nbsp;EN&nbsp;%s</span><span style='color:%s;'>&nbsp;VU&nbsp;%s</span></td>
  <td>submittors</td>
</tr>
", commify($asmCountInTable), commify($sciNameTotal), commify($gcfGcaCounts{'GCA'}), commify($gcfGcaCounts{'GCF'}), commify($totalAssemblySize), $criticalColor, commify($crCount), $endangeredColor, commify($enCount), $vulnerableColor, commify($vuCount);
  printf "</tfoot>
-->
</table>\n";
} else {
  print "</tbody></table>\n";
}

printf "  </div>        <!-- display inline-block to be 'text' centered -->\n";
printf "</div>  <!-- this parent div is text-align: center to center children -->\n\n";

############################################################################

if ( 1 == 0) {
printf "<hr>\n";
printf "<a id='nameTranslateSection'></a>\n";
printf "<p><a href='#pageTop'>=== back to top of page ===</a></p>\n";
printf "<p>
Please note, in some cases the IUCN scientific name was translated to the
scientific name used in the NCBI assembly to establish an equivalence
between the two data sources.  Please beware of this translation when
interpreting the IUCN status.
</p>\n";
printf "<button id='nameTranslationHideShow' onclick='gar.hideTable(\"nameTranslation\")'>[hide]</button>\n";
printf "<table class='sortable borderOne' id='nameTranslation'>\n";
printf "<caption style='text-align:center;'><b>IUCN to NCBI scientific name translation</b></caption>\n";
printf "<thead>\n";
printf "<tr>\n";
printf "<th>NCBI assembly scientific name</th>\n";
printf "<th>translated to IUCN scientific name</th>\n";
printf "</thead><tbody>\n";
foreach my $ncbiName (sort keys(%equivalentNamesUsed)) {
   printf "<tr><th>%s</th><th>%s</th></tr>\n", $ncbiName, $equivalentNamesUsed{$ncbiName};
}
print "</tbody></table>\n";
}	#	if ( 1 == 0)

######### output new metaInfo to accumulating metaInfo file
my $newMetaInfoCount = 0;
foreach my $asmId (sort keys %newMetaInfo) {
  ++$newMetaInfoCount;
}
if ($newMetaInfoCount > 0) {
printf STDERR "# adding %d new items to ../accumulateMetaInfo.tsv\n", $newMetaInfoCount;
if (-s "../accumulateMetaInfo.tsv" ) {
  open (FH, ">>../accumulateMetaInfo.tsv") or die "can not append to ../accumulateMetaInfo.tsv";
} else {
  open (FH, ">../accumulateMetaInfo.tsv") or die "can not write to ../accumulateMetaInfo.tsv";
}
foreach my $asmId (sort keys %newMetaInfo) {
  printf FH "%s\t%s\n", $asmId, $newMetaInfo{$asmId};
  printf STDERR "# new metaData for %s\n", $asmId;
  ++$newMetaInfoCount;
}
close (FH);
} else {
  printf STDERR "# no new metaInfo\n";
}

printf STDERR "# done at exit\n";
exit 0;

__END__

my $count = 0;
foreach my $asmId (sort keys %gcxCountry) {
  next if (defined ($asmSuppressed{$asmId}));
  next if (! defined($gcxCountry{$asmId}));
  next if (! defined($sciName{$asmId}));
  next if ("n/a" eq $gcxCountry{$asmId});
##########################################################################
# found discussion of google image search URL at:
# https://stackoverflow.com/questions/21530274/format-for-a-url-that-goes-to-google-image-search
# did not work:
#    my $imgSearchUrl="https://www.google.com/search?q=$noSpace&tbm=isch";
# um=1&hl=en&safe=active&nfpr=1
# and
# http://devcoma.blogspot.com/2017/04/google-search-parameters-resources.html
# as_rights=cc_publicdomain
#     my $imgSearchUrl="https://images.google.com/images?q=$noSpace&um=1&hl=en&safe=active&nfpr=1";
# safe=active == safe search on
# tbs=il:cl - limit result to creative commons license
}
