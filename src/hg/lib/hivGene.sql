# hivGene.sql was originally generated by the autoSql program, which also 
# generated hivGene.c and hivGene.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#HIV Genes and Regions
CREATE TABLE hivGene (
    bin smallint unsigned not null,	# used for efficient position indexing
    chrom varchar(255) not null,	# Chromosome
    chromStart int unsigned not null,	# Start position in chromosome
    chromEnd int unsigned not null,	# End position in chromosome
    name varchar(255) not null,	# Name of item
              #Indices
    PRIMARY KEY(name)
);
