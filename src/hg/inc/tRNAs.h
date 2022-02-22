/* tRNAs.h was originally generated by the autoSql program, which also 
 * generated tRNAs.c and tRNAs.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2010 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef TRNAS_H
#define TRNAS_H

#define TRNAS_NUM_COLS 12

struct tRNAs
/* transfer RNA genes */
    {
    struct tRNAs *next;  /* Next in singly linked list. */
    char *chrom;	/* chromosome */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* transfer RNA gene name */
    unsigned score;	/* Score from 900-1000.  1000 is best */
    char strand[2];	/* Value should be + or - */
    char *aa;	/* Amino acid for the tRNA */
    char *ac;	/* Anticodon for the tRNA */
    char *intron;	/* Coordinates for intron */
    float trnaScore;	/* tRNAScanSE score */
    char *genomeUrl;	/* GtRNAdb genome summary URL */
    char *trnaUrl;	/* GtRNAdb tRNA alignment URL */
    };

void tRNAsStaticLoad(char **row, struct tRNAs *ret);
/* Load a row from tRNAs table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct tRNAs *tRNAsLoad(char **row);
/* Load a tRNAs from row fetched with select * from tRNAs
 * from database.  Dispose of this with tRNAsFree(). */

struct tRNAs *tRNAsLoadAll(char *fileName);
/* Load all tRNAs from whitespace-separated file.
 * Dispose of this with tRNAsFreeList(). */

struct tRNAs *tRNAsLoadAllByChar(char *fileName, char chopper);
/* Load all tRNAs from chopper separated file.
 * Dispose of this with tRNAsFreeList(). */

#define tRNAsLoadAllByTab(a) tRNAsLoadAllByChar(a, '\t');
/* Load all tRNAs from tab separated file.
 * Dispose of this with tRNAsFreeList(). */

struct tRNAs *tRNAsCommaIn(char **pS, struct tRNAs *ret);
/* Create a tRNAs out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new tRNAs */

void tRNAsFree(struct tRNAs **pEl);
/* Free a single dynamically allocated tRNAs such as created
 * with tRNAsLoad(). */

void tRNAsFreeList(struct tRNAs **pList);
/* Free a list of dynamically allocated tRNAs's */

void tRNAsOutput(struct tRNAs *el, FILE *f, char sep, char lastSep);
/* Print out tRNAs.  Separate fields with sep. Follow last field with lastSep. */

#define tRNAsTabOut(el,f) tRNAsOutput(el,f,'\t','\n');
/* Print out tRNAs as a line in a tab-separated file. */

#define tRNAsCommaOut(el,f) tRNAsOutput(el,f,',',',');
/* Print out tRNAs as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* TRNAS_H */

