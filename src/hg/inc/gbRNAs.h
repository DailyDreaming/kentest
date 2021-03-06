/* gbRNAs.h was originally generated by the autoSql program, which also 
 * generated gbRNAs.c and gbRNAs.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2005 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef GBRNAS_H
#define GBRNAS_H

#define GBRNAS_NUM_COLS 8

struct gbRNAs
/* Genbank RNA genes */
    {
    struct gbRNAs *next;  /* Next in singly linked list. */
    char *chrom;	/* chromosome */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* gene name */
    unsigned score;	/* Score from 900-1000.  1000 is best */
    char strand[2];	/* Value should be + or - */
    char *product;	/* Description of RNA gene */
    char *intron;	/* Coordinates of intron in RNA gene */
    };

void gbRNAsStaticLoad(char **row, struct gbRNAs *ret);
/* Load a row from gbRNAs table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct gbRNAs *gbRNAsLoad(char **row);
/* Load a gbRNAs from row fetched with select * from gbRNAs
 * from database.  Dispose of this with gbRNAsFree(). */

struct gbRNAs *gbRNAsLoadAll(char *fileName);
/* Load all gbRNAs from whitespace-separated file.
 * Dispose of this with gbRNAsFreeList(). */

struct gbRNAs *gbRNAsLoadAllByChar(char *fileName, char chopper);
/* Load all gbRNAs from chopper separated file.
 * Dispose of this with gbRNAsFreeList(). */

#define gbRNAsLoadAllByTab(a) gbRNAsLoadAllByChar(a, '\t');
/* Load all gbRNAs from tab separated file.
 * Dispose of this with gbRNAsFreeList(). */

struct gbRNAs *gbRNAsCommaIn(char **pS, struct gbRNAs *ret);
/* Create a gbRNAs out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new gbRNAs */

void gbRNAsFree(struct gbRNAs **pEl);
/* Free a single dynamically allocated gbRNAs such as created
 * with gbRNAsLoad(). */

void gbRNAsFreeList(struct gbRNAs **pList);
/* Free a list of dynamically allocated gbRNAs's */

void gbRNAsOutput(struct gbRNAs *el, FILE *f, char sep, char lastSep);
/* Print out gbRNAs.  Separate fields with sep. Follow last field with lastSep. */

#define gbRNAsTabOut(el,f) gbRNAsOutput(el,f,'\t','\n');
/* Print out gbRNAs as a line in a tab-separated file. */

#define gbRNAsCommaOut(el,f) gbRNAsOutput(el,f,',',',');
/* Print out gbRNAs as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* GBRNAS_H */

