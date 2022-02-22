#!/bin/bash
set -beEu -x -o pipefail

#	Do not modify this script, modify the source tree copy:
#	kent/src/hg/utils/otto/sarscov2phylo/processRelease.sh

usage() {
    echo "usage: $0 releaseLabel problematic_sites_sarsCov2.vcf"
}

if [ $# != 2 ]; then
  usage
  exit 1
fi

releaseLabel=$1
problematicSitesVcf=$2

echo "releaseLabel=$releaseLabel problematicSitesVcf=$problematicSitesVcf"

scriptDir=$(dirname "${BASH_SOURCE[0]}")

# UShER (and matToVcf)
usherDir=~angie/github/usher
usher=$usherDir/build/usher
matToVcf=$usherDir/build/matToVcf

# strain_phylogenetics / find_parsimonious_assignments for parsimony scores
find_parsimonious_assignments=~angie/github/strain_phylogenetics/build/find_parsimonious_assignments

# Files generated by getRelease.sh
metadata=gisaid_metadata.tsv
fasta=gisaid_sequences.fasta
alignedFasta=gisaid_aligned.fasta

# We'll need to prune the tree to keep only those sequences that are in metadata and fasta:
grep ^\> $fasta | sed -re 's/^>//' | sort > namesInFasta

# Make renaming files for tree (EPI_ IDs) and VCF (isolate names): add strain name and
# date with shortened year.
awk -F"\t" '{print $3 "\t" $1 "|" $3 "|" $5;}' $metadata \
| grep -Fwf namesInFasta \
| sed -re 's/\|20/\|/;' \
| sort > tree.renaming
awk -F"\t" '{print $1 "\t" $1 "|" $3 "|" $5;}' $metadata \
| grep -Fwf namesInFasta \
| sed -re 's/\|20/\|/;' \
| sort  > vcf.renaming
wc -l tree.renaming
wc -l vcf.renaming

# Rename tree IDs from just EPI IDs to strain|epi|date ids and prune any sequences not in
# metadata and fasta:
phyloRenameAndPrune ft_SH.tree tree.renaming ft_SH.renamed.tree
sed -re 's/\)[0-9.]+:/\):/g; s/:[0-9e.:-]+//g; s/[\(\);]//g; s/,/\n/g;'" s/'//g;" \
  ft_SH.renamed.tree \
| sort > tree.renamedPruned.ids.sorted
wc -l tree.renamedPruned.ids.sorted

# Set the root of the tree to the Wuhan/Hu-1 (NC_045512.2) reference not WIV04:
~angie/github/newick_utils/src/nw_reroot ft_SH.renamed.tree \
    'Wuhan/Hu-1/2019|EPI_ISL_402125|19-12-26' > ft_SH.reroot.nh

# Run faToVcf without any filtering, masking or conversion of ambiguous alleles:
time faToVcf $alignedFasta stdout -includeRef \
  -ref=Wuhan/Hu-1/2019 \
  -vcfChrom=NC_045512v2 -verbose=2 \
| vcfRenameAndPrune stdin vcf.renaming gisaid-$releaseLabel.unfiltered.vcf
ls -l gisaid-$releaseLabel.unfiltered.vcf
wc -l gisaid-$releaseLabel.unfiltered.vcf
gzip -f gisaid-$releaseLabel.unfiltered.vcf

# Run usher and matToVcf to make ambig-resolved VCF for hgTracks
time $usher -c \
  --vcf gisaid-$releaseLabel.unfiltered.vcf.gz \
  --tree ft_SH.reroot.nh \
  --save-mutation-annotated-tree sarscov2phylo-$releaseLabel.notMasked.pb \
  --write-uncondensed-final-tree
mv uncondensed-final-tree.nh ft_SH.reroot.collapsed.notMasked.nh 
$matToVcf -i sarscov2phylo-$releaseLabel.notMasked.pb \
    -v gisaid-$releaseLabel.vcf
bgzip -f gisaid-$releaseLabel.vcf
tabix -p vcf gisaid-$releaseLabel.vcf.gz

# Remove problematic sites recommended for masking for usher/phyloPlace
tawk '{ if ($1 ~ /^#/) { print; } else if ($7 == "mask") { $1 = "NC_045512v2"; print; } }' \
    $problematicSitesVcf > mask.vcf
time vcfFilter -excludeVcf=mask.vcf gisaid-$releaseLabel.unfiltered.vcf.gz \
| gzip -c \
    > gisaid-$releaseLabel.unfiltered.masked.vcf.gz

# Full find_parsimonious_assignments output on uncollapsed tree for collaborators
time $find_parsimonious_assignments --tree ft_SH.reroot.nh \
    --vcf gisaid-$releaseLabel.unfiltered.masked.vcf.gz \
| gzip -c \
    > find_parsimonious_assignments.$releaseLabel.out.gz

# Run usher to collapse tree and make masked protobuf for hgPhyloPlace
time $usher -c \
  --vcf gisaid-$releaseLabel.unfiltered.masked.vcf.gz \
  --tree ft_SH.reroot.nh \
  --save-mutation-annotated-tree sarscov2phylo-$releaseLabel.masked.pb \
  --write-uncondensed-final-tree
mv uncondensed-final-tree.nh ft_SH.reroot.collapsed.nh 

# Parsimony scores on collapsed tree
time $find_parsimonious_assignments --tree ft_SH.reroot.collapsed.nh \
    --vcf <(gunzip -c gisaid-$releaseLabel.vcf.gz) \
| tail -n+2 \
| sed -re 's/^[A-Z]([0-9]+)[A-Z,]+.*parsimony_score=([0-9]+).*/\1\t\2/;' \
| tawk '{print "NC_045512v2", $1-1, $1, $2;}' \
| sort -k2n,2n \
    > gisaid-$releaseLabel.parsimony.bg
bedGraphToBigWig gisaid-$releaseLabel.parsimony.bg /hive/data/genomes/wuhCor1/chrom.sizes \
    gisaid-$releaseLabel.parsimony.bw

# Full find_parsimonious_assignments output on collapsed tree for collaborators
time $find_parsimonious_assignments --tree ft_SH.reroot.collapsed.nh \
    --vcf gisaid-$releaseLabel.unfiltered.masked.vcf.gz \
    > find_parsimonious_assignments.$releaseLabel.collapsed.out

# Now filter by frequency for faster track display: alt al freq >= 0.001
sampleCount=$(wc -l < tree.renamedPruned.ids.sorted)
minAc001=$(( (($sampleCount + 999) / 1000) ))
time vcfFilter -minAc=$minAc001 -rename gisaid-$releaseLabel.vcf.gz \
    > gisaid-$releaseLabel.minAf.001.vcf
ls -l gisaid-$releaseLabel.minAf.001.vcf
wc -l gisaid-$releaseLabel.minAf.001.vcf
bgzip -f gisaid-$releaseLabel.minAf.001.vcf
tabix -p vcf gisaid-$releaseLabel.minAf.001.vcf.gz

# Alt al freq >= 0.01
minAc01=$(( (($sampleCount + 99) / 100) ))
time vcfFilter -minAc=$minAc01 -rename gisaid-$releaseLabel.minAf.001.vcf.gz \
    > gisaid-$releaseLabel.minAf.01.vcf
ls -l gisaid-$releaseLabel.minAf.01.vcf
wc -l gisaid-$releaseLabel.minAf.01.vcf
bgzip -f gisaid-$releaseLabel.minAf.01.vcf
tabix -p vcf gisaid-$releaseLabel.minAf.01.vcf.gz

# Make sample color files
#*** TODO: Nextstrain Clade is now in field 18!  Add that as an option!
cut -f3,18-20 $metadata \
| sort > metadata.epiToLineageAndClades
# Join on EPI ID to associate tree sample names with lineages.
join -t$'\t' tree.renaming metadata.epiToLineageAndClades -o 1.2,2.2,2.3,2.4 > sampleToLineage
$scriptDir/cladeLineageColors.pl sampleToLineage
gzip -f *Colors
