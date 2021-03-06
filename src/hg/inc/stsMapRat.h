/* stsMapRat.h was originally generated by the autoSql program, which also 
 * generated stsMapRat.c and stsMapRat.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2004 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef STSMAPRAT_H
#define STSMAPRAT_H

struct stsMapRat
/* STS marker and its position on golden path and various maps */
    {
    struct stsMapRat *next;  /* Next in singly linked list. */
    char *chrom;	/* Chromosome or 'unknown' */
    int chromStart;	/* Start position in chrom - negative 1 if unpositioned */
    unsigned chromEnd;	/* End position in chrom */
    char *name;	/* Name of STS marker */
    unsigned score;     /* Score of a marker = 1000/(#placements) when placed uniquely, else 1500/(#placements) when placed in multiple locations */
    unsigned identNo;	/* Identification number of STS */
    char *ctgAcc;	/* Contig accession number */
    char *otherAcc;	/* Accession number of other contigs that the marker hits */
    char *rhChrom;	/* Chromosome (no chr) from RH map or 0 if none */
    float rhPos;	/* Position on rh map */
    float rhLod;	/* Lod score of RH map */
    char *fhhChr;	/* Chromosome (no chr) from FHHxACI genetic or 0 if none */
    float fhhPos;	/* Position on FHHxACI map */
    char *shrspChrom;	/* Chromosome (no chr) from SHRSPxBN geneticmap or 0 if none */
    float shrspPos;	/* Position on SHRSPxBN genetic map */
    };

void stsMapRatStaticLoad(char **row, struct stsMapRat *ret);
/* Load a row from stsMapRat table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct stsMapRat *stsMapRatLoad(char **row);
/* Load a stsMapRat from row fetched with select * from stsMapRat
 * from database.  Dispose of this with stsMapRatFree(). */

struct stsMapRat *stsMapRatLoadAll(char *fileName);
/* Load all stsMapRat from a tab-separated file.
 * Dispose of this with stsMapRatFreeList(). */

struct stsMapRat *stsMapRatCommaIn(char **pS, struct stsMapRat *ret);
/* Create a stsMapRat out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new stsMapRat */

void stsMapRatFree(struct stsMapRat **pEl);
/* Free a single dynamically allocated stsMapRat such as created
 * with stsMapRatLoad(). */

void stsMapRatFreeList(struct stsMapRat **pList);
/* Free a list of dynamically allocated stsMapRat's */

void stsMapRatOutput(struct stsMapRat *el, FILE *f, char sep, char lastSep);
/* Print out stsMapRat.  Separate fields with sep. Follow last field with lastSep. */

#define stsMapRatTabOut(el,f) stsMapRatOutput(el,f,'\t','\n');
/* Print out stsMapRat as a line in a tab-separated file. */

#define stsMapRatCommaOut(el,f) stsMapRatOutput(el,f,',',',');
/* Print out stsMapRat as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* STSMAPRAT_H */

