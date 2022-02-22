#!/usr/bin/env perl

# Read in a file with 3 columns: sample name, Pangolin lineage, GISAID clade.
# Choose a color for the sample according to the scheme in Figure 1 of
# https://www.eurosurveillance.org/content/10.2807/1560-7917.ES.2020.25.32.2001410
# Figure 1 was generated by Emma Hodcroft of Nextstrain and Aine O'Toole, Pangolin author.

use warnings;
use strict;

my %gc2col = ( # GISAID clade coloring
              "S"  => "#ec676d",
              "L"  => "#f79e43",
              "O"  => "#f9d136",
              "V"  => "#faea95",
              "G"  => "#b6d77a",
              "GH" => "#8fd4ed",
              "GR" => "#a692c3"
             );

while (<>) {
  chomp;
  my ($sample, $lineage, $gClade) = split;
  my $color = "#000000";
  if (defined $gc2col{$gClade}) {
    $color = $gc2col{$gClade};
  }
  print "$sample\t$color\n";
}
