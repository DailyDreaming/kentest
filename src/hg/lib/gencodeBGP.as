table gencodeBGP
"GENCODE bigGenePred"
   (
   string chrom;       "Reference sequence chromosome or scaffold"
   uint   chromStart;  "Start position in chromosome"
   uint   chromEnd;    "End position in chromosome"
   string name;        "Ensembl ID"
   uint score;         "Score (0-1000)"
   char[1] strand;     "+ or - for strand"
   uint thickStart;    "Start of where display should be thick (start codon)"
   uint thickEnd;      "End of where display should be thick (stop codon)"
   uint reserved;       "RGB value (use R,G,B string in input file)"
   int blockCount;     "Number of blocks"
   int[blockCount] blockSizes; "Comma separated list of block sizes"
   int[blockCount] chromStarts; "Start positions relative to chromStart"
   string name2;       "UCSC Genes ID"
   string cdsStartStat; "Status of CDS start annotation (none, unknown, incomplete, or complete)"
   string cdsEndStat;   "Status of CDS end annotation (none, unknown, incomplete, or complete)"
   int[blockCount] exonFrames; "Exon frame {0,1,2}, or -1 if no frame for exon"
   string type;        "Transcript type"
   string geneName;    "Gene Symbol"
   string geneName2;   "UniProt display ID"
   string geneType;    "Gene type"

# high level type of transcript (from gencodeAttrs)"
   string transcriptClass; "Transcript Class"
   string source; "Source of transcript (from gencodeTranscriptSource)"
   string transcriptType; "BioType of transcript (from gencodeAttrs)"
   string tag; "symbolic tags (from gencodeTags)"
   string level;           "support level, tsl1 is strongest support, tsl5 weakest, NA means not analyzed (from gencodeTranscriptionSupportLevel)"
# tier:  all, basic, canonical
   string tier;   "Transcript Tier"
   )

