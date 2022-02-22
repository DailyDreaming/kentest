table dbNsfpSeqChange
"Coding sequence missense changes annotated by dbNSFP (http://dbnsfp.houstonbioinformatics.org/)"
    (
    string chrom;      "Reference sequence chromosome or scaffold"
    uint   chromStart; "Start position in chromosome"
    uint   chromEnd;   "End position in chromosome"
    enum('A','C','G','T') refAl;   "Allele found in reference assembly"
    lstring ensTxId;   "Ensembl transcript ID(s); can be comma-sep'd list of overlapping transcripts"
    lstring ensGeneId; "Ensembl gene ID(s); usually single, but can be comma-sep'd list parallel to ensTxId"
    enum('+','-') strand; "Strand of Ensembl transcript(s)"
    string refCodon;   "Codon from reference assembly; can be list????"
    string codonPos;   "Position of change in codon (1, 2 or 3); can be list"
    char[1] refAa;     "Amino acid for refCodon or '.' (in which case we can recompute)"
    string aaPos;      "Offset of changed amino acid (1-based); can be list"
    enum('A','C','G','T') altAl1;       "alternate allele #1"
    char[1] altAa1;                     "Amino acid for codon with altAl1 substituted at codonPos"
    enum('A','C','G','T','.') altAl2;   "alternate allele #2"
    char[1] altAa2;                     "Amino acid for codon with altAl2 substituted at codonPos"
    enum('A','C','G','T','.') altAl3;   "alternate allele #3"
    char[1] altAa3;                     "Amino acid for codon with altAl3 substituted at codonPos"
    )
